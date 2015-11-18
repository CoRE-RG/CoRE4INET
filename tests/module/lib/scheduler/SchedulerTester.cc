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

using namespace CoRE4INET;

Define_Module(SchedulerTester);

void SchedulerTester::initialize()
{
    Scheduled::initialize();
    scheduleAt(simTime(), new cMessage("ACTIVATOR!"));
}

void SchedulerTester::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        ev << "Testcase 1: Register Event at 1000" << endl;
        SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("Test Event 1", ACTION_TIME_EVENT);
        event->setAction_time(1000);
        event->setDestinationGate(gate("schedulerIn"));
        getPeriod()->registerEvent(event);
        ev << "REGISTRED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;
    }
    else if (msg->arrivedOn("schedulerIn") && strcmp(msg->getName(), "Test Event 1") == 0)
    {
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *) msg;
        ev << "EXECUTED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;

        ev << "Testcase 2: Register Event at 1000 for this cycle (shoud be executed at the same moment)" << endl;
        SchedulerActionTimeEvent *event2 = new SchedulerActionTimeEvent("Test Event 2", ACTION_TIME_EVENT);
        event2->setAction_time(1000);
        event2->setDestinationGate(gate("schedulerIn"));
        getPeriod()->registerEvent(event2);
        ev << "REGISTRED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;
    }
    else if (msg->arrivedOn("schedulerIn") && strcmp(msg->getName(), "Test Event 2") == 0)
    {
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *) msg;
        ev << "EXECUTED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;

        ev << "Testcase 3: Register Event at 1000 for next cycle (shoud be executed in next cycle)" << endl;
        SchedulerActionTimeEvent *event3 = new SchedulerActionTimeEvent("Test Event 3", ACTION_TIME_EVENT);
        event3->setAction_time(1000);
        event3->setDestinationGate(gate("schedulerIn"));
        event3->setNext_cycle(true);
        getPeriod()->registerEvent(event3);
        ev << "REGISTRED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;
    }
    else if (msg->arrivedOn("schedulerIn") && strcmp(msg->getName(), "Test Event 3") == 0)
    {
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *) msg;
        ev << "EXECUTED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;

        ev << "Testcase 4: Register Event at 1000 for next cycle and correct clock -1000" << endl;
        SchedulerActionTimeEvent *event4 = new SchedulerActionTimeEvent("Test Event 4", ACTION_TIME_EVENT);
        event4->setAction_time(1000);
        event4->setDestinationGate(gate("schedulerIn"));
        event4->setNext_cycle(true);
        getPeriod()->registerEvent(event4);
        ev << "REGISTRED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;
        int clock_correction = -1000;
        getTimer()->clockCorrection(clock_correction);
        ev << "Clock correction " << clock_correction << "ticks" << endl;
    }
    else if (msg->arrivedOn("schedulerIn") && strcmp(msg->getName(), "Test Event 4") == 0)
    {
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *) msg;
        ev << "EXECUTED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;

        ev << "Testcase 5: Register Event at 1000 for next cycle and correct clock +1000" << endl;
        SchedulerActionTimeEvent *event5 = new SchedulerActionTimeEvent("Test Event 5", ACTION_TIME_EVENT);
        event5->setAction_time(1000);
        event5->setDestinationGate(gate("schedulerIn"));
        event5->setNext_cycle(true);
        getPeriod()->registerEvent(event5);
        ev << "REGISTRED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;
        int clock_correction = 1000;
        getTimer()->clockCorrection(clock_correction);
        ev << "Clock correction " << clock_correction << "ticks" << endl;
    }
    else if (msg->arrivedOn("schedulerIn") && strcmp(msg->getName(), "Test Event 5") == 0)
        {
            SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *) msg;
            ev << "EXECUTED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                    << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;

            ev << "Testcase 6: Register Event at 1000 for next cycle and correct clock 11000 (clock after action_time)" << endl;
            SchedulerActionTimeEvent *event6 = new SchedulerActionTimeEvent("Test Event 6", ACTION_TIME_EVENT);
            event6->setAction_time(1000);
            event6->setDestinationGate(gate("schedulerIn"));
            event6->setNext_cycle(true);
            getPeriod()->registerEvent(event6);
            ev << "REGISTRED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                    << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;
            int clock_correction = 11000;
            getTimer()->clockCorrection(clock_correction);
            ev << "Clock correction " << clock_correction << "ticks" << endl;
        }
    else if (msg->arrivedOn("schedulerIn") && strcmp(msg->getName(), "Test Event 6") == 0)
    {
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *) msg;
        ev << "EXECUTED: ACTION_TIME_EVENT: action_time:" << event->getAction_time() << " NOW [simtime:" << simTime()
                << "; ticks:" << getPeriod()->getTicks() << "; total_ticks:" << getPeriod()->getTotalTicks() << "]" << endl;
    }
    delete msg;
}
