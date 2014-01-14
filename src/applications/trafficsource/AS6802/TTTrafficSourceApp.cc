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

#include <ModuleAccess.h>

namespace CoRE4INET {

Define_Module( TTTrafficSourceApp);

TTTrafficSourceApp::TTTrafficSourceApp():moduloCycle(0){
}

void TTTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();

    if(par("enabled").boolValue()){
        Scheduled::initialize();

        SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
        event->setAction_time((uint32_t)(par("action_time").doubleValue()/findModuleWhereverInNode("oscillator",getParentModule())->par("tick").doubleValue()));
        event->setDestinationGate(gate("schedulerIn"));
        period->registerEvent(event);
    }
}

void TTTrafficSourceApp::handleMessage(cMessage *msg){

    if(msg->arrivedOn("schedulerIn")){
        moduloCycle++;
        if(moduloCycle==(unsigned int)par("modulo").longValue()){
            sendMessage();
            moduloCycle=0;
        }

        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        event->setNext_cycle(true);
        period->registerEvent(event);
    }
    else{
        delete msg;
    }
}


} //namespace
