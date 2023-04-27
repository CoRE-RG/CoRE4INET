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

#include "CreditBasedShaper.h"

//INET
#include "inet/linklayer/ethernet/Ethernet.h"

//INET
#include "inet/common/ModuleAccess.h"

namespace CoRE4INET {

Define_Module(CreditBasedShaper);

simsignal_t CreditBasedShaper::creditSignal = registerSignal("credit");

CreditBasedShaper::CreditBasedShaper()
{
    this->credit = 0;
    this->isScheduled = false;
    this->queueSize = 0;
    this->previousQueueSize = 0;
    this->newTime = 0;
    this->oldTime = 0;
    this->portBandwidth = 0;
}

bool CreditBasedShaper::isOpen()
{
    this->idleSlope(this->queueSize == 0);
    return IEEE8021QbvSelectionAlgorithm::isOpen();
}

void CreditBasedShaper::initialize()
{
    IEEE8021QbvSelectionAlgorithm::initialize();
    Timed::initialize();
    this->getParentModule()->getSubmodule("queue", this->getIndex())->subscribe("size", this);
    this->getParentModule()->getParentModule()->subscribe("transmitState", this);
    this->srpTable = inet::getModuleFromPar<SRPTable>(par("srpTable"), this, true);
    this->outChannel = this->getParentModule()->getParentModule()->getSubmodule("mac")->gate("phys$o")->findTransmissionChannel();
    this->portBandwidth = static_cast<unsigned int>(ceil(outChannel->getNominalDatarate()));
    WATCH(this->credit);
    WATCH(this->queueSize);
    WATCH(this->portBandwidth);
}

void CreditBasedShaper::handleParameterChange(const char* parname)
{
    IEEE8021QbvSelectionAlgorithm::handleParameterChange(parname);
    Timed::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "srClass"))
    {
        if (strcmp(par("srClass").stringValue(), "A") == 0)
        {
            this->srClass = SR_CLASS::A;
        }
        else if (strcmp(par("srClass").stringValue(), "B") == 0)
        {
            this->srClass = SR_CLASS::B;
        }
        else
        {
            throw cRuntimeError("Parameter srClass of %s is %s and is only allowed to be A or B", getFullPath().c_str(),
                    par("srClass").stringValue());
        }
    }
}

void CreditBasedShaper::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("schedulerIn"))
    {
        this->isScheduled = false;
        this->idleSlope(this->queueSize == 0);
    }
    delete msg;
}

void CreditBasedShaper::receiveSignal(__attribute__ ((unused)) cComponent *source, simsignal_t signalID, long l, __attribute__ ((unused)) cObject *details)
{
    if (strncmp(getSignalName(signalID), "transmitState", 14) == 0)
    {
        inet::EtherMACBase::MACTransmitState macTransmitState = static_cast<inet::EtherMACBase::MACTransmitState>(l);
        if (macTransmitState == inet::EtherMACBase::MACTransmitState::TX_IDLE_STATE)
        {
            this->idleSlope(this->queueSize == 0);
        }
    }
}

void CreditBasedShaper::receiveSignal(__attribute__ ((unused)) cComponent *source, simsignal_t signalID, unsigned long l, __attribute__ ((unused)) cObject *details)
{
    if (strncmp(getSignalName(signalID), "size", 18) == 0)
    {
        this->previousQueueSize = this->queueSize;
        this->queueSize = l;
        // Frame arrived in queue
        if (this->queueSize > this->previousQueueSize)
        {
            this->idleSlope(previousQueueSize == 0);
        }
        // Frame forwarded from queue
        if (this->queueSize < this->previousQueueSize)
        {
            cPacket* sizeMsg = new cPacket();
            sizeMsg->setByteLength((this->previousQueueSize - this->queueSize) + PREAMBLE_BYTES + SFD_BYTES + (INTERFRAME_GAP_BITS / 8));
            this->sendSlope(this->outChannel->calculateDuration(sizeMsg));
            delete sizeMsg;
        }
    }
}

void CreditBasedShaper::idleSlope(bool maxCreditZero)
{
    this->newTime = this->getCurrentTime();
    simtime_t duration = this->newTime - this->oldTime;
    unsigned long reservedBandwidth = this->srpTable->getBandwidthForModuleAndSRClass(this->getParentModule()->getParentModule(), this->srClass);
    if (reservedBandwidth > 0)
    {
        if (duration > 0)
        {
            this->credit += static_cast<int>(ceil(static_cast<double>(reservedBandwidth) * duration.dbl()));
            if (maxCreditZero && this->credit > 0)
            {
                this->credit = 0;
            }
            this->oldTime = this->getCurrentTime();
            this->refreshState();
        }
        if (duration >= 0 - getOscillator()->getCurrentTick())
        {
            emit(this->creditSignal, this->credit);
        }
        if (this->credit < 0 && !(this->isScheduled))
        {
            double tillZeroDuration = static_cast<double>(-credit) / static_cast<double>(reservedBandwidth);
            SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
            event->setTimer(static_cast<uint64_t>(ceil(tillZeroDuration / getOscillator()->getPreciseTick())));
            event->setDestinationGate(gate("schedulerIn"));
            getTimer()->registerEvent(event);
            this->isScheduled = true;
        }
    }
}

void CreditBasedShaper::sendSlope(simtime_t duration)
{
    if (duration > 0)
    {
        unsigned long reservedBandwidth = this->srpTable->getBandwidthForModuleAndSRClass(this->getParentModule()->getParentModule(), this->srClass);
        credit -= static_cast<int>(ceil(static_cast<double>(this->portBandwidth - reservedBandwidth) * duration.dbl()));
        this->oldTime = this->getCurrentTime() + duration;
        this->refreshState();
        if (!(this->isScheduled))
        {
            SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
            event->setTimer(static_cast<uint64_t>(ceil(duration / getOscillator()->getPreciseTick())));
            event->setDestinationGate(gate("schedulerIn"));
            getTimer()->registerEvent(event);
            this->isScheduled = true;
        }
    }
}

simtime_t CreditBasedShaper::getCurrentTime()
{
    return getTimer()->getTotalSimTime();
}

void CreditBasedShaper::refreshState()
{
    if (credit < 0)
    {
        this->close();
    }
    else
    {
        this->open();
    }
}

} //namespace
