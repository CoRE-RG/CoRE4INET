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

#include "RCBuffer.h"
#include <CTFrame_m.h>
#include <TTEScheduler.h>

namespace TTEthernetModel {

Define_Module( RCBuffer);

RCBuffer::RCBuffer()
{
    bagExpired = true;
}

RCBuffer::~RCBuffer()
{
    delete timerMessage;
}

void RCBuffer::initialize()
{
    timerMessage = new SchedulerTimerEvent("RCBuffer Scheduler Event", TIMER_EVENT);
    timerMessage->setDestinationGate(gate("schedulerIn"));
    timerMessage->setTimer(par("bag"));

    //Update displaystring
    setIsEmpty(true);
}

void RCBuffer::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (bagExpired)
        {
            bagExpired = false;
            numReset = 0;
            //Send Message
            for (std::list<cGate*>::iterator gate = destinationGates.begin(); gate != destinationGates.end(); ++gate)
            {
                sendDirect(msg->dup(), *gate);
            }
            recordPacketSent();
            delete msg;
        }
        else
        {
            enqueue((EtherFrame*) msg);
        }
    }

    if (msg->arrivedOn("schedulerIn") && msg->getKind() == TIMER_EVENT)
    {
        cMessage *outgoingMessage = dequeue();
        if (outgoingMessage)
        {
            bagExpired = false;
            numReset = 0;
            //Send Message
            for (std::list<cGate*>::iterator gate = destinationGates.begin(); gate != destinationGates.end(); ++gate)
            {
                sendDirect(outgoingMessage->dup(), *gate);
            }
            recordPacketSent();
            delete outgoingMessage;
        }
        else
        {
            bagExpired = true;
            getDisplayString().setTagArg("i2", 0, "");
            delete msg;
        }
    }
}

void RCBuffer::resetBag()
{
    Enter_Method("resetBag()");
    //Set icon:
    getDisplayString().setTagArg("i2", 0, "status/hourglass");

    numReset++;
    if (numReset == destinationGates.size())
    {
        //Reregister scheduler
        TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
        tteScheduler->registerEvent(timerMessage);
    }
}

} //namespace
