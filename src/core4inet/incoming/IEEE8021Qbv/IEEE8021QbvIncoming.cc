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
        if (AVBFrame *inFrame = dynamic_cast<AVBFrame*>(msg))
        {
            std::list<cModule*> listeners = srptable->getListenersForTalkerAddress(inFrame->getDest(),
                    inFrame->getVID());
            if (listeners.empty())
            {
                emit(droppedSignal, inFrame);
            }
            else
            {
                for (std::list<cModule*>::const_iterator listener = listeners.begin(); listener != listeners.end();
                        ++listener)
                {
                    if (strcmp((*listener)->getName(), "phy") == 0)
                    {
                        sendDirect(inFrame->dup(), 0, getHardwareDelay(), (*listener)->gate("upperLayerDirectIn"));
                        emit(rxPkSignal, inFrame);
                    }
                    else
                    {
                        if ((*listener)->hasGate("AVBin"))
                        {
                            sendDirect(inFrame->dup(), (*listener)->gate("AVBin"));
                            emit(rxPkSignal, inFrame);
                        }
                    }
                }
            }
            delete inFrame;
        }
        else
        {
            throw cRuntimeError("Received non-AVBFrame frame");
        }
    }
    else
    {
        delete msg;
    }
}

} //namespace
