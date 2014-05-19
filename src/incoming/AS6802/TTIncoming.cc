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

#include "TTIncoming.h"

#include "ModuleAccess.h"
#include "scheduler/SchedulerMessageEvents_m.h"

namespace CoRE4INET {

Define_Module(TTIncoming);

TTIncoming::TTIncoming() :
        CTIncoming::CTIncoming()
{
    frame = NULL;
}

TTIncoming::~TTIncoming()
{
    if (frame != NULL)
    {
        delete frame;
    }
}

void TTIncoming::initialize()
{
    Incoming::initialize();
    if (par("period").stdstringValue().length() == 0)
    {
        par("period").setStringValue("period[0]");
    }
    period = dynamic_cast<Period*>(findModuleWhereverInNode(par("period").stringValue(), getParentModule()));
    ASSERT2(period, "cannot find period, you should specify it!");
}

void TTIncoming::handleMessage(cMessage *msg)
{
    //Incoming Message
    if (msg->arrivedOn("in"))
    {
        recordPacketReceived((EtherFrame*) msg);

        //get current time in cylce
        uint32_t currentTicks = period->getTicks();
        //Now check for correct arrival:
        if (frame != NULL)
        {
            emit(droppedSignal, (EtherFrame*) msg);
            hadError = true;
            if (ev.isGUI())
            {
                ev.printf("Received frame before permanence point of previous frame \n");
                bubble("Received frame before permanence point of previous frame");
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getDisplayString().setTagArg("tt", 0,
                        "WARNING: Received frame before permanence point of previous frame");
                getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                getParentModule()->getDisplayString().setTagArg("tt", 0, "Problem with Buffer");
            }
            delete msg;
        }
        //Check too early
        else if (par("receive_window_start").longValue() > 0
                && currentTicks < (uint32_t) par("receive_window_start").longValue())
        {
            emit(droppedSignal, (EtherFrame*) msg);
            hadError = true;
            if (ev.isGUI())
            {
                ev.printf(
                        "Received frame in %s too early! Receive Time was %d Ticks, should have been between %d and %d! \n",
                        getName(), currentTicks, par("receive_window_start").longValue(),
                        par("receive_window_end").longValue());
                bubble("Frame to early");
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getDisplayString().setTagArg("tt", 0,
                        "WARNING: Buffer configuration problem - Received frame too early");
                getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                getParentModule()->getDisplayString().setTagArg("tt", 0,
                        "WARNING: Buffer configuration problem - Received frame too early");
            }
            delete msg;
        }
        //Check too late
        else if (par("receive_window_end").longValue() > 0
                && currentTicks > (uint32_t) par("receive_window_end").longValue())
        {
            emit(droppedSignal, (EtherFrame*) msg);
            hadError = true;
            if (ev.isGUI())
            {
                ev.printf(
                        "Received frame in %s too late! Receive Time was %d Ticks, should have been between %d and %d! \n",
                        getName(), currentTicks, par("receive_window_start").longValue(),
                        par("receive_window_end").longValue());
                bubble("Frame to late");
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getDisplayString().setTagArg("tt", 0,
                        "WARNING: Buffer configuration problem - Received frame too late");
                getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                getParentModule()->getDisplayString().setTagArg("tt", 0,
                        "WARNING: Buffer configuration problem - Received frame too late");
            }
            delete msg;
        }
        //Timing ok
        else
        {
            //delay for permanence_pit if set
            if (par("permanence_pit").doubleValue() > 0)
            {
                if (!hadError && ev.isGUI())
                    getDisplayString().setTagArg("i2", 0, "status/hourglass");
                frame = (EtherFrame *) msg;
                SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("PIT Event", ACTION_TIME_EVENT);
                event->setAction_time((uint32_t) par("permanence_pit").longValue());
                event->setDestinationGate(gate("schedulerIn"));
                period->registerEvent(event);
            }
            else
            {
                send(msg, "out");
            }
        }
    }
    else if (msg->arrivedOn("schedulerIn") && msg->getKind() == ACTION_TIME_EVENT)
    {
        ASSERT(frame);
        delete msg;
        if (!hadError && ev.isGUI())
            getDisplayString().setTagArg("i2", 0, "");
        send(frame, "out");
        frame = NULL;
    }

}

} //namespace
