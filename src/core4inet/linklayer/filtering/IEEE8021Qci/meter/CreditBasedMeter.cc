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

void CreditBasedMeter::initialize()
{
    IEEE8021QciMeter::initialize();
    Timed::initialize();
    inet::EtherMACFullDuplex* mac =  dynamic_cast<inet::EtherMACFullDuplex*>(this->getParentModule()->getParentModule()->getSubmodule("mac"));
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
        IEEE8021QciCtrl *ctrl = dynamic_cast<IEEE8021QciCtrl*>(msg);
        if (!ctrl)
        {
            throw cRuntimeError("No filtering ctrl header");
        }
        cPacket *data = ctrl->decapsulate();
        if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(data))
        {
            this->refreshReservedBandwidthAndMaxCredit();
            this->idleSlope(frame);
            this->refreshState();
            this->meter(frame);
        }
        else
        {
            throw cRuntimeError("Encapsulated packet of received message on gate in that is no EtherFrame");
        }
        delete ctrl;
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

void CreditBasedMeter::idleSlope(inet::EtherFrame *frame)
{
    SimTime currentTime = this->getCurrentTime();
    SimTime transmissionDuration = calculateTransmissionDuration(frame);
    SimTime incomingTime = currentTime - transmissionDuration;
    SimTime idleDuration = incomingTime - lastCalcTime;
    this->credit += static_cast<int>(ceil(this->reservedBandwidth * idleDuration.dbl()));
    if (this->credit > this->maxCredit)
    {
        this->credit = this->maxCredit;
    }
    this->lastCalcTime = incomingTime;
}

void CreditBasedMeter::sendSlope(inet::EtherFrame *frame)
{
    SimTime currentTime = this->getCurrentTime();
    SimTime transmissionDuration = calculateTransmissionDuration(frame);
    this->credit -= static_cast<int>(ceil((inChannel->getNominalDatarate() - this->reservedBandwidth) * transmissionDuration.dbl()));
    this->lastCalcTime = currentTime;
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
        IEEE8021QciMeter::handleMessage(frame);
        this->sendSlope(frame);
        this->refreshState();
    }
    else if (this->state == this->State::R_RF)
    {
        delete frame;
    }
}

void CreditBasedMeter::refreshReservedBandwidthAndMaxCredit()
{
    this->reservedBandwidth = 0;
    unsigned long maxSingleStreamBandwidth = 0;
    for(std::vector<IEEE8021QciFilter*>::iterator it = streamFilters.begin(); it != streamFilters.end(); ++it)
    {
        IEEE8021QciFilter *streamFilter = *it;
        if (streamFilter->getMeterID() == static_cast<unsigned int>(this->getIndex()))
        {
            unsigned long streamBandwidth = this->srptable->getBandwidthForStream(streamFilter->getStreamID());
            this->reservedBandwidth += streamBandwidth;
            if (streamBandwidth > maxSingleStreamBandwidth)
            {
                maxSingleStreamBandwidth = streamBandwidth;
            }
        }
    }
    SimTime maxDuration;
    if (this->srClass == SR_CLASS::A)
    {
        maxDuration = SimTime{125, SIMTIME_US};
    }
    else if (this->srClass == SR_CLASS::B)
    {
        maxDuration = SimTime{250, SIMTIME_US};
    }
    SimTime duration = (maxSingleStreamBandwidth / inChannel->getNominalDatarate()) * maxDuration;
    this->maxCredit = static_cast<int>(ceil((inChannel->getNominalDatarate() - this->reservedBandwidth) * duration.dbl() * (this->maxBurst - 1)));
}

SimTime CreditBasedMeter::calculateTransmissionDuration(inet::EtherFrame *frame)
{
    inet::EtherFrame *sizeFrame = frame->dup();
    sizeFrame->setByteLength(sizeFrame->getByteLength() + PREAMBLE_BYTES + SFD_BYTES + (INTERFRAME_GAP_BITS / 8));
    SimTime frameDuration = inChannel->calculateDuration(sizeFrame);
    delete sizeFrame;
    return frameDuration;
}

SimTime CreditBasedMeter::getCurrentTime()
{
    return this->getTimer()->getTotalSimTime();
}

} //namespace
