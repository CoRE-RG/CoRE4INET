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

#include "core4inet/incoming/AS6802/RCIncoming.h"

//CoRE4INET
#include "core4inet/base/AS6802/AS6802Defs.h"
#include "core4inet/utilities/ConfigFunctions.h"

//INET
#include "inet/linklayer/ethernet/EtherFrame_m.h"

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
        if (inet::EtherFrame *etherframe = dynamic_cast<inet::EtherFrame *>(msg))
        {
            recordPacketReceived(etherframe);

            uint64_t currentTotalTicks = getTimer()->getTotalTicks();
            //Now check for correct arrival:
            //Check too early
            if (!firstMessage && ((currentTotalTicks - lastArrived) < (bag - jitter)))
            {
                emit(droppedSignal, etherframe);
                EV_ERROR << "Received frame in " << getName() << " too early! Gap was " << (currentTotalTicks - lastArrived) << " Ticks, should have been between minimum " << bag << "!" << endl;
                if (getEnvir()->isGUI())
                {

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

void RCIncoming::handleParameterChange(const char* parname)
{
    CTIncoming::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "bag"))
    {
#if LONG_BIT == 32
        this->bag = static_cast<uint64_t>(parameterULongCheckRange(par("bag"), 0, MAX_BAG_TICKS));
#else
        this->bag = parameterULongCheckRange(par("bag"), 0, MAX_BAG_TICKS);
#endif
    }
    if (!parname || !strcmp(parname, "jitter"))
    {
#if LONG_BIT == 32
        this->jitter = static_cast<uint64_t>(parameterULongCheckRange(par("jitter"), 0, MAX_JITTER_TICKS));
#else
        this->jitter = parameterULongCheckRange(par("jitter"), 0, MAX_JITTER_TICKS);
#endif
    }
}


} //namespace
