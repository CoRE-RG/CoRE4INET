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

//CoRE4INET
#include "CoRE4INET_ConfigFunctions.h"

//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

Define_Module(SimpleOscillator);

SimpleOscillator::SimpleOscillator()
{
    this->parametersInitialized = false;
    this->max_drift = 0;
    this->lastCorrection = simTime();
}

void SimpleOscillator::initialize(int stage)
{
    Oscillator::initialize(stage);

    if (stage == 0)
    {
        lastCorrection = simTime();
    }
    else if (stage == 1)
    {
        SchedulerActionTimeEvent *actionTimeEvent = new SchedulerActionTimeEvent("SimpleOscillator Scheduler Event",
                ACTION_TIME_EVENT);
        actionTimeEvent->setAction_time(0);
        actionTimeEvent->setNext_cycle(true);
        actionTimeEvent->setDestinationGate(gate("schedulerIn"));
        getPeriod()->registerEvent(actionTimeEvent);
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
        simtime_t reference_time = ((simTime() - lastCorrection) / getPeriod()->getCycleTicks());
        simtime_t drift_change = reference_time * (par("drift_change").doubleValue() / 1000000);

        simtime_t precise_tick = getPreciseTick();
        simtime_t newTick = getCurrentTick() + drift_change;

        if ((newTick - precise_tick) > this->max_drift)
            setCurrentTick(precise_tick + this->max_drift);
        else if ((newTick - precise_tick) < -this->max_drift)
            setCurrentTick(precise_tick - this->max_drift);
        else
            setCurrentTick(newTick);
        emit(currentDrift, (getCurrentTick() - precise_tick));

        lastCorrection = simTime();
        //Reregister scheduler
        getPeriod()->registerEvent(static_cast<SchedulerActionTimeEvent *>(msg));
    }
}

void SimpleOscillator::handleParameterChange(const char* parname)
{
    Oscillator::handleParameterChange(parname);
    Scheduled::handleParameterChange(parname);
    if (!parname && !parametersInitialized)
    {
        parametersInitialized = true;
    }
    if (!parname || !strcmp(parname, "max_drift"))
    {
        this->max_drift = ((parameterDoubleCheckRange(par("max_drift"), 0, DBL_MAX) / 1000000) * getPreciseTick());
    }
}

} //namespace
