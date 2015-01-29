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

#include "CoRE4INET_Oscillator.h"

//CoRE4INET
#include "CoRE4INET_Defs.h"
#include "CoRE4INET_ConfigFunctions.h"

//INET
#include "Compat.h"

//OMNeT
#include "cwatch.h"

namespace CoRE4INET {

Define_Module(Oscillator);

simsignal_t Oscillator::currentDrift = registerSignal("currentDrift");

Oscillator::Oscillator()
{
    this->tick = 0;
    this->current_tick = 0;
    this->parametersInitialized = false;
}

void Oscillator::initialize(int stage)
{
    if (stage == 0)
    {
        WATCH(this->current_tick);
    }
}

int Oscillator::numInitStages() const
{
    return 1;
}

void Oscillator::handleParameterChange(const char* parname)
{
    if (!parname && !parametersInitialized)
    {
        parametersInitialized = true;
    }
    if (!parname || !strcmp(parname, "tick"))
    {
        this->tick = SimTime(parameterDoubleCheckRange(par("tick"), 0, MAX_TICK_LENGTH));
        this->current_tick = this->tick;
    }
}

void Oscillator::setCurrentTick(simtime_t tick_length)
{
    this->current_tick = tick_length;
}

simtime_t Oscillator::getCurrentTick() const
{
    return this->current_tick;
}
simtime_t Oscillator::getPreciseTick()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->tick;
}

} //namespace
