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

#include "core4inet/linklayer/filtering/IEEE8021Qci/gate/IEEE8021QciGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciGate);

void IEEE8021QciGate::initialize()
{
    handleParameterChange(nullptr);
    WATCH(state);
}

void IEEE8021QciGate::handleMessage(cMessage *msg)
{
    if (state == IEEE8021QciGateState::OPEN)
    {
        IEEE8021QciCtrl* ctrl = dynamic_cast<IEEE8021QciCtrl*>(msg);
        if (!ctrl)
        {
            throw cRuntimeError("No filtering ctrl header");
        }
        IEEE8021QciMeter* meter = dynamic_cast<IEEE8021QciMeter*>(getParentModule()->getSubmodule("flowmeters", ctrl->getMeterID()));
        if (!meter)
        {
            throw cRuntimeError("Cannot find meter %d configured in filter for stream %d", ctrl->getMeterID(), ctrl->getStreamID());
        }
        sendDirect(msg, meter->gate("input"));
    }
    else if (state == IEEE8021QciGateState::CLOSE)
    {
        delete msg;
    }
}

void IEEE8021QciGate::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "state"))
    {
        if (!strcmp(par("state").stringValue(), "O"))
        {
            this->state = IEEE8021QciGateState::OPEN;
        }
        else if (!strcmp(par("state").stringValue(), "C"))
        {
            this->state = IEEE8021QciGateState::CLOSE;
        }
        else
        {
            throw cRuntimeError("Parameter state of %s is %s and is only allowed to be O or C", getFullPath().c_str(), par("state").stringValue());
        }
    }
}

} //namespace
