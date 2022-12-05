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

#include "IEEE8021QbvIncoming.h"

//std
#include <string>
using namespace std;
//CoRE4INET
//Auto-generated messages
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"

namespace CoRE4INET {

Define_Module(IEEE8021QbvIncoming);

void IEEE8021QbvIncoming::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        if (const inet::EthernetIIFrame* ether2frame = dynamic_cast<const inet::EthernetIIFrame*>(msg))
        {
            if (ether2frame->getEtherType() == 0x8100)
            {
                if (const EthernetIIFrameWithQTag* qframe = dynamic_cast<const EthernetIIFrameWithQTag*>(ether2frame))
                {
                    std::list<cModule*> listeners = srptable->getListenersForTalkerAddress(qframe->getDest(),
                            qframe->getVID());
                    if (listeners.empty())
                    {
                        emit(droppedSignal, qframe);
                    }
                    else
                    {
                        for (std::list<cModule*>::const_iterator listener = listeners.begin(); listener != listeners.end();
                                ++listener)
                        {
                            if (strcmp((*listener)->getName(), par("portModule")) == 0)
                            {
                                sendDirect(qframe->dup(), 0, getHardwareDelay(), (*listener)->gate("upperLayerDirectIn"));
                                emit(rxPkSignal, qframe);
                            }
                            else
                            {
                                if ((*listener)->hasGate("AVBin"))
                                {
                                    sendDirect(qframe->dup(), (*listener)->gate("AVBin"));
                                    emit(rxPkSignal, qframe);
                                }
                                else if ((*listener)->hasGate("in"))
                                {
                                    sendDirect(qframe->dup(), (*listener)->gate("in"));
                                    emit(rxPkSignal, qframe);
                                }
                            }
                        }
                    }
                    delete qframe;
                }
                else
                {
                    throw cRuntimeError("Ethertype is 0x8100 but message type is not EthernetIIFrameWithQTag");
                }
            }
            else
            {
                throw cRuntimeError("Received non-AVBFrame frame");
            }
        }
    }
    else
    {
        delete msg;
    }
}

} //namespace
