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

#include "CoRE4INET_RCIncoming.h"

//INET
#include "EtherFrame_m.h"

namespace CoRE4INET {

Define_Module(RCIncoming);

RCIncoming::RCIncoming() :
        CTIncoming::CTIncoming()
{
    lastArrived = 0;
    bag = 0;
    jitter = 0;
    firstMessage = true;
}

void RCIncoming::initialize()
{
    Timed::initialize();
}

void RCIncoming::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        recordPacketReceived((inet::EtherFrame*) msg);

        uint64_t currentTotalTicks = timer->getTotalTicks();
        //Now check for correct arrival:
        //Check too early
        if (!firstMessage && ((currentTotalTicks - lastArrived) < (bag - jitter)))
        {
            emit(droppedSignal, (inet::EtherFrame*) msg);
            if (ev.isGUI())
            {
                ev.printf("Received frame in %s too early! Gap was %d Ticks, should have been between minimum %d! \n",
                        getName(), currentTotalTicks - lastArrived, par("bag").longValue());
                bubble("Frame to early");
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
            }

            delete msg;
        }
        //Timing ok
        else
        {
            lastArrived = currentTotalTicks;
            sendDelayed(msg, SimTime(getParentModule()->par("hardware_delay").doubleValue()), "out");
        }
    }
}

void RCIncoming::handleParameterChange(__attribute((unused)) const char* parname)
{
    bag = (uint64_t) par("bag").longValue();
    jitter = (uint64_t) par("jitter").longValue();
}

} //namespace
