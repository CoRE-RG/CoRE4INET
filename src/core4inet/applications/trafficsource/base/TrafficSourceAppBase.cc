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

#include "core4inet/applications/trafficsource/base/TrafficSourceAppBase.h"

//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

//INET
#include "inet/linklayer/ethernet/Ethernet.h"

namespace CoRE4INET {

simsignal_t TrafficSourceAppBase::sigPayload = registerSignal("payloadSignal");

TrafficSourceAppBase::TrafficSourceAppBase()
{
    this->enabled = false;
    this->payload = 0;
}

TrafficSourceAppBase::~TrafficSourceAppBase()
{

}


bool TrafficSourceAppBase::isEnabled()
{
    return par("enabled").boolValue() && (stopTime < SIMTIME_ZERO || stopTime > simTime());
}

size_t TrafficSourceAppBase::getPayloadBytes(){
    handleParameterChange("payload");
    emit(sigPayload,static_cast<unsigned long>(this->payload));
    return this->payload;
}

void TrafficSourceAppBase::initialize()
{
    ApplicationBase::initialize();
    handleParameterChange(nullptr);
    startTime = par("startTime").doubleValue();
    stopTime = par("stopTime").doubleValue();
    if (stopTime > SIMTIME_ZERO && stopTime < startTime)
    {
        throw cRuntimeError("Invalid startTime/stopTime parameters");
    }
    if (isEnabled())
    {
        scheduleAt(simTime() + startTime, new cMessage(START_MSG_NAME));
        if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/asleep");
        }
    }
    else
    {
        if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/stop");
        }
    }
}

void TrafficSourceAppBase::handleParameterChange(const char* parname)
{
    ApplicationBase::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "enabled"))
    {
        this->enabled = par("enabled").boolValue();
    }
    if (!parname || !strcmp(parname, "startTime"))
    {
        parameterDoubleCheckRange(par("startTime"), 0, SIMTIME_MAX.dbl());
    }
    if (!parname || !strcmp(parname, "payload"))
    {
        this->payload = parameterULongCheckRange(par("payload"), 0,
                MAX_ETHERNET_DATA_BYTES);
    }
}

}
//namespace
