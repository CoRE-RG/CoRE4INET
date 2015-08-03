//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "CoRE4INET_AVBBuffer.h"

//CoRE4INET
#include "CoRE4INET_ModuleAccess.h"

namespace CoRE4INET {

//Define_Module(AVBBuffer);

simsignal_t AVBBuffer::creditSignal = registerSignal("credit");

AVBBuffer::AVBBuffer()
{
    this->srClass = SR_CLASS_A;
    this->credit = 0;
    this->maxCredit = 0;
    this->inTransmission = false;
    this->newTime = 0;
    this->oldTime = 0;
    this->Wduration = 0;
    this->tick = -1;
    this->srptable = nullptr;
    this->portBandwith = 0;
}

AVBBuffer::~AVBBuffer()
{

}

int AVBBuffer::numInitStages() const
{
    return 1;
}

void AVBBuffer::initialize(int stage)
{
    Buffer::initialize(stage);

    if (stage == 0)
    {
        Timed::initialize();


        this->tick = getOscillator()->getPreciseTick();

        this->srptable = dynamic_cast<SRPTable*>(findModuleWhereverInNode("srpTable", getParentModule()));
        if (!this->srptable)
        {
            throw cRuntimeError("Cannot find srpTable");
        }

        if (cModule* phy = getParentModule()->getSubmodule("phy", getIndex()))
        {
            if (cModule* mac = phy->getSubmodule("mac"))
            {
                if (cGate * macOutGate = mac->gate("phys$o"))
                {
                    if (cChannel *outChannel = macOutGate->findTransmissionChannel())
                    {
                        this->portBandwith = static_cast<unsigned int>(ceil(outChannel->getNominalDatarate()));
                    }
                    else
                    {
                        this->portBandwith = 0;
                    }
                }
                else
                {
                    throw cRuntimeError("mac module of phy[%d] has no phys$o gate", getIndex());
                }
            }
            else
            {
                throw cRuntimeError("phy[%d] has no mac module", getIndex());
            }
        }
        else
        {
            throw cRuntimeError("Cannot find phy[%d]", getIndex());
        }

        this->newTime = simTime();
        this->oldTime = simTime();

        WATCH(credit);
        WATCH(maxCredit);
        WATCH(inTransmission);
        WATCH(newTime);
        WATCH(oldTime);
        WATCH(Wduration);
    }
}

void AVBBuffer::handleMessage(cMessage *msg)
{
    newTime = simTime();

    if (credit < 0)
    {
        idleSlope(newTime - oldTime);
    }

    if (msg->arrivedOn("in"))
    {
        Buffer::handleMessage(msg);
        if (inTransmission)
        {
            interferenceSlope(newTime - oldTime);
            if (credit > maxCredit)
                maxCredit = credit;
        }
        else
        {
            if (credit >= 0)
            {
                if (size() > 0)
                {
                    cMessage *outFrame = getFrame();
                    send(outFrame, "out");
                    inTransmission = true;
                }
                else
                {
                    resetCredit();
                }

            }
            else if (credit < 0)
            {
                unsigned long reservedBandwith = srptable->getBandwidthForModuleAndSRClass(
                        getParentModule()->getSubmodule("phy", getIndex()), srClass);
                Wduration = static_cast<double>(-credit) / static_cast<double>(reservedBandwith);
                SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
                event->setTimer(static_cast<uint64_t>(ceil(Wduration / tick)));
                event->setDestinationGate(gate("schedulerIn"));
                getTimer()->registerEvent(event);
            }
        }
    }
    else if (msg->arrivedOn("schedulerIn"))
    {
        if (inTransmission)
        {
            interferenceSlope(newTime - oldTime);
            if (credit > maxCredit)
                maxCredit = credit;
        }
        else
        {
            if (credit >= 0)
            {
                //if (msgCnt > 0)
                if (size() > 0)
                {
                    cMessage *outFrame = getFrame();
                    send(outFrame, "out");
                    inTransmission = true;
                }
                else
                {
                    resetCredit();
                }
            }
            else if (credit < 0)
            {
                //emit(creditSignal, credit);
                unsigned long reservedBandwith = srptable->getBandwidthForModuleAndSRClass(
                        getParentModule()->getSubmodule("phy", getIndex()), srClass);
                //When there is no bandwidth reserved reset credit and delete all messages
                if (reservedBandwith == 0)
                {
                    resetCredit();
                    clear();
                }
                else
                {
                    Wduration = static_cast<double>(-credit) / static_cast<double>(reservedBandwith);
                    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
                    event->setTimer(static_cast<uint64_t>(ceil(Wduration / tick)));
                    event->setDestinationGate(gate("schedulerIn"));
                    getTimer()->registerEvent(event);
                }
            }
        }
        delete msg;
    }

    if (newTime >= oldTime){
        oldTime = simTime();
        emit(creditSignal, credit);
    }
}

void AVBBuffer::handleParameterChange(const char* parname)
{
    Buffer::handleParameterChange(parname);
    Timed::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "srClass"))
    {
        if (strcmp(par("srClass").stringValue(), "A") == 0)
        {
            this->srClass = SR_CLASS_A;
        }
        else if (strcmp(par("srClass").stringValue(), "B") == 0)
        {
            this->srClass = SR_CLASS_B;
        }
        else
        {
            throw cRuntimeError("Parameter srClass of %s is %s and is only allowed to be A or B", getFullPath().c_str(),
                    par("srClass").stringValue());
        }
    }
}

