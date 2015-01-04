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

Oscillator* Timed::getOscillator()
{
    if (!parametersInitialized)
    {
        handleParameterChange(NULL);
    }
    return oscillator;
}

Timer* Timed::getTimer()
{
    if (!parametersInitialized)
    {
        handleParameterChange(NULL);
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
        this->timer = dynamic_cast<Timer*>(extendedFindModuleWhereverInNode(par("timer").stringValue(),
                getParentModule(), this, cModuleType::get("core4inet.scheduler.timer")));
        if (!this->timer)
        {
            throw cRuntimeError(
                    "Configuration problem of parameter %s in module %s: The requested timer module: %s could not be found!",
                    parname, this->getFullPath().c_str(), par("period").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "oscillator"))
    {
        this->oscillator = dynamic_cast<Oscillator*>(extendedFindModuleWhereverInNode(par("oscillator").stringValue(),
                getParentModule(), this, cModuleType::get("core4inet.scheduler.oscillator")));
        if (!this->oscillator)
        {
            throw cRuntimeError(
                    "Configuration problem of parameter %s in module %s: The requested oscillator module: %s could not be found!",
                    parname, this->getFullPath().c_str(), par("period").stringValue());
        }
    }
}
