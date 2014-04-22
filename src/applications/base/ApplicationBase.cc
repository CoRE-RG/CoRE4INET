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

#include "ApplicationBase.h"

#include "CoRE4INETDefs.h"
#include "HelperFunctions.h"

#include <ModuleAccess.h>

namespace CoRE4INET {

Define_Module(ApplicationBase);

void ApplicationBase::handleMessage(cMessage *msg)
{
}

void ApplicationBase::handleParameterChange(__attribute__((unused)) const char* parname)
{
    buffers.clear();
    std::vector<std::string> bufferPaths = cStringTokenizer(par("buffers").stringValue(), DELIMITERS).asVector();
    for (std::vector<std::string>::iterator bufferPath = bufferPaths.begin(); bufferPath != bufferPaths.end();
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
                opp_error("Configuration problem of buffers: Module: %s is not in node %s! Maybe a copy-paste problem?",
                        (*bufferPath).c_str(), findContainingNode(this)->getFullName());
            }
            Buffer *buffer = dynamic_cast<Buffer*>(module);
            if (buffer && buffer->hasPar("ct_id"))
            {
                buffers[(uint16_t) buffer->par("ct_id").longValue()].push_back(buffer);
            }
            else
            {
                opp_error("Buffer module %s has no ct_id configured!", (*bufferPath).c_str());
            }
        }
        else
        {
            opp_error("Configuration problem of buffers: Module: %s could not be resolved!", (*bufferPath).c_str());
        }
    }
}

} //namespace
