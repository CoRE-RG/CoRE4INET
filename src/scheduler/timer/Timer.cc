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

namespace CoRE4INET {

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
                EV << "WARNING: Message(s) (was/were) delayed by the scheduler. The event(s) affected (is/are): ";
                for(std::list<SchedulerActionTimeEvent*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2){
                    EV << (*it2)->getName() << " by " << (*it2)->getDestinationGate()->getOwner()->getName() << "; ";
                }
                EV << "The delay was " << (ticks-(*it).first) << "ticks. This may happen for events in the clock correction interval." << std::endl;
                if(ev.isGUI()){
                    getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getDisplayString().setTagArg("tt", 0, "WARNING: ActionTimeEvent was delayed (probably due to clock correction)");
                    getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getDisplayString().setTagArg("tt", 0, "Problem with Timer");
                }
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
            if((ticks - (*it).first) > 1){
                EV<<"misscheduled: "<<(ticks - (*it).first)<<std::endl;
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
    if(simTime()!=recalculationTime){//simTime()!=lastRecalculation has no effect due to rounding avoidance
        if(!oscillator){
            throw std::runtime_error("Timer was not yet initialized");
        }
        simtime_t current_tick = oscillator->getTick();
        uint64_t elapsed_ticks=(uint64_t)floor((simTime()-lastRecalculation) / current_tick);
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
    cancelEvent(selfMessage);
    recalculate();
    try{
        simtime_t next_action = (nextAction()-getTotalTicks()) * oscillator->getTick();
        scheduleAt(simTime()+next_action, selfMessage);
    }
    catch(std::range_error re){
        //No message should be scheduled as there are no messages registered
    }
}

uint32_t Timer::nextAction(){
    if(registredActionTimeEvents.size()==0 && registredTimerEvents.size()==0){
        throw std::range_error("no events registered");
    }
    else if(registredTimerEvents.size()==0 || (registredActionTimeEvents.size()!=0 && registredActionTimeEvents.begin()->first < registredTimerEvents.begin()->first)){
        return (uint32_t)registredActionTimeEvents.begin()->first;
    }
    else{
        return (uint32_t)registredTimerEvents.begin()->first;
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
        try{
            uint64_t old_actionpoint = nextAction();
            registredTimerEvents[actionpoint].push_back(event);
            //TODO: Overflow -> must regard ticks here!
            if(!selfMessage->isScheduled() || actionpoint<old_actionpoint){
                reschedule();
            }
        }
        catch(__attribute((unused)) const std::range_error& re){
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
    int32_t distance = (int32_t)((int64_t)actionTimeEvent->getAction_time()-(int64_t)period->getTicks());
    if(distance<0 || (distance == 0 && actionTimeEvent->getNext_cycle())){
        actionpoint = (uint64_t)((int64_t)getTotalTicks() + ((int64_t)period->par("cycle_ticks").longValue() + distance));
    }
    else{
        actionpoint = (uint64_t)((int64_t)getTotalTicks() + distance);
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
        catch(__attribute((unused)) const std::range_error& re){
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

Oscillator* Timer::getOscillator(){
    if(!oscillator){
        throw std::runtime_error("Timer was not yet initialized");
    }
    return oscillator;
}

void Timer::clockCorrection(int32_t ticks){
    Enter_Method("clock correction %d ticks",ticks);
    emit(clockCorrectionSignal, ticks);
    this->ticks=(uint64_t)((int64_t)this->ticks + ticks);
    //Now correct the timer events that must be independent of clockCorrection
    std::map<uint64_t, std::list<SchedulerTimerEvent*> > correctedTimerEvents;
    std::map<uint64_t,std::list<SchedulerTimerEvent*> >::iterator it = correctedTimerEvents.begin();
    for(std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it2 = registredTimerEvents.begin(); it2!=registredTimerEvents.end();++it2){
        if(correctedTimerEvents.size()==0){
            correctedTimerEvents[(uint64_t)((int64_t)(*it2).first+ticks)] = (*it2).second;
            it=correctedTimerEvents.begin();
        }else{
            //Better version with hint?
            it = correctedTimerEvents.insert(it,  std::pair<uint64_t,std::list<SchedulerTimerEvent*> >(((uint64_t)((int64_t)(*it2).first+ticks)),(*it2).second));
        }
    }
    registredTimerEvents = correctedTimerEvents;
    sendOutEvents();
}

} //namespace
