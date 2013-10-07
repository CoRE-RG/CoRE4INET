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

#include "Timer.h"

namespace TTEthernetModel {

Define_Module(Timer);

void Timer::initialize()
{
    ticks=0;
}

void Timer::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        recalculate();
        for(std::map<uint64_t, std::list<SchedulerEvent*> >::iterator it = registredEvents.begin(); it!=registredEvents.end();++it){
            if((*it).first <= ticks){
                for(std::list<SchedulerEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
                    sendDirect((*it2), (*it2)->getDestinationGate());
                }
                registredEvents.erase(it);
            }
            else{
                break;
            }
        }
    }
}

void Timer::recalculate(){
    if(simTime()!=lastRecalculation){
        ticks+=floor((simTime()-lastRecalculation)/ SimTime(oscillator->par("current_tick").doubleValue()));
        lastRecalculation=simTime();
    }
}

void Timer::reschedule(){
    recalculate();
    simtime_t actiontime = nextAction() * oscillator->par("current_tick").doubleValue();
    cancelEvent(selfMessage);
    scheduleAt(actiontime, selfMessage);
}

uint32_t Timer::nextAction(){
    return registredEvents.begin()->first;
}

bool Timer::registerEvent(SchedulerEvent *event, Period *period){
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerEvent %s)",event->getName());
#else
    Enter_Method_Silent();
#endif

    take(event);

    uint64_t actionpoint = 0;
    if (event->getKind() == ACTION_TIME_EVENT)
    {
        SchedulerActionTimeEvent *actionTimeEvent = dynamic_cast<SchedulerActionTimeEvent*>(event);
        //Check whether event is in cycle
        if(actionTimeEvent->getAction_time() > (uint32_t)period->par("cycle_ticks").longValue()){
            bubble("Schedule contains out of cycle events!");
            return false;
        }
        int32_t distance = actionTimeEvent->getAction_time()-period->getTicks();
        if(distance<0){
            actionpoint = getTotalTicks() + ((uint32_t)period->par("cycle_ticks").longValue() + distance);
        }
        else{
            actionpoint = getTotalTicks() + distance;
        }
    }
    else if (event->getKind() == TIMER_EVENT)
    {
        SchedulerTimerEvent *timerEvent = dynamic_cast<SchedulerTimerEvent*>(event);
        actionpoint = getTotalTicks() + timerEvent->getTimer();
    }
    registredEvents[actionpoint].push_back(event);
    //TODO: Overflow -> must regard ticks here!
    if(actionpoint<nextAction()){
        reschedule();
    }
    return true;
}

uint64_t Timer::getTotalTicks()
{
    recalculate();
    return ticks;
}

} //namespace
