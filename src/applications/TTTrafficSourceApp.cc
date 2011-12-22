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

#include "TTTrafficSourceApp.h"
#include <CTFrame_m.h>
#include "TTEScheduler.h"

namespace TTEthernetModel {

Define_Module( TTTrafficSourceApp);

TTTrafficSourceApp::TTTrafficSourceApp():moduloCycle(0){
}

void TTTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();

    TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
    event->setAction_time(par("action_time").doubleValue()/tteScheduler->par("tick").doubleValue());
    event->setDestinationGate(gate("schedulerIn"));
    tteScheduler->registerEvent(event);
}

void TTTrafficSourceApp::handleMessage(cMessage *msg){

    if(msg->arrivedOn("schedulerIn")){
        moduloCycle++;
        if(moduloCycle==(unsigned int)par("modulo").longValue()){
            sendMessage();
            moduloCycle=0;
        }

        TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        tteScheduler->registerEvent(event);
    }
    else{
        delete msg;
    }
}


} //namespace
