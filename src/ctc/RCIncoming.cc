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

#include "RCIncoming.h"

#include <TTEScheduler.h>

namespace TTEthernetModel {

Define_Module(RCIncoming);


RCIncoming::RCIncoming()
{
    lastArrived=0;
}

void RCIncoming::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        TTEScheduler *tteScheduler = (TTEScheduler*)getParentModule()->getSubmodule("tteScheduler");
        unsigned long currentTotalTicks = tteScheduler->getTotalTicks();
        //Now check for correct arrival:
        //TODO what todo with JITTER?
        //Check too early
        if(currentTotalTicks-lastArrived < bag){
            ev.printf("Received frame in %s too early! Gap was %d Ticks, should have been between minimum %d! \n", getName(), currentTotalTicks-lastArrived,par("bag").longValue());
            bubble("Frame to early");
            emit(ctDroppedSignal, 1);
            getDisplayString().setTagArg("i2", 0, "status/excl3");
            delete msg;
        }
        //Timing ok
        else{
            lastArrived=currentTotalTicks;
            send(msg,"out");
        }
    }
}

void RCIncoming::handleParameterChange(const char* parname){
    bag = (unsigned long)par("bag").longValue();
}

} //namespace
