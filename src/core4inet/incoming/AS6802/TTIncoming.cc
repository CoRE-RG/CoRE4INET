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

#include "core4inet/incoming/AS6802/TTIncoming.h"

//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

//INET
#include "inet/common/ModuleAccess.h"
//Auto-generated Messages
#include "core4inet/scheduler/SchedulerMessageEvents_m.h"

namespace CoRE4INET {

Define_Module(TTIncoming);

TTIncoming::TTIncoming() :
        CTIncoming::CTIncoming()
{
    this->frame = nullptr;
    this->receive_window_start = 0;
    this->receive_window_end = 0;
    this->permanence_pit = 0;
}

TTIncoming::~TTIncoming()
{
    if (frame != nullptr)
    {
        delete frame;
    }
}

void TTIncoming::initialize()
{
    Scheduled::initialize();
}

void TTIncoming::handleMessage(cMessage *msg)
{
    //Incoming Message
    if (msg && msg->arrivedOn("in"))
    {
        if (inet::EtherFrame *etherframe = dynamic_cast<inet::EtherFrame *>(msg))
        {
            recordPacketReceived(etherframe);

            //get current time in cylce
            uint32_t currentTicks = getPeriod()->getTicks();
            //Now check for correct arrival:
            if (frame != nullptr)
            {
                emit(droppedSignal, etherframe);
                hadError = true;
                EV_ERROR << "Received frame before permanence point of previous frame" << endl;
                if (getEnvir()->isGUI())
                {

                    bubble("Received frame before permanence point of previous frame");
                    getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getDisplayString().setTagArg("tt", 0,
                            "WARNING: Received frame before permanence point of previous frame");
                    getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getDisplayString().setTagArg("tt", 0, "Problem with Buffer");
                }
                delete etherframe;
            }
            //Check too early
            else if (receive_window_start > 0 && currentTicks < static_cast<uint32_t>(receive_window_start))
            {
                emit(droppedSignal, etherframe);
                hadError = true;
                EV_ERROR << "Received frame in " << getName() << " too early! Receive Time was " << currentTicks << " Ticks, should have been between " << receive_window_start << " and " << receive_window_end << "!" << endl;
                if (getEnvir()->isGUI())
                {

                    bubble("Frame to early");
                    getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getDisplayString().setTagArg("tt", 0,
                            "WARNING: Buffer configuration problem - Received frame too early");
                    getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getDisplayString().setTagArg("tt", 0,
                            "WARNING: Buffer configuration problem - Received frame too early");
                }
                delete etherframe;
            }
            //Check too late
            else if (receive_window_end > 0 && currentTicks > static_cast<uint32_t>(receive_window_end))
            {
                emit(droppedSignal, etherframe);
                hadError = true;
                EV_ERROR <<"Received frame in " << getName() << " too late! Receive Time was " << currentTicks << " Ticks, should have been between " << receive_window_start << " and " << receive_window_end << "!" << endl;
                if (getEnvir()->isGUI())
                {

                    bubble("Frame to late");
                    getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getDisplayString().setTagArg("tt", 0,
                            "WARNING: Buffer configuration problem - Received frame too late");
                    getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getDisplayString().setTagArg("tt", 0,
                            "WARNING: Buffer configuration problem - Received frame too late");
                }
                delete etherframe;
            }
            //Timing ok
            else
            {
                //delay for permanence_pit if set
                if (permanence_pit > 0)
                {
                    if (!hadError && getEnvir()->isGUI())
                        getDisplayString().setTagArg("i2", 0, "status/hourglass");
                    frame = etherframe;
                    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("PIT Event", ACTION_TIME_EVENT);
                    event->setAction_time(static_cast<uint32_t>(permanence_pit));
                    event->setDestinationGate(gate("schedulerIn"));
                    getPeriod()->registerEvent(event);
                }
                else
                {
                    sendDelayed(etherframe, getHardwareDelay(), "out");
                }
            }
        }
        else
        {
            throw cRuntimeError("Received non-Ethernet frame");
        }
    }
    else if (msg && msg->arrivedOn("schedulerIn") && msg->getKind() == ACTION_TIME_EVENT)
    {
        if(!frame)
        {
            throw cRuntimeError("Received schedule event for a non-existing frame");
        }
        delete msg;
        if (!hadError && getEnvir()->isGUI())
            getDisplayString().removeTag("i2");
        sendDelayed(frame, getHardwareDelay(), "out");
        frame = nullptr;
    }

}

void TTIncoming::handleParameterChange(const char* parname)
{
    CTIncoming::handleParameterChange(parname);
    Scheduled::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "receive_window_start"))
    {
        this->receive_window_start = parameterLongCheckRange(par("receive_window_start"), -1, static_cast<long>(getPeriod()->getCycleTicks()));
    }
    if (!parname || !strcmp(parname, "receive_window_end"))
    {
        this->receive_window_end = parameterLongCheckRange(par("receive_window_end"), -1, static_cast<long>(getPeriod()->getCycleTicks()));
    }
    if (!parname || !strcmp(parname, "permanence_pit"))
    {
        this->permanence_pit = parameterLongCheckRange(par("permanence_pit"), -1, static_cast<long>(getPeriod()->getCycleTicks()));
    }

}

} //namespace
