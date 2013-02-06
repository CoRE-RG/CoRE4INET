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

#include "TTEScheduler.h"

#include <SchedulerMessage_m.h>

namespace TTEthernetModel {

Define_Module( TTEScheduler);

simsignal_t TTEScheduler::currentDrift = SIMSIGNAL_NULL;
simsignal_t TTEScheduler::newCycle = SIMSIGNAL_NULL;

int TTEScheduler::numInitStages() const
{
    return 1;
}

void TTEScheduler::initialize(int stage)
{
    if(stage==0){
        currentDrift = registerSignal("currentDrift");
        newCycle = registerSignal("newCycle");
        cycles = 0;

        //Start Timer
        scheduleAt(simTime(), new SchedulerEvent("NEW_CYCLE", NEW_CYCLE));

        lastCycleStart = simTime();
        lastNewCycleMessage = simTime();
        lastCycleTicks = 0;
    }
}

bool TTEScheduler::registerEvent(SchedulerEvent *event){
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerEvent %s)",event->getName());
#else
    Enter_Method_Silent();
#endif

    if (event->getKind() == ACTION_TIME_EVENT)
    {
        return registerEvent(dynamic_cast<SchedulerActionTimeEvent*>(event), false);
    }
    else if (event->getKind() == TIMER_EVENT)
    {
        take(event);
        registredEvents.push_back(event);
        SchedulerTimerEvent *timerEvent = (SchedulerTimerEvent*) event;
        scheduleAt(simTime() + currentTick * timerEvent->getTimer(), event);
    }
    return true;
}


bool TTEScheduler::registerEvent(SchedulerActionTimeEvent *actionTimeEvent, bool forceNextCycle)
{
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerEvent %s, forceNextCycle %d)",event->getName(), forceNextCycle);
#else
    Enter_Method_Silent();
#endif

    take(actionTimeEvent);
    registredEvents.push_back(actionTimeEvent);

    //Check whether event is in cycle
    if(actionTimeEvent->getAction_time()>cycleTicks){
        bubble("Schedule contains out of cycle events!");
        return false;
    }

    if ((actionTimeEvent->getAction_time() <= getTicks()) || forceNextCycle)
    {
        scheduleAt(lastCycleStart
                            + currentTick
                            * (actionTimeEvent->getAction_time() + cycleTicks),
                            actionTimeEvent);
    }
    else
    {

        scheduleAt(lastCycleStart + currentTick * (actionTimeEvent->getAction_time()),
                            actionTimeEvent);
    }
    return true;
}

void TTEScheduler::unregisterEvent(SchedulerEvent *event){
    if(event->isScheduled()){
        cancelEvent(event);
        registredEvents.remove(event);
    }

}

void TTEScheduler::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && (msg->getKind() == ACTION_TIME_EVENT || msg->getKind() == TIMER_EVENT))
    {
        SchedulerEvent *event = (SchedulerEvent*) msg;
        registredEvents.remove(event);
        sendDirect(event, event->getDestinationGate());
    }
    else if (msg->isSelfMessage() && msg->getKind() == NEW_CYCLE)
    {
        //First the precision is changed for the next cycle
        changeDrift();

        emit(newCycle, 1L);
        cycles++;
        lastCycleStart = simTime();
        lastNewCycleMessage = simTime();
        lastCycleTicks += cycleTicks;
        scheduleAt(lastCycleStart + currentTick * cycleTicks, msg);
        newCyclemsg = msg;

        correctEvents();
    }
}

void TTEScheduler::changeDrift(){

    simtime_t newDriftChange = uniform(-maxDriftChange,maxDriftChange);
    simtime_t newTick = currentTick+newDriftChange;
    if((newTick-tick)>maxDrift)
        par("current_tick").setDoubleValue((tick+maxDrift).dbl());
    else if((newTick-tick)<-maxDrift)
        par("current_tick").setDoubleValue((tick-maxDrift).dbl());
    else
        par("current_tick").setDoubleValue(newTick.dbl());
    emit(currentDrift, par("current_tick").doubleValue()-tick);
}

void TTEScheduler::correctEvents(){
    for(std::list<SchedulerEvent*>::const_iterator registredEvent = registredEvents.begin(); registredEvent != registredEvents.end(); registredEvent++){
        if((*registredEvent)->getKind() == ACTION_TIME_EVENT){
            SchedulerActionTimeEvent *actionTimeEvent = (SchedulerActionTimeEvent*)*registredEvent;
            cancelEvent(actionTimeEvent);
            //TODO lots of improvements!
            if (actionTimeEvent->getAction_time() > getTicks())
            {
                scheduleAt(lastCycleStart + currentTick * actionTimeEvent->getAction_time(),
                        actionTimeEvent);
            }
            else if (actionTimeEvent->getAction_time() == getTicks())
            {
                scheduleAt(simTime(), actionTimeEvent);
            }
            else
            {
                if(lastCycleStart>simTime()){
                    scheduleAt(lastCycleStart
                                            + currentTick
                                            * (actionTimeEvent->getAction_time()),
                                            actionTimeEvent);
                }
                else{
                    scheduleAt(lastCycleStart
                                            + currentTick
                                            * (actionTimeEvent->getAction_time() + cycleTicks),
                                            actionTimeEvent);
                }
            }
        }
    }
}

void TTEScheduler::handleParameterChange(const char* parname){
    maxDriftChange = par("max_drift_change").doubleValue();
    maxDrift = par("max_drift").doubleValue();
    currentTick = par("current_tick").doubleValue();
    tick = par("tick").doubleValue();
    cycleTicks = par("cycle_ticks").longValue();
}

void TTEScheduler::clockCorrection(int32_t ticks){
    Enter_Method("clock correction %d ticks",ticks);

    lastCycleStart+=ticks*currentTick;

    //Now correct the new cylce time
    cancelEvent(newCyclemsg);
    scheduleAt(simTime()-(simTime()-lastCycleStart) + currentTick * cycleTicks, newCyclemsg);
    //Now correct the events
    correctEvents();
}

uint32_t TTEScheduler::getTicks()
{
    if(simTime() >= lastCycleStart){
        return floor(((simtime_t)((simTime() - lastCycleStart) / currentTick)).dbl());
    }
    else{
        return cycleTicks - floor(((simtime_t)((lastCycleStart - simTime()) / currentTick)).dbl());
    }
}

uint64_t TTEScheduler::getTotalTicks()
{
    return lastCycleTicks + floor(((simtime_t)((simTime() - lastNewCycleMessage) / currentTick)).dbl());
}

uint32_t TTEScheduler::getCycles()
{
    return cycles;
}

} //namespace
