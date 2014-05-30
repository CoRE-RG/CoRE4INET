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

//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

Define_Module(CTApplicationBase);

void CTApplicationBase::initialize()
{
    //TODO: Minor watch unordered maps
    //WATCH_LISTMAP(ctbuffers);
    ApplicationBase::initialize();
}

void CTApplicationBase::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("RCin"))
    {
        RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(msg->getSenderModule());
        if (rcBuffer)
            rcBuffer->resetBag();
    }
    ApplicationBase::handleMessage(msg);
}

void CTApplicationBase::handleParameterChange(const char* parname)
{
    ApplicationBase::handleParameterChange(parname);
    ctbuffers.clear();
    std::vector<std::string> bufferPaths = cStringTokenizer(par("buffers").stringValue(), DELIMITERS).asVector();
    for (std::vector<std::string>::const_iterator bufferPath = bufferPaths.begin(); bufferPath != bufferPaths.end();
            bufferPath++)
    {
        cModule* module = simulation.getModuleByPath((*bufferPath).c_str());
        if (!module)
        {
            module = findModuleWhereverInNode((*bufferPath).c_str(), this);
        }
        if (module)
        {
            if (findContainingNode(module) != findContainingNode(this))
            {
                throw cRuntimeError(
                        "Configuration problem of buffers: Module: %s is not in node %s! Maybe a copy-paste problem?",
                        (*bufferPath).c_str(), findContainingNode(this)->getFullName());
            }
            if (CTBuffer *buffer = dynamic_cast<CTBuffer*>(module))
            {
                ctbuffers[(uint16_t) buffer->par("ct_id").longValue()].push_back(buffer);
            }
        }
        else
        {
            throw cRuntimeError("Configuration problem of buffers: Module: %s could not be resolved!",
                    (*bufferPath).c_str());
        }
    }
}

} //namespace
