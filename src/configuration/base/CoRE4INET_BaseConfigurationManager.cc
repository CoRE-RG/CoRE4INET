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

#include "CoRE4INET_BaseConfigurationManager.h"

//OMNeT++
#include "cmessage.h"

namespace CoRE4INET {

Define_Module(BaseConfigurationManager);

void BaseConfigurationManager::initialize()
{
    //Generate start message to delete module
    scheduleAt(simTime(), new cMessage("Delete Module"));
}

void BaseConfigurationManager::handleMessage(cMessage *msg)
{
    //delete module on first message, it is not needed anymore;
    delete msg;
    deleteModule();
}

} //namespace
