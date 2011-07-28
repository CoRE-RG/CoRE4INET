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

Define_Module(TTEScheduler);

void TTEScheduler::initialize()
{
	ConfigurationUtils::getPreloadedMMR();
	ecorecpp::ModelRepository_ptr mr = ecorecpp::ModelRepository::_instance();
	ConfigurationUtils::resolveCommonAliases(mr);
	::ecore::EObject_ptr eobj = mr->getByFilename(getParentModule()->par("network_configuration"));
	assert(eobj);
	NetworkConfig_ptr nc = ::ecore::instanceOf< NetworkConfig >(eobj);
	assert(nc);
	DeviceSpecification_ptr ds = ConfigurationUtils::getDeviceSpecification(getParentModule()->par("device_name").stdstringValue(),nc);
	assert(ds);

	//TODO cycle time auslesen


	if(ds->eClass()->getName() == "Switch"){
		TargetDevice_ptr td = ds->as< Switch >()->getRefDeviceMapping()->getRefTargetDevice();
		if(td->eClass()->getName() == ("TTTechIpTargetDevice")){
			TTTechIpTargetDevice_ptr iptd = td->as< TTTechIpTargetDevice >();
			par("tick_ns").setLongValue(ConfigurationUtils::freq2ns(iptd->getClockSpeed()));
			//TODO Infomessage of parameter change
		}
	}

	tick.setRaw(par("tick_ns").longValue()*pow(10,SimTime::SCALEEXP_NS-SimTime::getScaleExp()));

	//Start Timer
	scheduleAt(simTime(), new SchedulerEvent("NEW_CYCLE", NEW_CYCLE));

	lastCycleStart=simTime();
}

void TTEScheduler::registerEvent(SchedulerEvent *event){
	Enter_Method("registerEvent(SchedulerEvent %s)",event->getName());
	take(event);
	if(event->getKind() == ACTION_TIME_EVENT){
		SchedulerActionTimeEvent *actionTimeEvent = (SchedulerActionTimeEvent*)event;

		if(actionTimeEvent->getAction_time()>getTicks()){
			scheduleAt(simTime()+precision(tick*actionTimeEvent->getAction_time()),actionTimeEvent);
		}
		else{
			scheduleAt(simTime()+precision(tick*(actionTimeEvent->getAction_time()-getTicks()+par("cycle_ticks").longValue())),actionTimeEvent);
		}
	}
	else if(event->getKind() == TIMER_EVENT){
		SchedulerTimerEvent *timerEvent = (SchedulerTimerEvent*)event;;
		scheduleAt(simTime()+precision(tick*timerEvent->getTimer()),event);
	}
}


void TTEScheduler::handleMessage(cMessage *msg)
{
	if(msg->isSelfMessage() && msg->getKind() == ACTION_TIME_EVENT){
		SchedulerEvent *event= (SchedulerEvent*)msg;
		sendDirect(event,event->getDestinationGate());
	}
	else if(msg->isSelfMessage() && msg->getKind() == NEW_CYCLE){
		lastCycleStart=simTime();
		lastCycleTicks+=par("cycle_ticks").longValue();
		scheduleAt(lastCycleStart+precision(tick*par("cycle_ticks")), msg);
		//now the precision can be changed (TBD)
	}
}

unsigned int TTEScheduler::getTicks(){
	return precision(simTime()-lastCycleStart)/tick;
}

unsigned long TTEScheduler::getTotalTicks(){
    return lastCycleTicks+getTicks();
}

SimTime TTEScheduler::precision(SimTime logical){
	return logical*1.000000;
}

} //namespace
