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

#include "CoRE4INET_Incoming.h"

//CoRE4INET
#include "CoRE4INET_ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(Incoming);

simsignal_t Incoming::droppedSignal = registerSignal("droppedPk");
simsignal_t Incoming::rxPkSignal = registerSignal("rxPk");

Incoming::Incoming()
{
    hadError = false;
    this->hardware_delay = 0;
    parametersInitialized = false;
}

void Incoming::recordPacketReceived(EtherFrame *frame)
{
    emit(rxPkSignal, frame);
}

void Incoming::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        if(EtherFrame* ef = dynamic_cast<EtherFrame*>(msg))
        {
            recordPacketReceived(ef);
            sendDelayed(msg, this->hardware_delay, "out");
        }
        else
        {
            throw cRuntimeError("Message that is no EtherFrame arrived on in");
        }
    }
}

simtime_t Incoming::getHardwareDelay()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->hardware_delay;
}

void Incoming::handleParameterChange(const char* parname)
{
    if (!parametersInitialized)
    {
        parametersInitialized = true;
    }
    if (!parname || !strcmp(parname, "hardware_delay"))
    {
        this->hardware_delay = SimTime(parameterDoubleCheckRange(par("hardware_delay"), 0, DBL_MAX));
    }

}

} //namespace
