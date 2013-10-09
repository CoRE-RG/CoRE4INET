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
    oscillator = dynamic_cast<Oscillator*>(gate("oscillator_in")->getPathStartGate()->getOwnerModule());
    ASSERT2(oscillator, "cannot find oscillator!");
    selfMessage = new cMessage("Scheduler Message");
}

Timer::~Timer()
{
    cancelAndDelete(selfMessage);
    for(std::map<uint64_t, std::list<SchedulerEvent*> >::iterator it = registredEvents.begin(); it!=registredEvents.end();++it){
        for(std::list<SchedulerEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
            cancelAndDelete(*it2);
        }
        registredEvents.erase(it);
    }
}

void Timer::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        recalculate();
        EV << "now is:" << ticks << " size is:"<< registredEvents.size()<< std::endl;
        for(std::map<uint64_t, std::list<SchedulerEvent*> >::iterator it = registredEvents.begin(); it!=registredEvents.end();++it){
            EV << "check:" << (*it).first << std::endl;
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
        reschedule();
        EV << "changed size is:"<< registredEvents.size()<< std::endl;
    }
}

void Timer::recalculate(){
    if(simTime()!=lastRecalculation){
        simtime_t current_tick = oscillator->getTick();
        uint64_t elapsed_ticks=floor((simTime()-lastRecalculation) / current_tick);
        ticks+=elapsed_ticks;
        //this is required to avoid rounding errors
        lastRecalculation += elapsed_ticks*current_tick;
    }
}

void Timer::reschedule(){
    recalculate();
    simtime_t next_action = (nextAction()-getTotalTicks()) * oscillator->getTick();
    cancelEvent(selfMessage);
    if(registredEvents.size()>0){
        scheduleAt(simTime()+next_action, selfMessage);
    }
}

uint32_t Timer::nextAction(){
    return registredEvents.begin()->first;
}

uint64_t Timer::registerEvent(SchedulerTimerEvent *event){
    return registerEvent(event, NULL);
}

uint64_t Timer::registerEvent(SchedulerEvent *event, Period *period){
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerEvent %s)",event->getName());
#else
    Enter_Method_Silent();
#endif

    take(event);

    uint64_t actionpoint = 0;
    if (event->getKind() == ACTION_TIME_EVENT)
    {
        ASSERT(period);
        SchedulerActionTimeEvent *actionTimeEvent = dynamic_cast<SchedulerActionTimeEvent*>(event);
        //Check whether event is in cycle
        if(actionTimeEvent->getAction_time() > (uint32_t)period->par("cycle_ticks").longValue()){
            bubble("Schedule contains out of cycle events!");
            return false;
        }
        int32_t distance = actionTimeEvent->getAction_time()-period->getTicks();
        if(distance<0 || actionTimeEvent->getNext_cycle()){
            actionpoint = getTotalTicks() + ((uint32_t)period->par("cycle_ticks").longValue() + distance);
        }
        else{
            actionpoint = getTotalTicks() + distance;
        }
        ev << "actime:" << actionTimeEvent->getAction_time() << " distance:" << distance << " acpoint:"<< actionpoint << "name: "<<actionTimeEvent->getName()<<std::endl;
    }
    else if (event->getKind() == TIMER_EVENT)
    {
        SchedulerTimerEvent *timerEvent = dynamic_cast<SchedulerTimerEvent*>(event);
        actionpoint = getTotalTicks() + timerEvent->getTimer();
    }
    else{
        //TODO throw
        return 0;
    }
    //We do not have to schedule anything if the point is now!
    if(actionpoint==getTotalTicks()){
        sendDirect(event, event->getDestinationGate());
    }
    else{
        ASSERT2(actionpoint>=getTotalTicks(), "Cannot schedule past Events");
        uint64_t old_actionpoint = nextAction();
        registredEvents[actionpoint].push_back(event);
        //TODO: Overflow -> must regard ticks here!
        if(!selfMessage->isScheduled() || actionpoint<old_actionpoint){
            reschedule();
        }
    }
    return actionpoint;
}

uint64_t Timer::getTotalTicks()
{
    recalculate();
    return ticks;
}

void Timer::clockCorrection(int32_t ticks){
    Enter_Method("clock correction %d ticks",ticks);

    this->ticks+ticks;
    reschedule();
}

} //namespace
