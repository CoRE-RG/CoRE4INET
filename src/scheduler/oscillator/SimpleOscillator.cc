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

#include "SimpleOscillator.h"

#include <ModuleAccess.h>

namespace TTEthernetModel {

Define_Module(SimpleOscillator);

void SimpleOscillator::initialize(int stage)
{
    Oscillator::initialize(stage);
    if(stage==0){
        if(par("period").stdstringValue().length()==0){
            par("period").setStringValue("period[0]");
        }
        period = dynamic_cast<Period*>(findModuleWhereverInNode(par("period").stringValue(), getParentModule()));
        ASSERT2(period, "cannot find period, you should specify it!");

        lastCorrection = simTime();
    }
    else if(stage==1){
        SchedulerActionTimeEvent *actionTimeEvent = new SchedulerActionTimeEvent("SimpleOscillator Scheduler Event", ACTION_TIME_EVENT);
        actionTimeEvent->setAction_time(0);
        actionTimeEvent->setNext_cycle(true);
        actionTimeEvent->setDestinationGate(gate("schedulerIn"));
        period->registerEvent(actionTimeEvent);
    }
}

int SimpleOscillator::numInitStages() const{
    return 2;
}

void SimpleOscillator::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("schedulerIn") && msg->getKind() == ACTION_TIME_EVENT){
        //change drift
        double reference_time = ((simTime()-lastCorrection).dbl() / period->par("cycle_ticks").doubleValue());
        double drift_change = reference_time*(par("drift_change").doubleValue()/1000000);


        double current_tick = par("current_tick").doubleValue();
        double tick = par("tick").doubleValue();
        double max_drift = (par("max_drift").doubleValue()*par("tick").doubleValue()/1000000);

        double newTick = current_tick+drift_change;

        if((newTick-tick)>max_drift)
            par("current_tick").setDoubleValue(tick+max_drift);
        else if((newTick-tick)<-max_drift)
            par("current_tick").setDoubleValue(tick-max_drift);
        else
            par("current_tick").setDoubleValue(newTick);
        emit(currentDrift, (par("current_tick").doubleValue()-tick));


        lastCorrection = simTime();
        //Reregister scheduler
        period->registerEvent(static_cast<SchedulerActionTimeEvent *>(msg));
    }
}


simtime_t SimpleOscillator::getTick(){
    return SimTime(par("current_tick").doubleValue());
}

} //namespace
