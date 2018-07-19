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

#include "core4inet/linklayer/filtering/IEEE8021Qci/IEEE8021QciOutput.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciOutput);

void IEEE8021QciOutput::initialize()
{
}

void IEEE8021QciOutput::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        send(msg, "upperLayerOut");
    }
    else if (msg && msg->arrivedOn("filterIn"))
    {
        send(msg, "upperLayerOut");
    }
}

} //namespace
