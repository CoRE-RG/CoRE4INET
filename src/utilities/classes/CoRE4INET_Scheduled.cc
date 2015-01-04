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

#include "CoRE4INET_Scheduled.h"

//CoRE4INET
#include "CoRE4INET_ConfigFunctions.h"

//INET
#include "ModuleAccess.h"

using namespace CoRE4INET;

Scheduled::Scheduled()
{
    this->period = NULL;
    this->parametersInitialized = false;
}

Period* Scheduled::getPeriod()
{
    if (!parametersInitialized)
    {
        handleParameterChange(NULL);
    }
    return this->period;
}

void Scheduled::handleParameterChange(const char* parname)
{
    if (!parname && !parametersInitialized)
    {
        parametersInitialized = true;
    }
    if (!parname || !strcmp(parname, "period"))
    {
        this->period = dynamic_cast<Period*>(extendedFindModuleWhereverInNode(par("period").stringValue(),
                getParentModule(), this, cModuleType::get("core4inet.scheduler.period")));
        if (!this->period)
        {
            throw cRuntimeError(
                                "Configuration problem of parameter %s in module %s: The requested period module: %s could not be found!",
                                parname, this->getFullPath().c_str(), par("period").stringValue());
        }
    }
}
