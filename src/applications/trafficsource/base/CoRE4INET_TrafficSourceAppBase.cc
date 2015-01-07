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

#include "CoRE4INET_TrafficSourceAppBase.h"

//CoRE4INET
#include "CoRE4INET_ConfigFunctions.h"

//INET
#include "Ethernet.h"

//OMNeT++
#include "cmessage.h"

namespace CoRE4INET {

Define_Module(TrafficSourceAppBase);

TrafficSourceAppBase::TrafficSourceAppBase()
{
    this->enabled = false;
    this->payload = 0;
}
bool TrafficSourceAppBase::isEnabled()
{
    return this->enabled;
}

size_t TrafficSourceAppBase::getPayloadBytes(){
    return this->payload;
}

void TrafficSourceAppBase::initialize()
{
    ApplicationBase::initialize();
    handleParameterChange(nullptr);
    if (isEnabled())
    {
        scheduleAt(simTime() + par("start_time").doubleValue(), new cMessage(START_MSG_NAME));
    }
}

void TrafficSourceAppBase::handleParameterChange(const char* parname)
{
    ApplicationBase::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "enabled"))
    {
        this->enabled = par("enabled").boolValue();
    }
    if (!parname || !strcmp(parname, "start_time"))
    {
        parameterDoubleCheckRange(par("start_time"), 0, MAXTIME.dbl());
    }
    if (!parname || !strcmp(parname, "payload"))
    {
        this->payload = parameterULongCheckRange(par("payload"), (MIN_ETHERNET_FRAME_BYTES - ETHER_MAC_FRAME_BYTES),
                MAX_ETHERNET_DATA_BYTES);
    }
}

}
//namespace
