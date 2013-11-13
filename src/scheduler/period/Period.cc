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

#include "Period.h"
#include "Timer.h"
#include <exception>

namespace CoRE4INET {

Define_Module(Period);

simsignal_t Period::newCycle = SIMSIGNAL_NULL;

Period::Period(){
    cycles=0;
    newCycleEvent=NULL;
    timer=NULL;
}

void Period::initialize()
{
    WATCH(cycles);
    newCycle = registerSignal("newCycle");

    ASSERT(par("cycle_ticks").longValue()>par("offset_ticks").longValue());
    timer = dynamic_cast<Timer *>(gate("out")->getPathEndGate()->getOwnerModule());
    ASSERT(timer);

    newCycleEvent = new SchedulerActionTimeEvent("Period New Cycle Event", ACTION_TIME_EVENT);
    newCycleEvent->setDestinationGate(gate("schedulerIn"));
    newCycleEvent->setNext_cycle(true);
    timer->registerEvent(newCycleEvent, this);
}

void Period::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("schedulerIn") && msg->getKind() == ACTION_TIME_EVENT){
        cycles++;
        emit(newCycle, 1L);
        timer->registerEvent(newCycleEvent, this);
    }
    else{
        delete msg;
    }
}


uint64_t Period::registerEvent(SchedulerEvent *event){
    if(!timer){
        throw std::runtime_error("Period was not yet initialized");
    }
    if(dynamic_cast<SchedulerActionTimeEvent*>(event)){
        return timer->registerEvent(dynamic_cast<SchedulerActionTimeEvent*>(event), this);
    }
    else if(dynamic_cast<SchedulerTimerEvent*>(event)){
        return timer->registerEvent(dynamic_cast<SchedulerTimerEvent*>(event));
    }
    else{
        throw std::invalid_argument("Unknown event Kind");
    }
}

uint32_t Period::getTicks(){
    if(!timer){
        throw std::runtime_error("Period was not yet initialized");
    }
    //cycle_ticks is added to assure a positive return value
    return (par("cycle_ticks").longValue() + timer->getTotalTicks() - par("offset_ticks").longValue()) % par("cycle_ticks").longValue();
}

uint64_t Period::getTotalTicks(){
    if(!timer){
        throw std::runtime_error("Period was not yet initialized");
    }
    return timer->getTotalTicks();
}

uint32_t Period::getCycles(){
    return cycles;
}

} //namespace
