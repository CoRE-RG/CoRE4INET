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

#include "CTApplicationBase.h"

#include "CoRE4INETDefs.h"
#include "HelperFunctions.h"

#include "RCBuffer.h"

#include <ModuleAccess.h>

namespace CoRE4INET {

Define_Module(CTApplicationBase);

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

} //namespace
