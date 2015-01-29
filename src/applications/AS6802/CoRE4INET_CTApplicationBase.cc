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

#include "CoRE4INET_CTApplicationBase.h"

//CoRE4INET
#include "CoRE4INET_Defs.h"
#include "CoRE4INET_RCBuffer.h"
#include "CoRE4INET_customWatch.h"
#include "CoRE4INET_ConfigFunctions.h"

//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

Define_Module(CTApplicationBase)

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
            if (findContainingNode(*module) != findContainingNode(this))
            {
                throw cRuntimeError(
                        "Configuration problem of parameter buffers in module %s: Module: %s is not in node %s! Maybe a copy-paste problem?",
                        this->getFullName(), (*module)->getFullName(), findContainingNode(this)->getFullName());
            }
            if (CTBuffer *buffer = dynamic_cast<CTBuffer*>(*module))
            {
                ctbuffers[buffer->getCTID()].push_back(buffer);
            }
        }
    }
}

} //namespace
