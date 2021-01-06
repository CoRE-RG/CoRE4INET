//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "CreditBasedMeter.h"

namespace CoRE4INET {

Define_Module(CreditBasedMeter);

simsignal_t CreditBasedMeter::creditSignal = registerSignal("credit");

void CreditBasedMeter::receiveSignal(cComponent *source, simsignal_t signalID, long l, __attribute__((unused)) cObject *details)
{
    (void) source;
    (void) signalID;
    inet::EtherMACBase::MACReceiveState macReceiveState = static_cast<inet::EtherMACBase::MACReceiveState>(l);
    if (macReceiveState == inet::EtherMACBase::MACReceiveState::RECEIVING_STATE) //NOT IMPLEMENTED IN INET 3.5
    {
        this->refreshReservedBandwidthAndMaxCredit();
        this->idleSlope(simtime_t{0});
        this->refreshState();
        this->emitCredit();
    }
}

void CreditBasedMeter::initialize()
{
    IEEE8021QciMeter::initialize();
    Timed::initialize();
    inet::EtherMACFullDuplex* mac =  dynamic_cast<inet::EtherMACFullDuplex*>(this->getParentModule()->getParentModule()->getSubmodule("mac"));
    mac->subscribe("receiveState", this);
    if (!mac->gate("phys$o"))
    {
        throw cRuntimeError("A filtering can only be used attached to an EtherMACFullDuplex");
    }
    int numStreamFilters = parameterULongCheckRange(this->getParentModule()->par("numStreamFilters"), 0, UINT32_MAX);
    this->credit = 0;
    this->state = this->State::R_RA;
    this->reservedBandwidth = 0;
    this->maxCredit = 0;
    this->inChannel = mac->gate("phys$o")->findTransmissionChannel();
    this->lastCalcTime = 0;
    this->srptable = dynamic_cast<SRPTable*>(this->getParentModule()->getParentModule()->getParentModule()->getSubmodule("srpTable"));
    this->streamFilters.clear();
    for (int i = 0; i < numStreamFilters; i++)
    {
        this->streamFilters.push_back(dynamic_cast<IEEE8021QciFilter*>(this->getParentModule()->getSubmodule("streamFilter", i)));
    }
    this->lastEmitCredit = 0;
    this->isSendSlopeActive = false;
    this->handleParameterChange(nullptr);
    WATCH(this->credit);
    WATCH(this->state);
    WATCH(this->reservedBandwidth);
    WATCH(this->maxCredit);
}

void CreditBasedMeter::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        cPacket *packet = IEEE8021QciMeter::checkAndRemoveCtrlInfo(msg);
        if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(packet))
        {
            this->numFramesReceived++;
            this->numBytesReceived += frame->getByteLength();
            this->emit(frameReceivedSignal, static_cast<long>(frame->getByteLength()));
            this->refreshReservedBandwidthAndMaxCredit();
            this->idleSlope(simtime_t{0});
            this->refreshState();
            this->meter(frame);
        }
        else
        {
            throw cRuntimeError("Packet type is not EtherFrame");
        }
    }
    else if (msg && msg->arrivedOn("schedulerIn"))
    {
        if (!strcmp(msg->getName(), "CBM_SENDSLOPE_END"))
            isSendSlopeActive = false;
        if (!isSendSlopeActive)
        {
            this->refreshReservedBandwidthAndMaxCredit();
            this->idleSlope(simtime_t{0});
            this->scheduleCreditReachZero();
            this->scheduleCreditReachMax();
            this->refreshState();
            this->emitCredit();
        }

        delete msg;
    }
}

void CreditBasedMeter::handleParameterChange(const char* parname)
{
    Timed::handleParameterChange(parname);
    if(!parname || !strcmp(parname, "maxBurst"))
    {
        this->maxBurst = parameterULongCheckRange(this->par("maxBurst"), 0, UINT32_MAX);
    }
    if (!parname || !strcmp(parname, "srClass"))
    {
        if (!strcmp(this->par("srClass").stringValue(), "A"))
        {
            this->srClass = SR_CLASS::A;
        }
        else if (!strcmp(this->par("srClass").stringValue(), "B"))
        {
            this->srClass = SR_CLASS::B;
        }
        else
        {
            throw cRuntimeError("Parameter srClass of %s is %s and is only allowed to be A or B", this->getFullPath().c_str(),
                    this->par("srClass").stringValue());
        }
    }
}

void CreditBasedMeter::refreshDisplay() const
{
    if (this->state == this->State::R_RA)
    {
        this->getDisplayString().setTagArg("b",3,"green");
    }
    else if (this->state == this->State::R_RF)
    {
        this->getDisplayString().setTagArg("b",3,"red");
    }
}

void CreditBasedMeter::idleSlope(simtime_t delta)
{
    simtime_t currentTime = this->getCurrentTime();
    simtime_t calcTime = currentTime - delta;
    simtime_t idleDuration = calcTime - lastCalcTime;
    if (idleDuration.dbl() > 0)
    {
        this->credit += static_cast<int>(ceil(this->reservedBandwidth * idleDuration.dbl()));
        if (this->credit > this->maxCredit)
        {
            this->credit = this->maxCredit;
        }
        this->lastCalcTime = calcTime;
    }
}

