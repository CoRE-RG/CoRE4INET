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

void TTEScheduler::registerEvent(SchedulerEvent *event)
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

        ev << "AT: " << actionTimeEvent->getAction_time() << " T: " << getTicks() << endl;
        //TODO alles mögliche ;)
        if (actionTimeEvent->getAction_time()-50 > getTicks())
        {
            scheduleAt(lastCycleStart + par("current_tick").doubleValue() * actionTimeEvent->getAction_time(),
                    actionTimeEvent);
        }
        else
        {
            scheduleAt(lastCycleStart
                    + par("current_tick").doubleValue()
                    * (actionTimeEvent->getAction_time() + par("cycle_ticks").longValue()),
                    actionTimeEvent);
        }
    }
    else if (event->getKind() == TIMER_EVENT)
    {
        SchedulerTimerEvent *timerEvent = (SchedulerTimerEvent*) event;
        scheduleAt(simTime() + par("current_tick").doubleValue() * timerEvent->getTimer(), event);
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
        //TODO
        double new_drift = uniform(-par("max_drift").doubleValue(),par("max_drift").doubleValue());
        par("current_tick").setDoubleValue(par("current_tick").doubleValue()+new_drift);
        emit(currentDrift, par("current_tick").doubleValue()-par("tick").doubleValue());


        emit(newCycle, 1L);
        lastCycleStart = simTime();
        lastCycleTicks += par("cycle_ticks").longValue();
        scheduleAt(lastCycleStart + par("current_tick").doubleValue() * par("cycle_ticks").longValue(), msg);



        //TODO
//        int modticks = (int)(simTime().dbl()/par("tick").doubleValue())%par("cycle_ticks").longValue();
//        if(modticks>(par("cycle_ticks").longValue()/2))
//            modticks=modticks-par("cycle_ticks").longValue();
//        ev << "TICKS:" << modticks << endl;
//        clockCorrection(-modticks);

        //Now the events are corrected according to the new precision
        correctEvents();
    }
}

void TTEScheduler::correctEvents(){
    for(std::list<SchedulerEvent*>::const_iterator registredEvent = registredEvents.begin(); registredEvent != registredEvents.end(); registredEvent++){
        if((*registredEvent)->getKind() == ACTION_TIME_EVENT){
            SchedulerActionTimeEvent *actionTimeEvent = (SchedulerActionTimeEvent*)*registredEvent;
            cancelEvent(actionTimeEvent);
            //TODO alles mögliche ;)
            if (actionTimeEvent->getAction_time()-50 > getTicks())
            {
                scheduleAt(lastCycleStart + par("current_tick").doubleValue() * actionTimeEvent->getAction_time(),
                        actionTimeEvent);
            }
            else
            {
                scheduleAt(lastCycleStart
                        + par("current_tick").doubleValue()
                        * (actionTimeEvent->getAction_time() + par("cycle_ticks").longValue()),
                        actionTimeEvent);
            }
        }
    }
}

void TTEScheduler::clockCorrection(int ticks){
    lastCycleStart+=SimTime(ticks*par("current_tick").doubleValue());
    //TODO Now correct the new cylce time
    //Now correct the events
    correctEvents();
}

unsigned int TTEScheduler::getTicks()
{
    return round(((simTime() - lastCycleStart) / par("current_tick").doubleValue()).dbl());
}

unsigned long TTEScheduler::getTotalTicks()
{
    return lastCycleTicks + getTicks();
}

} //namespace
