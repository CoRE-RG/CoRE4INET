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

#include "BGBuffer.h"
#include "ApplicationBase.h"

namespace TTEthernetModel {

Define_Module(BGBuffer);

void BGBuffer::initialize()
{
    //Update displaystring
    setIsEmpty(true);
}

void BGBuffer::handleMessage(cMessage *msg)
{
    Buffer::handleMessage(msg);

    if (msg->arrivedOn("in") && destinationGates.size() > 0)
    {
        EtherFrame *outgoingMessage = dequeue();

        if(outgoingMessage){
            //Send Message
            for (std::list<cGate*>::iterator destGate = destinationGates.begin(); destGate != destinationGates.end(); ++destGate)
            {
                sendDirect(outgoingMessage->dup(), *destGate);
            }
            if(gate("out")->isConnected()){
                send(outgoingMessage->dup(),"out");
            }
            //TODO: Message was not really transmitted! Maybe we find a better moment to execute the callback
            for(std::map<ApplicationBase*,Callback*>::const_iterator iter = transmitCallbacks.begin();
                    iter != transmitCallbacks.end(); ++iter){
                iter->first->executeCallback(iter->second);
            }
            recordPacketSent(outgoingMessage);
            delete msg;
        }
    }
}

} //namespace
