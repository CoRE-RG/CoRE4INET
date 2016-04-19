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

#include "core4inet/applications/AS6802/CTApplicationBase.h"

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"
#include "core4inet/utilities/customWatch.h"
#include "core4inet/utilities/ConfigFunctions.h"

//INET
#include "inet/common/ModuleAccess.h"

namespace CoRE4INET {

CTApplicationBase::CTApplicationBase(){}

CTApplicationBase::~CTApplicationBase(){
    ctbuffers.clear();
}

void CTApplicationBase::initialize()
{
    WATCH_LISTUMAP(ctbuffers);
    ApplicationBase::initialize();
}

void CTApplicationBase::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("RCin"))
    {
        if (RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(msg->getSenderModule()))
            rcBuffer->resetBag();
    }
    ApplicationBase::handleMessage(msg);
}

void CTApplicationBase::handleParameterChange(const char* parname)
{
    ApplicationBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "buffers"))
    {
        ctbuffers.clear();
        std::vector<cModule*> modules = parameterToModuleList(par("buffers"), DELIMITERS);
        for (std::vector<cModule*>::const_iterator module = modules.begin(); module != modules.end(); ++module)
        {
            if (inet::findContainingNode(*module) != inet::findContainingNode(this))
            {
                throw cRuntimeError(
                        "Configuration problem of parameter buffers in module %s: Module: %s is not in node %s! Maybe a copy-paste problem?",
                        this->getFullName(), (*module)->getFullName(), inet::findContainingNode(this)->getFullName());
            }
            if (CTBuffer *buffer = dynamic_cast<CTBuffer*>(*module))
            {
                ctbuffers[buffer->getCTID()].push_back(buffer);
            }
        }
    }
}

} //namespace
