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

using namespace TTEthernetModel;

Define_Module( DummySync);

void DummySync::initialize()
{
    TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("Sync Task Event", ACTION_TIME_EVENT);
    event->setAction_time(par("action_time").longValue());
    event->setDestinationGate(gate("schedulerIn"));
    tteScheduler->registerEvent(event);
}

void DummySync::handleMessage(cMessage *msg)
{
    TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
    if(msg->arrivedOn("schedulerIn")){
        if(tteScheduler->getCycles()>1){
            unsigned int cycleTicks = tteScheduler->par("cycle_ticks").longValue();
            double tick = tteScheduler->par("tick").doubleValue();

            int modticks = ((int)(simTime().dbl()/tick)-par("action_time").longValue())%cycleTicks;
            if(modticks>(cycleTicks/2))
                modticks=modticks-cycleTicks;
            modticks+=uniform(-par("precission").doubleValue()/2, par("precission").doubleValue()/2)/tick;

            tteScheduler->clockCorrection(-modticks);
        }

        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        tteScheduler->registerEvent(event);
    }
}
