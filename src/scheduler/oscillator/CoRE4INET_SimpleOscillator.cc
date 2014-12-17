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

#include "CoRE4INET_SimpleOscillator.h"

//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

Define_Module(SimpleOscillator);

SimpleOscillator::SimpleOscillator(){
    this->period = NULL;
    this->lastCorrection = simTime();
}

void SimpleOscillator::initialize(int stage)
{
    Oscillator::initialize(stage);
    if (stage == 0)
    {
        if (par("period").stdstringValue().length() == 0)
        {
            par("period").setStringValue("period[0]");
        }
        period = dynamic_cast<Period*>(findModuleWhereverInNode(par("period").stringValue(), getParentModule()));
        ASSERT2(period, "cannot find period, you should specify it!");

        lastCorrection = simTime();
    }
    else if (stage == 1)
    {
        SchedulerActionTimeEvent *actionTimeEvent = new SchedulerActionTimeEvent("SimpleOscillator Scheduler Event",
                ACTION_TIME_EVENT);
        actionTimeEvent->setAction_time(0);
        actionTimeEvent->setNext_cycle(true);
        actionTimeEvent->setDestinationGate(gate("schedulerIn"));
        period->registerEvent(actionTimeEvent);
    }
}

int SimpleOscillator::numInitStages() const
{
    return 2;
}

void SimpleOscillator::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("schedulerIn") && msg->getKind() == ACTION_TIME_EVENT)
    {
        //change drift
        simtime_t reference_time = ((simTime() - lastCorrection) / period->getCycleTicks());
        ev << "ACHTUNG!!!!!!"<< endl << reference_time << "ACHTUNG!!!!!!" << endl;
        simtime_t drift_change = reference_time * (par("drift_change").doubleValue() / 1000000);

        simtime_t current_tick = getCurrentTick();
        simtime_t tick = getPreciseTick();
        simtime_t max_drift = ((par("max_drift").doubleValue()/ 1000000) * tick);

        simtime_t newTick = current_tick + drift_change;

        if ((newTick - tick) > max_drift)
            setCurrentTick(tick + max_drift);
        else if ((newTick - tick) < -max_drift)
            setCurrentTick(tick - max_drift);
        else
            setCurrentTick(newTick);
        emit(currentDrift, (getCurrentTick() - tick));

        lastCorrection = simTime();
        //Reregister scheduler
        period->registerEvent(static_cast<SchedulerActionTimeEvent *>(msg));
    }
}

} //namespace
