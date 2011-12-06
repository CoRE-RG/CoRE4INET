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

#include <configuration/ConfigurationUtils.h>

#include <SchedulerMessage_m.h>
#include <SchedulerMessageEvents_m.h>

namespace TTEthernetModel {

Define_Module( TTEScheduler);

simsignal_t TTEScheduler::currentDrift = SIMSIGNAL_NULL;
simsignal_t TTEScheduler::newCycle = SIMSIGNAL_NULL;

void TTEScheduler::initialize()
{
    currentDrift = registerSignal("currentDrift");
    newCycle = registerSignal("newCycle");

    ConfigurationUtils::getPreloadedMMR();
    ecorecpp::ModelRepository_ptr mr = ecorecpp::ModelRepository::_instance();
    ConfigurationUtils::resolveCommonAliases(mr);
    ::ecore::EObject_ptr eobj = mr->getByFilename(getParentModule()->par("network_configuration"));
    assert(eobj);
    NetworkConfig_ptr nc = ::ecore::instanceOf<NetworkConfig>(eobj);
    assert(nc);
    DeviceSpecification_ptr ds = ConfigurationUtils::getDeviceSpecification(
            getParentModule()->par("device_name").stdstringValue(), nc);
    assert(ds);

    //TODO cycle time auslesen


    if (ds->eClass()->getName() == "Switch")
    {
        TargetDevice_ptr td = ds->as<Switch> ()->getRefDeviceMapping()->getRefTargetDevice();
        if (td->eClass()->getName() == ("TTTechIpTargetDevice"))
        {
            TTTechIpTargetDevice_ptr iptd = td->as<TTTechIpTargetDevice> ();
            par("tick").setDoubleValue(ConfigurationUtils::freq2s(iptd->getClockSpeed()));
            par("current_tick").setDoubleValue(par("tick").doubleValue());
            //TODO Infomessage of parameter change
        }
    }

    //Start Timer
    scheduleAt(simTime(), new SchedulerEvent("NEW_CYCLE", NEW_CYCLE));

    lastCycleStart = simTime();
}

bool TTEScheduler::registerEvent(SchedulerEvent *event)
{
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerEvent %s)",event->getName());
#else
    Enter_Method_Silent();
#endif
    take(event);
    registredEvents.push_back(event);
    if (event->getKind() == ACTION_TIME_EVENT)
    {
        SchedulerActionTimeEvent *actionTimeEvent = (SchedulerActionTimeEvent*) event;
        //Check whether event is in cycle
        if(actionTimeEvent->getAction_time()>cycleTicks){
            bubble("Schedule contains out of cycle events!");
            return false;
        }

        if (actionTimeEvent->getAction_time() > getTicks())
        {
            scheduleAt(lastCycleStart + currentTick * actionTimeEvent->getAction_time(),
                    actionTimeEvent);
        }
        else
        {
            scheduleAt(lastCycleStart
                    + currentTick
                    * (actionTimeEvent->getAction_time() + cycleTicks),
                    actionTimeEvent);

        }
    }
    else if (event->getKind() == TIMER_EVENT)
    {
        SchedulerTimerEvent *timerEvent = (SchedulerTimerEvent*) event;
        scheduleAt(simTime() + currentTick * timerEvent->getTimer(), event);
    }
    return true;
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
        lastCycleStart = simTime();
        lastCycleTicks += cycleTicks;
        scheduleAt(lastCycleStart + currentTick * cycleTicks, msg);
        newCyclemsg = msg;


        //TODO
        int modticks = (int)(simTime().dbl()/tick)%cycleTicks;
        if(modticks>(cycleTicks/2))
            modticks=modticks-cycleTicks;
        ev << "TICKS:" << modticks << endl;
        modticks+=uniform(-0.000002,0.000002)/tick;
        clockCorrection(-modticks);
        ev << "NOW: " << getTicks() << endl;
    }
}

void TTEScheduler::changeDrift(){

    double newDriftChange = uniform(-maxDriftChange,maxDriftChange);
    double newTick = currentTick+newDriftChange;
    if((newTick-tick)>maxDrift)
        par("current_tick").setDoubleValue(tick+maxDrift);
    else if((newTick-tick)<-maxDrift)
        par("current_tick").setDoubleValue(tick-maxDrift);
    else
        par("current_tick").setDoubleValue(newTick);
    emit(currentDrift, par("current_tick").doubleValue()-tick);
}

void TTEScheduler::correctEvents(){
    for(std::list<SchedulerEvent*>::const_iterator registredEvent = registredEvents.begin(); registredEvent != registredEvents.end(); registredEvent++){
        if((*registredEvent)->getKind() == ACTION_TIME_EVENT){
            SchedulerActionTimeEvent *actionTimeEvent = (SchedulerActionTimeEvent*)*registredEvent;
            cancelEvent(actionTimeEvent);
            //TODO alles mögliche ;)
            if (actionTimeEvent->getAction_time() > getTicks())
            {
                scheduleAt(lastCycleStart + currentTick * actionTimeEvent->getAction_time(),
                        actionTimeEvent);
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
            assert(actionTimeEvent->isScheduled());
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

void TTEScheduler::clockCorrection(int ticks){
    lastCycleStart+=SimTime(ticks*currentTick);

    //Now correct the new cylce time
    cancelEvent(newCyclemsg);
    scheduleAt(simTime()-(simTime()-lastCycleStart) + currentTick * cycleTicks, newCyclemsg);
    //Now correct the events
    correctEvents();
}

unsigned int TTEScheduler::getTicks()
{
    if(simTime() >= lastCycleStart){
        return round(((simTime() - lastCycleStart) / currentTick).dbl());
    }
    else{
        return cycleTicks - round(((lastCycleStart - simTime()) / currentTick).dbl());
    }
}

unsigned long TTEScheduler::getTotalTicks()
{
    return lastCycleTicks + getTicks();
}

} //namespace
