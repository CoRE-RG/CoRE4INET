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

#include "core4inet/linklayer/filtering/IEEE8021Qci/filter/IEEE8021QciFilter.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciFilter);

void IEEE8021QciFilter::initialize()
{
    handleParameterChange(nullptr);
}

void IEEE8021QciFilter::handleMessage(cMessage *msg)
{
    IEEE8021QciGate *gate = dynamic_cast<IEEE8021QciGate*>(getParentModule()->getSubmodule("streamGate", this->gateID));
    if (!gate)
    {
        throw cRuntimeError("Cannot find gate %d configured in filter for stream %d", this->gateID, this->streamID);
    }
    IEEE8021QciCtrl* ctrl = new IEEE8021QciCtrl;
    ctrl->setStreamID(this->streamID);
    ctrl->setGateID(this->gateID);
    ctrl->setMeterID(this->meterID);
    ctrl->encapsulate(PK(msg));
    std::string ctrlName = "sID:" + std::to_string(this->streamID) + "|gID:" + std::to_string(this->gateID) + "|mID:" + std::to_string(this->meterID);
    ctrl->setName(ctrlName.c_str());
    sendDirect(ctrl, gate->gate("in"));
}

void IEEE8021QciFilter::handleParameterChange(const char *parname)
{
    if (!parname || !strcmp(parname, "streamID"))
    {
#if LONG_BIT == 32
        this->streamID = parameterULongCheckRange(par("streamID"), 0, static_cast<unsigned long>(MAX_STREAM_ID));
#else
        this->streamID = parameterULongCheckRange(par("streamID"), 0, MAX_STREAM_ID);
#endif
    }
    if (!parname || !strcmp(parname, "gateID"))
    {
        this->gateID = parameterULongCheckRange(par("gateID"), 0, UINT32_MAX);
    }
    if (!parname || !strcmp(parname, "meterID"))
    {
        this->meterID = parameterULongCheckRange(par("meterID"), 0, UINT32_MAX);
    }
}

} //namespace
