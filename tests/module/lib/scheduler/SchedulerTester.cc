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

#include "SchedulerTester.h"


using namespace TTEthernetModel;

Define_Module(SchedulerTester);

void SchedulerTester::initialize()
{
    Scheduled::initialize();
    scheduleAt(simTime(), new cMessage("ACTIVATOR!"));
}

void SchedulerTester::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
        event->setAction_time(1000);
        event->setDestinationGate(gate("schedulerIn"));
        period->registerEvent(event);
        ev << "REGISTRED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime() << "; ticks:" << period->getTicks() << "; total_ticks:" << period->getTotalTicks() << "]" << endl;
    }
    else if(msg->arrivedOn("schedulerIn")){
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        ev << "EXECUTED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime() << "; ticks:" << period->getTicks() << "; total_ticks:" << period->getTotalTicks() << "]" << endl;
    }
    delete msg;
}
