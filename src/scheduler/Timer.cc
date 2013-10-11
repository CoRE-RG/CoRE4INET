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

#include <exception>

namespace TTEthernetModel {

Define_Module(Timer);

simsignal_t Timer::clockCorrectionSignal = SIMSIGNAL_NULL;

Timer::Timer(){
    ticks=0;
    selfMessage = new cMessage("Scheduler Message");
    oscillator = NULL;
}

void Timer::initialize()
{
    oscillator = dynamic_cast<Oscillator*>(gate("oscillator_in")->getPathStartGate()->getOwnerModule());
    ASSERT2(oscillator, "cannot find oscillator!");

    clockCorrectionSignal = registerSignal("clockCorrection");

    recalculationTime = lastRecalculation = simTime();
}

Timer::~Timer()
{
    cancelAndDelete(selfMessage);
    for(std::map<uint64_t, std::list<SchedulerActionTimeEvent*> >::iterator it = registredActionTimeEvents.begin(); it!=registredActionTimeEvents.end();++it){
        for(std::list<SchedulerActionTimeEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
            cancelAndDelete(*it2);
        }
        registredActionTimeEvents.erase(it);
    }
    for(std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it = registredTimerEvents.begin(); it!=registredTimerEvents.end();++it){
        for(std::list<SchedulerTimerEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
            cancelAndDelete(*it2);
        }
        registredTimerEvents.erase(it);
    }
}

void Timer::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        sendOutEvents();
    }
}

void Timer::sendOutEvents(){
    recalculate();
    for(std::map<uint64_t, std::list<SchedulerActionTimeEvent*> >::iterator it = registredActionTimeEvents.begin(); it!=registredActionTimeEvents.end();++it){
        if((*it).first <= ticks){
            if((*it).first < ticks){
                EV << "WARNING: A message was delayed by the scheduler. The event(s) affected is (are): ";
                for(std::list<SchedulerActionTimeEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
                    EV << (*it2)->getName() << " by " << (*it2)->getDestinationGate()->getOwner()->getName() << "; ";
                }
                EV << "The delay was " << (ticks-(*it).first) << "ticks. This may happen for events in the clock correction interval." << std::endl;
            }
            for(std::list<SchedulerActionTimeEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
                sendDirect((*it2), (*it2)->getDestinationGate());
            }
            registredActionTimeEvents.erase(it);
        }
        else{
            break;
        }
    }
    for(std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it = registredTimerEvents.begin(); it!=registredTimerEvents.end();++it){
        if((*it).first <= ticks){
            if((*it).first < ticks){
                opp_error("THIS SHOULD NOT HAPPEN!");
            }
            for(std::list<SchedulerTimerEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
                sendDirect((*it2), (*it2)->getDestinationGate());
            }
            registredTimerEvents.erase(it);
        }
        else{
            break;
        }
    }
    reschedule();
}

void Timer::recalculate(){
    if(!oscillator){
        throw std::runtime_error("Timer was not yet initialized");
    }
    if(simTime()!=recalculationTime){//simTime()!=lastRecalculation has no effect due to rounding avoidance
        simtime_t current_tick = oscillator->getTick();
        uint64_t elapsed_ticks=floor((simTime()-lastRecalculation) / current_tick);
        ticks+=elapsed_ticks;
        //this is required to avoid rounding errors
        lastRecalculation += elapsed_ticks*current_tick;
        recalculationTime = simTime();
    }
}

void Timer::reschedule(){
    if(!oscillator){
        throw std::runtime_error("Timer was not yet initialized");
    }
    recalculate();
    ev << "DEBUG3 nextAction():"<<nextAction()<<" getTotalTicks():"<<getTotalTicks()<<std::endl;
    cancelEvent(selfMessage);
    try{
        simtime_t next_action = (nextAction()-getTotalTicks()) * oscillator->getTick();
        scheduleAt(simTime()+next_action, selfMessage);
    }
    catch(std::range_error re){
        //No message should be scheduled as there are no messages registred
    }
}