void AVBBuffer::idleSlope(SimTime duration)
{
    if (duration >= 0)
    {
        Enter_Method
        ("idleSlope()");
        unsigned long reservedBandwith = srptable->getBandwidthForModuleAndSRClass(
                getParentModule()->getSubmodule("phy", getIndex()), srClass);

        credit += static_cast<int>(ceil(static_cast<double>(reservedBandwith) * duration.dbl()));
        if (credit > 0 && size() <= 0 && !inTransmission){
            resetCredit();
        }
    }
}

void AVBBuffer::interferenceSlope(SimTime duration)
{
    if (duration >= 0)
    {
        Enter_Method
        ("interferenceSlope()");
        unsigned long reservedBandwith = srptable->getBandwidthForModuleAndSRClass(
                getParentModule()->getSubmodule("phy", getIndex()), srClass);

        credit += static_cast<int>(ceil(static_cast<double>(reservedBandwith) * duration.dbl()));
    }
}

void AVBBuffer::sendSlope(SimTime duration)
{
    Enter_Method
    ("sendSlope()");

    if (duration < 0)
    {
        throw cRuntimeError("duration parameter is not allowed to become negative!");
    }

    unsigned long reservedBandwith = srptable->getBandwidthForModuleAndSRClass(
            getParentModule()->getSubmodule("phy", getIndex()), srClass);

    credit -= static_cast<int>(ceil(static_cast<double>(portBandwith - reservedBandwith) * duration.dbl()));
    inTransmission = false;
    if (size() > 0)
    {
        if (credit < 0)
        {
            Wduration = duration.dbl();
            SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
            event->setTimer(static_cast<uint64_t>(ceil(Wduration / tick)));
            event->setDestinationGate(gate("schedulerIn"));
            getTimer()->registerEvent(event);
        }
        else
        {
            cMessage *outFrame = getFrame();
            send(outFrame, "out");
            inTransmission = true;
        }
    }
    else if (credit > 0)
    {
        resetCredit();
    }
    // -- Only for credit vector statistic accuracy:
    else if (credit < 0)
    {
        Wduration = duration.dbl() + CBS_CREDITEMITSTRETCHTIME;
        SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
        event->setTimer(static_cast<uint64_t>(ceil(Wduration / tick)));
        event->setDestinationGate(gate("schedulerIn"));
        getTimer()->registerEvent(event);
    }
    // --

    if (oldTime <= simTime())
        oldTime = simTime() + duration;
    else
        oldTime = oldTime + duration;
}

void AVBBuffer::refresh()
{
    newTime = simTime();

    if (credit < 0)
    {
        idleSlope(newTime - oldTime);
    }

    if (inTransmission)
    {
        interferenceSlope(newTime - oldTime);
        if (credit > maxCredit)
            maxCredit = credit;
    }

    if (newTime >= oldTime){
        oldTime = simTime();
        emit(creditSignal, credit);
    }
}

int AVBBuffer::getCredit() const
{
    return credit;
}

void AVBBuffer::resetCredit()
{
    Enter_Method
    ("resetCredit");

    if (newTime >= oldTime)
    {
        credit = 0;
        emit(creditSignal, credit);
    }
}

} /* namespace CoRE4INET */
