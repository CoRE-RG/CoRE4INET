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

#include "DummySync.h"
#include "TTEScheduler.h"
#include "SchedulerMessageEvents_m.h"
#include "SyncNotification_m.h"

#include <ModuleAccess.h>

using namespace CoRE4INET;

Define_Module( DummySync);

int DummySync::numInitStages() const
{
    if(SyncBase::numInitStages()>3){
        return SyncBase::numInitStages();
    }
    else{
        return 3;
    }
}

void DummySync::initialize(int stage)
{
    SyncBase::initialize(stage);
    if(stage==1)
    {
        Scheduled::initialize();

        SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("Sync Task Event", ACTION_TIME_EVENT);
        event->setAction_time((uint32_t)par("action_time").longValue());
        event->setDestinationGate(gate("schedulerIn"));
        period->registerEvent(event);
    }
    if(stage==2)
    {
        notify(SYNC);
        getDisplayString().setTagArg("i", 1, "green");
    }
}

void DummySync::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("schedulerIn")){
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        event->setNext_cycle(true);
        period->registerEvent(event);

        if(period->getCycles()>0){
            uint32_t cycleTicks = (uint32_t)period->par("cycle_ticks").longValue();
            simtime_t tick = oscillator->par("tick").doubleValue();

            int64_t modticks = ((int64_t)(simTime()/tick)-par("action_time").longValue())%cycleTicks;
            if(modticks>((int64_t)cycleTicks/2))
                modticks=modticks-cycleTicks;
            modticks+=uniform(-par("precission").doubleValue()/2, par("precission").doubleValue()/2)/tick;

            timer->clockCorrection((int32_t)modticks);
        }
    }
}