uint32_t Timer::nextAction(){
    if(registredActionTimeEvents.size()==0 && registredTimerEvents.size()==0){
        throw std::range_error("no events registered");
    }
    else if(registredTimerEvents.size()==0 || registredActionTimeEvents.begin()->first < registredTimerEvents.begin()->first){
        return registredActionTimeEvents.begin()->first;
    }
    else{
        return registredTimerEvents.begin()->first;
    }
}

uint64_t Timer::registerEvent(SchedulerTimerEvent *event){
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerTimerEvent %s)",event->getName());
#else
    Enter_Method_Silent();
#endif

    take(event);
    //We do not have to schedule anything if the point is now!
    if(event->getTimer()==0){
        sendDirect(event, event->getDestinationGate());
        return getTotalTicks();
    }
    else{
        uint64_t actionpoint = getTotalTicks() + event->getTimer();
        EV << "actionpoint "<<actionpoint<<std::endl;
        try{
            uint64_t old_actionpoint = nextAction();
            registredTimerEvents[actionpoint].push_back(event);
            //TODO: Overflow -> must regard ticks here!
            if(!selfMessage->isScheduled() || actionpoint<old_actionpoint){
                reschedule();
            }
        }
        catch(const std::range_error& re){
            registredTimerEvents[actionpoint].push_back(event);
            reschedule();
        }
        return actionpoint;
    }
}

uint64_t Timer::registerEvent(SchedulerActionTimeEvent *actionTimeEvent, Period *period){
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerActionTimeEvent %s, %s)",event->getName(), period->getName());
#else
    Enter_Method_Silent();
#endif

    take(actionTimeEvent);

    uint64_t actionpoint = 0;

    ASSERT(period);
    //Check whether event is in cycle
    if(actionTimeEvent->getAction_time() > (uint32_t)period->par("cycle_ticks").longValue()){
        bubble("Schedule contains out of cycle events!");
        return false;
    }
    int32_t distance = actionTimeEvent->getAction_time()-period->getTicks();
    if(distance<0 || (distance == 0 && actionTimeEvent->getNext_cycle())){
        actionpoint = getTotalTicks() + ((uint32_t)period->par("cycle_ticks").longValue() + distance);
    }
    else{
        actionpoint = getTotalTicks() + distance;
    }


    //We do not have to schedule anything if the point is now!
    if(actionpoint==getTotalTicks()){
        sendDirect(actionTimeEvent, actionTimeEvent->getDestinationGate());
    }
    else{
        ASSERT2(actionpoint>getTotalTicks(), "Cannot schedule past or present Events");
        try{
            uint64_t old_actionpoint = nextAction();
            registredActionTimeEvents[actionpoint].push_back(actionTimeEvent);
            //TODO: Overflow -> must regard ticks here!
            if(!selfMessage->isScheduled() || actionpoint<old_actionpoint){
                reschedule();
            }
        }
        catch(const std::range_error& re){
            registredActionTimeEvents[actionpoint].push_back(actionTimeEvent);
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
    ev << "DEBUG2 correction:"<<ticks<<" was:"<<this->ticks<<" now:"<<this->ticks+ticks<<std::endl;
    emit(clockCorrectionSignal, ticks);
    this->ticks+=ticks;
    //Now correct the timer events that must be independent of clockCorrection
    std::map<uint64_t, std::list<SchedulerTimerEvent*> > correctedTimerEvents;
    for(std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it = registredTimerEvents.begin(); it!=registredTimerEvents.end();++it){
        correctedTimerEvents[(*it).first+ticks] = (*it).second;
    }
    registredTimerEvents = correctedTimerEvents;
    sendOutEvents();
    ev << "DEBUG2 correction:"<<ticks<<" was:"<<this->ticks<<" now:"<<this->ticks+ticks<<std::endl;
}

} //namespace
