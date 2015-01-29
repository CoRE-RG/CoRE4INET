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

//CoRE4INET
#include "CoRE4INET_AS6802Defs.h"
#include "CoRE4INET_ConfigFunctions.h"

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
        if (EtherFrame *etherframe = dynamic_cast<EtherFrame *>(msg))
        {
            recordPacketReceived(etherframe);

            uint64_t currentTotalTicks = getTimer()->getTotalTicks();
            //Now check for correct arrival:
            //Check too early
            if (!firstMessage && ((currentTotalTicks - lastArrived) < (bag - jitter)))
            {
                emit(droppedSignal, etherframe);
                if (ev.isGUI())
                {
                    ev.printf(
                            "Received frame in %s too early! Gap was %d Ticks, should have been between minimum %d! \n",
                            getName(), currentTotalTicks - lastArrived, bag);
                    bubble("Frame to early");
                    getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                }

                delete etherframe;
            }
            //Timing ok
            else
            {
                lastArrived = currentTotalTicks;
                sendDelayed(etherframe, getHardwareDelay(), "out");
            }
        }
    }
    else
    {
        throw cRuntimeError("Received non-Ethernet frame");
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuseless-cast"

void RCIncoming::handleParameterChange(const char* parname)
{
    CTIncoming::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "bag"))
    {
        this->bag = static_cast<uint64_t>(parameterULongCheckRange(par("bag"), 0, MAX_BAG_TICKS));
    }
    if (!parname || !strcmp(parname, "jitter"))
    {
        this->jitter = static_cast<uint64_t>(parameterULongCheckRange(par("jitter"), 0, MAX_JITTER_TICKS));
    }
}

#pragma GCC diagnostic pop

} //namespace
