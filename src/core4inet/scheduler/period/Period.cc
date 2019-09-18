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

#include "core4inet/scheduler/period/Period.h"

//Std
#include <exception>
//CoRE4INET
#include "core4inet/scheduler/timer/Timer.h"
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(Period);

simsignal_t Period::newCycle = registerSignal("newCycle");

Period::Period()
{
    cycles = 0;
    newCycleEvent = nullptr;
    timer = nullptr;
    parametersInitialized = false;
    this->cycle_ticks = 0;
    this->offset_ticks = 0;
}

void Period::initialize()
{
    WATCH(cycles);

    timer = dynamic_cast<Timer *>(gate("out")->getPathEndGate()->getOwnerModule());
    ASSERT(timer);

    newCycleEvent = new SchedulerActionTimeEvent("Period New Cycle Event", ACTION_TIME_EVENT);
    newCycleEvent->setDestinationGate(gate("schedulerIn"));
    newCycleEvent->setNext_cycle(true);
    timer->registerEvent(newCycleEvent, this);
}

void Period::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("schedulerIn") && msg->getKind() == ACTION_TIME_EVENT)
    {
        cycles++;
        emit(newCycle, 1L);
        timer->registerEvent(newCycleEvent, this);
    }
    else
    {
        delete msg;
    }
}

uint64_t Period::registerEvent(SchedulerEvent *event)
{
    if (!timer)
    {
        throw std::runtime_error("Period was not yet initialized");
    }
    if (dynamic_cast<SchedulerActionTimeEvent*>(event))
    {
        return timer->registerEvent(dynamic_cast<SchedulerActionTimeEvent*>(event), this);
    }
    else if (dynamic_cast<SchedulerTimerEvent*>(event))
    {
        return timer->registerEvent(dynamic_cast<SchedulerTimerEvent*>(event));
    }
    else
    {
        throw std::invalid_argument("Unknown event Kind");
    }
}

uint32_t Period::getTicks()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    if (!timer)
    {
        throw std::runtime_error("Period was not yet initialized");
    }
    //cycle_ticks is added to assure a positive return value
    return static_cast<uint32_t>((cycle_ticks + timer->getTotalTicks() - offset_ticks) % cycle_ticks);
}

uint64_t Period::getTotalTicks()
{
    if (!timer)
    {
        throw std::runtime_error("Period was not yet initialized");
    }
    return timer->getTotalTicks();
}

uint32_t Period::getCycles() const
{
    return cycles;
}

Timer* Period::getTimer()
{
    return timer;
}

uint32_t Period::getCycleTicks()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->cycle_ticks;
}

simtime_t Period::getCycleLength()
{
    if (!timer)
    {
        throw std::runtime_error("Period was not yet initialized");
    }
    return getCycleTicks() * timer->getOscillator()->getPreciseTick();
}

uint32_t Period::getOffsetTicks()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->offset_ticks;
}

void Period::handleParameterChange(const char* parname)
{
    if (!parametersInitialized)
    {
        parametersInitialized = true;
    }
    if (!parname || !strcmp(parname, "cycle_ticks"))
    {
        this->cycle_ticks = static_cast<uint32_t>(parameterULongCheckRange(par("cycle_ticks"), 0, MAX_CYCLE_TICKS));
    }
    if (!parname || !strcmp(parname, "offset_ticks"))
    {
        this->offset_ticks = static_cast<uint32_t>(parameterULongCheckRange(par("offset_ticks"), 0,
                par("cycle_ticks")));
    }

}

} //namespace
