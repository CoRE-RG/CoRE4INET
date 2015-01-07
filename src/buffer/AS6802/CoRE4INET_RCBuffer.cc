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

#include "CoRE4INET_RCBuffer.h"

//Auto-generated Messages
#include "CTFrame_m.h"
#include "scheduler/SchedulerMessageEvents_m.h"

//CoRE4INET
#include "CoRE4INET_AS6802Defs.h"
#include "CoRE4INET_ConfigFunctions.h"

namespace CoRE4INET {

//Define_Module(RCBuffer);

RCBuffer::RCBuffer()
{
    this->bagExpired = true;
    this->lastSent = 0;
    this->bag = 0;
    this->jitter = 0;
    this->numReset = 0;
}

RCBuffer::~RCBuffer()
{
}

int RCBuffer::numInitStages() const
{
    if (CTBuffer::numInitStages() > 1)
        return CTBuffer::numInitStages();
    else
        return 1;
}

void RCBuffer::initialize(int stage)
{
    CTBuffer::initialize(stage);
    if (stage == 0)
    {
        Timed::initialize();
    }
}

void RCBuffer::handleMessage(cMessage *msg)
{
    CTBuffer::handleMessage(msg);

    if (destinationGates.size() > 0)
    {
        if (msg && msg->arrivedOn("in"))
        {
            if (bagExpired)
            {
                if (EtherFrame *outgoingMessage = getFrame())
                {
                    bagExpired = false;
                    numReset = 0;
                    //Send Message
                    for (std::list<cGate*>::const_iterator dgate = destinationGates.begin();
                            dgate != destinationGates.end(); ++dgate)
                    {
                        sendDirect(outgoingMessage->dup(), 0, 0, *dgate);
                    }
                    if (gate("out")->isConnected())
                    {
                        send(outgoingMessage->dup(), "out");
                    }
                    recordPacketSent(outgoingMessage);
                    delete outgoingMessage;
                }
            }
        }
        else if (msg && msg->arrivedOn("schedulerIn") && msg->getKind() == TIMER_EVENT)
        {
            if (EtherFrame *outgoingMessage = getFrame())
            {
                bagExpired = false;
                numReset = 0;
                //Send Message
                for (std::list<cGate*>::const_iterator gate_it = destinationGates.begin(); gate_it != destinationGates.end();
                        ++gate_it)
                {
                    sendDirect(outgoingMessage->dup(), *gate_it);
                }
                recordPacketSent(outgoingMessage);
                lastSent = getTimer()->getTotalTicks();
                delete outgoingMessage;
            }
            else
            {
                bagExpired = true;
                if (ev.isGUI())
                {
                    getDisplayString().setTagArg("i2", 0, "");
                }
            }
            delete msg;
        }
    }

}

void RCBuffer::handleParameterChange(const char* parname)
{
    CTBuffer::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "bag"))
    {
        this->bag = static_cast<uint64_t>(parameterULongCheckRange(par("bag"), 0, MAX_BAG));
    }
    if (!parname || !strcmp(parname, "jitter"))
    {
        this->jitter = static_cast<uint64_t>(parameterULongCheckRange(par("jitter"), 0, MAX_JITTER));
    }
}

void RCBuffer::resetBag()
{
    Enter_Method
    ("resetBag()");

    //Set icon:
    if (ev.isGUI())
    {
        getDisplayString().setTagArg("i2", 0, "status/hourglass");
    }

    numReset++;
    if (numReset == destinationGates.size())
    {
        //Jitter calculations: fo frame delay
        uint64_t delay = getTimer()->getTotalTicks() - lastSent;
        //If last frame was delayed more than jitter parameter set delay to jitter
        if (delay > jitter)
        {
            delay = jitter;
        }

        //Register scheduler
        SchedulerTimerEvent *timerMessage = new SchedulerTimerEvent("RCBuffer Scheduler Event", TIMER_EVENT);
        //Subtract delay from bag to allow frames to keep up their bandwidth
        if (bag < delay)
        {
            timerMessage->setTimer(0);
        }
        else
        {
            timerMessage->setTimer(bag - delay);
        }
        timerMessage->setDestinationGate(gate("schedulerIn"));
        getTimer()->registerEvent(timerMessage);
    }
}

long RCBuffer::getRequiredBandwidth()
{
    return static_cast<long>(ceil(
            static_cast<double>(getMaxMessageSize() * 8) * (1 / (static_cast<double>(this->bag) * getOscillator()->getPreciseTick()))));
}

} //namespace
