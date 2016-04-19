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

#include "core4inet/applications/base/ApplicationBase.h"

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/buffer/base/BGBuffer.h"
#include "core4inet/utilities/ConfigFunctions.h"

//INET
#include "inet/common/ModuleAccess.h"

namespace CoRE4INET {

ApplicationBase::~ApplicationBase()
{
}

void ApplicationBase::initialize()
{
    WATCH_LIST(bgbuffers);

    std::string displayName = par("displayName").stdstringValue();
    if (getEnvir()->isGUI() && displayName.length())
    {
        getDisplayString().setTagArg("t", 0, displayName.c_str());
    }
}

void ApplicationBase::handleMessage(__attribute__((unused))   cMessage *msg)
{
}

void ApplicationBase::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "buffers"))
    {
        bgbuffers.clear();
        std::vector<cModule*> modules = parameterToModuleList(par("buffers"), DELIMITERS);
        for (std::vector<cModule*>::const_iterator module = modules.begin(); module != modules.end(); ++module)
        {
            if (inet::findContainingNode(*module) != inet::findContainingNode(this))
            {
                throw cRuntimeError(
                        "Configuration problem of parameter buffers in module %s: Module: %s is not in node %s! Maybe a copy-paste problem?",
                        this->getFullName(), (*module)->getFullName(), inet::findContainingNode(this)->getFullName());
            }
            if (BGBuffer *buffer = dynamic_cast<BGBuffer*>(*module))
            {
                bgbuffers.push_back(buffer);
            }
        }
    }
}

} //namespace
