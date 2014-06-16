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

namespace CoRE4INET {

//Define_Module(RCBuffer);

RCBuffer::RCBuffer()
{
    bagExpired = true;
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
        if (msg->arrivedOn("in"))
        {
            if (bagExpired)
            {
                if (EtherFrame *outgoingMessage = getFrame())
                {
                    bagExpired = false;
                    numReset = 0;
                    //Send Message
                    for (std::list<cGate*>::const_iterator dgate = destinationGates.begin(); dgate != destinationGates.end();
                            ++dgate)
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
        else if (msg->arrivedOn("schedulerIn") && msg->getKind() == TIMER_EVENT)
        {
            if (EtherFrame *outgoingMessage = getFrame())
            {
                bagExpired = false;
                numReset = 0;
                //Send Message
                for (std::list<cGate*>::const_iterator gate = destinationGates.begin(); gate != destinationGates.end();
                        ++gate)
                {
                    sendDirect(outgoingMessage->dup(), *gate);
                }
                recordPacketSent(outgoingMessage);
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
        //Register scheduler
        SchedulerTimerEvent *timerMessage = new SchedulerTimerEvent("RCBuffer Scheduler Event", TIMER_EVENT);
        timerMessage->setTimer((uint64_t) par("bag").longValue());
        timerMessage->setDestinationGate(gate("schedulerIn"));
        timer->registerEvent(timerMessage);
    }
}

long RCBuffer::getRequiredBandwidth()
{
    return (par("maxMessageSize").longValue() * 8)
            * (1 / ((uint64_t) par("bag").longValue() * oscillator->par("tick").doubleValue()));
}

} //namespace
