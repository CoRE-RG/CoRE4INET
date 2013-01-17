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
#include "TTEApplicationBase.h"

namespace TTEthernetModel {

Define_Module( RCBuffer);

RCBuffer::RCBuffer()
{
    bagExpired = true;
    timerMessage = new SchedulerTimerEvent("RCBuffer Scheduler Event", TIMER_EVENT);
}

RCBuffer::~RCBuffer()
{
    cancelEvent(timerMessage);
    delete timerMessage;
}

int RCBuffer::numInitStages() const
{
    if(CTBuffer::numInitStages()>1)
        return CTBuffer::numInitStages();
    else
        return 1;
}

void RCBuffer::initialize(int stage)
{
    CTBuffer::initialize(stage);
    if(stage==0){
        timerMessage->setDestinationGate(gate("schedulerIn"));

        //Update displaystring
        setIsEmpty(true);
    }
}

void RCBuffer::handleMessage(cMessage *msg)
{
    CTBuffer::handleMessage(msg);

    if(destinationGates.size() > 0)
    {
        if (msg->arrivedOn("in"))
        {
            if (bagExpired)
            {
                cMessage *outgoingMessage = getFrame();
                if(outgoingMessage){
                    bagExpired = false;
                    numReset = 0;
                    //Send Message
                    for (std::list<cGate*>::iterator dgate = destinationGates.begin(); dgate != destinationGates.end(); ++dgate)
                    {
                        sendDirect(outgoingMessage->dup(),0,0, *dgate);
                    }
                    if(gate("out")->isConnected()){
                        send(outgoingMessage->dup(),"out");
                    }
                    recordPacketSent();
                    delete outgoingMessage;
                }
            }
        }
        else if (msg->arrivedOn("schedulerIn") && msg->getKind() == TIMER_EVENT)
        {
            cMessage *outgoingMessage = getFrame();
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
            }
        }
    }
}

void RCBuffer::handleParameterChange(const char* parname){
    CTBuffer::handleParameterChange(parname);

    timerMessage->setTimer(par("bag").doubleValue());
}

void RCBuffer::resetBag()
{
    Enter_Method("resetBag()");
    //This is the moment when the message was transmitted execute transmit callbacks if there are some
    for(std::map<TTEApplicationBase*,Callback*>::const_iterator iter = transmitCallbacks.begin();
            iter != transmitCallbacks.end(); ++iter){
        iter->first->executeCallback(iter->second);
    }

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
