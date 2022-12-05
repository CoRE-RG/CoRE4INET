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

#include "IEEE8021QciGateControlList.h"

//CoRE4INET
#include "core4inet/linklayer/filtering/IEEE8021Qci/gate/IEEE8021QciGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciGateControlList);

void IEEE8021QciGateControlList::handleParameterChange(const char* parname)
{
    Scheduled::handleParameterChange(parname);
    this->numGates = this->getParentModule()->par("numStreamGates").intValue();
    if (!parname || !strcmp(parname, "controlList"))
    {
        IEEE8021QbvGateControlList::handleParameterChange("controlList");
    }
}

void IEEE8021QciGateControlList::propagateGateControlElement(vector<string> gateStates)
{
    for (long i=static_cast<long>(this->numGates)-1; i>=0; i--)
    {
        IEEE8021QciGate* sg = dynamic_cast<IEEE8021QciGate*>(this->getParentModule()->getSubmodule("streamGate", i));
        if ( !strcmp(gateStates[i].c_str(), "o"))
        {
            sg->open();
        }
        if ( !strcmp(gateStates[i].c_str(), "C"))
        {
            sg->close();
        }
    }
}

} //namespace
