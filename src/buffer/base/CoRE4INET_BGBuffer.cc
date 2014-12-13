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

#include "CoRE4INET_BGBuffer.h"

namespace CoRE4INET {

//Define_Module(BGBuffer);

int BGBuffer::numInitStages() const
{
    if (Buffer::numInitStages() > 1)
        return Buffer::numInitStages();
    else
        return 1;
}

void BGBuffer::initialize(int stage)
{
    Buffer::initialize(stage);
    if (stage == 0)
    {
        if (ev.isGUI())
        {
            //Update displaystring
            getDisplayString().setTagArg("i", 0, "buffer/empty");
        }
    }
}

void BGBuffer::handleMessage(cMessage *msg)
{
    Buffer::handleMessage(msg);

    if (msg && msg->arrivedOn("in") && !destinationGates.empty())
    {
        if (EtherFrame *outgoingMessage = dequeue())
        {
            //Send Message
            for (std::list<cGate*>::const_iterator destGate = destinationGates.begin(); destGate != destinationGates.end();
                    ++destGate)
            {
                sendDirect(outgoingMessage->dup(), *destGate);
            }
            if (gate("out")->isConnected())
            {
                send(outgoingMessage->dup(), "out");
            }
            recordPacketSent(outgoingMessage);
        }
        delete msg;
    }
    else if (msg && msg->arrivedOn("in") && gate("out")->isConnected())
    {
        if (EtherFrame *outgoingMessage = dequeue())
        {
            send(outgoingMessage->dup(), "out");

            recordPacketSent(outgoingMessage);
        }
        delete msg;
    }
}

} //namespace
