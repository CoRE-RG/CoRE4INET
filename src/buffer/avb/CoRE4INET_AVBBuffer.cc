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
#include "CoRE4INET_SRPTable.h"
//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

//Define_Module(AVBBuffer);

simsignal_t AVBBuffer::creditSignal = registerSignal("credit");

AVBBuffer::AVBBuffer()
{

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

        tick = findModuleWhereverInNode("oscillator", getParentModule())->par("tick").doubleValue();

        credit = 0;
        maxCredit = 0;
        inTransmission = false;
        newTime = simTime();
        oldTime = simTime();
        Wduration = 0;

        WATCH(credit);
        WATCH(maxCredit);
        WATCH(inTransmission);
        WATCH(Wduration);
    }
}

void AVBBuffer::handleMessage(cMessage *msg)
{
    Buffer::handleMessage(msg);

    newTime = simTime();

    if (credit < 0)
    {
        idleSlope(newTime - oldTime);
    }

    if (msg->arrivedOn("in"))
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
                SRPTable *srptable = check_and_cast<SRPTable*>(getParentModule()->getSubmodule("srpTable"));
                unsigned long reservedBandwith = srptable->getBandwidthForModule(
                        getParentModule()->getSubmodule("phy", getIndex()));
                Wduration = ((double) -credit) / reservedBandwith;
                SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
                event->setTimer((uint64_t) ceil(Wduration / tick));
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
                emit(creditSignal, credit);
                SRPTable *srptable = check_and_cast<SRPTable*>(getParentModule()->getSubmodule("srpTable"));
                unsigned long reservedBandwith = srptable->getBandwidthForModule(
                        getParentModule()->getSubmodule("phy", getIndex()));
                //When there is no bandwidth reserved reset credit and delete all messages
                if (reservedBandwith == 0)
                {
                    resetCredit();
                    clear();
                }
                else
                {
                    Wduration = ((double) -credit) / reservedBandwith;
                    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
                    event->setTimer((uint64_t) ceil(Wduration / tick));
                    event->setDestinationGate(gate("schedulerIn"));
                    getTimer()->registerEvent(event);
                }
            }
        }
        delete msg;
    }

    if (newTime >= oldTime)
        oldTime = simTime();
}

void AVBBuffer::handleParameterChange(const char* parname)
{
    Buffer::handleParameterChange(parname);
}

void AVBBuffer::idleSlope(SimTime duration)
{
    if (duration >= 0)
    {
        Enter_Method
        ("idleSlope()");
        SRPTable *srptable = check_and_cast<SRPTable*>(getParentModule()->getSubmodule("srpTable"));
        unsigned long reservedBandwith = srptable->getBandwidthForModule(
                getParentModule()->getSubmodule("phy", getIndex()));

        credit += ceil(reservedBandwith * duration.dbl());
        emit(creditSignal, credit);
        if (credit > 0 && size() == 0 && !inTransmission)
            resetCredit();
    }
}

void AVBBuffer::interferenceSlope(SimTime duration)
{
    if (duration >= 0)
    {
        Enter_Method
        ("interferenceSlope()");
        SRPTable *srptable = check_and_cast<SRPTable*>(getParentModule()->getSubmodule("srpTable"));
        unsigned long reservedBandwith = srptable->getBandwidthForModule(
                getParentModule()->getSubmodule("phy", getIndex()));

        credit += ceil(reservedBandwith * duration.dbl());
        emit(creditSignal, credit);
    }
}

void AVBBuffer::sendSlope(SimTime duration)
{
    Enter_Method
    ("sendSlope()");
    SRPTable *srptable = check_and_cast<SRPTable*>(getParentModule()->getSubmodule("srpTable"));
    unsigned long reservedBandwith = srptable->getBandwidthForModule(
            getParentModule()->getSubmodule("phy", getIndex()));

    cGate *physOutGate = getParentModule()->getSubmodule("phy", getIndex())->getSubmodule("mac")->gate("phys$o");
    cChannel *outChannel = physOutGate->findTransmissionChannel();

    unsigned int portBandwith = outChannel->getNominalDatarate();
    emit(creditSignal, credit);
    credit -= ceil((portBandwith - reservedBandwith) * duration.dbl());
    inTransmission = false;
    if (size() > 0)
    {
        if (credit < 0)
        {
            Wduration = duration.dbl();
            SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
            event->setTimer((uint64_t) ceil(Wduration / tick));
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

    if (newTime >= oldTime)
        oldTime = simTime();
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
