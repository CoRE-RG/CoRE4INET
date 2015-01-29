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

#include "CoRE4INET_Timed.h"

//CoRE4INET
#include "CoRE4INET_ConfigFunctions.h"

//INET
#include "ModuleAccess.h"

using namespace CoRE4INET;

Timed::Timed()
{
    this->parametersInitialized = false;
    this->oscillator = nullptr;
    this->timer = nullptr;
}

Oscillator* Timed::getOscillator()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return oscillator;
}

Timer* Timed::getTimer()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return timer;
}

void Timed::handleParameterChange(const char* parname)
{
    if (!parname && !parametersInitialized)
    {
        parametersInitialized = true;
    }
    if (!parname || !strcmp(parname, "timer"))
    {
        this->timer = extendedFindModuleWhereverInNode<Timer*>(par("timer").stringValue(), getParentModule(), this);
        if (!this->timer)
        {
            throw cRuntimeError(
                    "Configuration problem of parameter timer in module %s: The requested timer module: %s could not be found!",
                    this->getFullPath().c_str(), par("period").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "oscillator"))
    {
        this->oscillator = extendedFindModuleWhereverInNode<Oscillator*>(par("oscillator").stringValue(), getParentModule(),
                this);
        if (!this->oscillator)
        {
            throw cRuntimeError(
                    "Configuration problem of parameter %s in module %s: The requested oscillator module: %s could not be found!",
                    parname, this->getFullPath().c_str(), par("period").stringValue());
        }
    }
}
