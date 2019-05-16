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

#include "IEEE8021QbvSelection.h"

//std
#include <limits>
//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/buffer/base/Buffer.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selectionAlgorithm/IEEE8021QbvSelectionAlgorithm.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/gate/IEEE8021QbvGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QbvSelection);

IEEE8021QbvSelection::IEEE8021QbvSelection()
{
    this->framesRequested = 0;
}

void IEEE8021QbvSelection::initialize()
{
    this->handleParameterChange(nullptr);
}

void IEEE8021QbvSelection::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "numPCP"))
    {
        this->numPCP = parameterULongCheckRange(par("numPCP"), 1, std::numeric_limits<unsigned int>::max());
    }
}

void IEEE8021QbvSelection::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void IEEE8021QbvSelection::reportPacket()
{
    Enter_Method("reportPacket()");
    if (this->framesRequested > 0)
    {
        if (cMessage* msg = selectFrame())
        {
            this->framesRequested--;
            this->send(msg, "out");
        }
    }
}

void IEEE8021QbvSelection::requestPacket()
{
    Enter_Method("requestPacket()");
    this->framesRequested++;
    if (cMessage* msg = selectFrame())
    {
        this->framesRequested--;
        this->send(msg, "out");
    }
}

cMessage* IEEE8021QbvSelection::selectFrame()
{
    for(unsigned int i=numPCP-1; i>=0; i--)
    {
        Buffer* queue = dynamic_cast<Buffer*>(this->getParentModule()->getSubmodule("queue", i));
        IEEE8021QbvSelectionAlgorithm* tsa = dynamic_cast<IEEE8021QbvSelectionAlgorithm*>(this->getParentModule()->getSubmodule("transmissionSelectionAlgorithm", i));
        IEEE8021QbvGate* tg = dynamic_cast<IEEE8021QbvGate*>(this->getParentModule()->getSubmodule("transmissionGate", i));
        if (queue->size() > 0 && tsa->isOpen() && tg->isOpen())
        {
            return queue->getFrame();
        }
    }
    return nullptr;
}

} //namespace