void CreditBasedMeter::sendSlope(inet::EtherFrame *frame)
{
    simtime_t currentTime = this->getCurrentTime();
    simtime_t transmissionDuration = calculateTransmissionDuration(frame);
    this->credit -= static_cast<int>(ceil((inChannel->getNominalDatarate() - this->reservedBandwidth) * transmissionDuration.dbl()));
    this->lastCalcTime = currentTime + transmissionDuration;
    this->scheduleEvent(transmissionDuration, "CBM_SENDSLOPE_END");
    this->isSendSlopeActive = true;
}

void CreditBasedMeter::refreshState()
{
    if (this->credit < 0)
    {
        this->state = this->State::R_RF;
    }
    else
    {
        this->state = this->State::R_RA;
    }
}

void CreditBasedMeter::meter(inet::EtherFrame *frame)
{
    if (this->state == this->State::R_RA)
    {
        IEEE8021QciMeter::sendMessage(frame);
        this->emitCredit();
        this->sendSlope(frame);
        this->refreshState();
    }
    else if (this->state == this->State::R_RF)
    {
        IEEE8021QciMeter::dropMessage(frame);
    }
}

void CreditBasedMeter::refreshReservedBandwidthAndMaxCredit()
{
    this->reservedBandwidth = 0;
    unsigned long maxSingleStreamBandwidth = 0;
    for(std::vector<IEEE8021QciFilter*>::iterator it = streamFilters.begin(); it != streamFilters.end(); ++it)
    {
        IEEE8021QciFilter *streamFilter = *it;
        if (streamFilter->getMeterId() == static_cast<unsigned int>(this->getIndex()))
        {
            std::list<uint16_t> vids = this->srptable->getVidsForStreamId(streamFilter->getStreamId());
            for (std::list<uint16_t>::iterator it2 = vids.begin(); it2 != vids.end(); ++it2)
            {
                uint16_t vid = *it2;
                unsigned long streamBandwidth = this->srptable->getBandwidthForStream(streamFilter->getStreamId(), vid);
                this->reservedBandwidth += streamBandwidth;
                if (streamBandwidth > maxSingleStreamBandwidth)
                {
                    maxSingleStreamBandwidth = streamBandwidth;
                }
            }
        }
    }
    simtime_t maxDuration;
    if (this->srClass == SR_CLASS::A)
    {
        maxDuration = simtime_t{125, SIMTIME_US};
    }
    else if (this->srClass == SR_CLASS::B)
    {
        maxDuration = simtime_t{250, SIMTIME_US};
    }
    simtime_t duration = (maxSingleStreamBandwidth / inChannel->getNominalDatarate()) * maxDuration;
    this->maxCredit = static_cast<int>(ceil((inChannel->getNominalDatarate() - this->reservedBandwidth) * duration.dbl() * (this->maxBurst - 1)));
}

simtime_t CreditBasedMeter::calculateTransmissionDuration(inet::EtherFrame *frame)
{
    inet::EtherFrame *sizeFrame = frame->dup();
    sizeFrame->setByteLength(sizeFrame->getByteLength() + PREAMBLE_BYTES + SFD_BYTES + (INTERFRAME_GAP_BITS / 8));
    simtime_t frameDuration = inChannel->calculateDuration(sizeFrame);
    delete sizeFrame;
    return frameDuration;
}

simtime_t CreditBasedMeter::getCurrentTime()
{
    return this->getTimer()->getTotalSimTime();
}

void CreditBasedMeter::scheduleCreditReachZero()
{
    if (this->credit < 0)
    {
        simtime_t duration = simtime_t{static_cast<double>(abs(this->credit)) / this->reservedBandwidth};
        this->scheduleEvent(duration);
    }
}

void CreditBasedMeter::scheduleCreditReachMax()
{
    if (this->credit < this->maxCredit && credit >= 0)
    {
        simtime_t duration = simtime_t{static_cast<double>(maxCredit - credit) / this->reservedBandwidth};
        this->scheduleEvent(duration);
    }
}

void CreditBasedMeter::scheduleEvent(simtime_t duration)
{
    this->scheduleEvent(duration, "API Scheduler Task Event");

}

void CreditBasedMeter::scheduleEvent(simtime_t duration, const char *name)
{
    SchedulerTimerEvent *event = new SchedulerTimerEvent(name, TIMER_EVENT);
    event->setTimer(static_cast<uint64_t>(ceil(duration / this->getOscillator()->getPreciseTick())));
    event->setDestinationGate(gate("schedulerIn"));
    this->getTimer()->registerEvent(event);
}

void CreditBasedMeter::emitCredit()
{
    if (this->getCurrentTime() > this->lastEmitCredit)
    {
        this->emit(creditSignal, credit);
        this->lastEmitCredit = this->getCurrentTime();
    }
}

} //namespace
