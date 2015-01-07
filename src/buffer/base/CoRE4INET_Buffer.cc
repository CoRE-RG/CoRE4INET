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

#include "CoRE4INET_Buffer.h"

//CORE4INET
#include "CoRE4INET_Defs.h"
#include "CoRE4INET_ConfigFunctions.h"

#include "ModuleAccess.h"

using namespace CoRE4INET;

//Define_Module(Buffer);

simsignal_t Buffer::txPkSignal = registerSignal("txPk");
simsignal_t Buffer::rxPkSignal = registerSignal("rxPk");

Buffer::Buffer()
{
    maxMessageSize = 0;
}

Buffer::~Buffer()
{
    destinationGates.clear();
}

int Buffer::numInitStages() const
{
    return 1;
}

void Buffer::initialize(int stage)
{
    if (stage == 0)
    {
        EV_DETAIL << "Initialize Buffer" << endl;

        if (ev.isGUI())
        {
            //Update displaystring
            getDisplayString().setTagArg("i", 0, "buffer/empty");
        }
    }
}

void Buffer::recordPacketSent(EtherFrame *frame)
{
    emit(txPkSignal, frame);
}

void Buffer::recordPacketReceived(EtherFrame *frame)
{
    emit(rxPkSignal, frame);
}

EtherFrame* Buffer::getFrame()
{
    return dequeue();
}

void Buffer::putFrame(EtherFrame* frame)
{
    enqueue(frame);
}

void Buffer::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        if (EtherFrame *frame = dynamic_cast<EtherFrame *>(msg))
        {
            recordPacketReceived(frame);

            if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
            {
                frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);  // "padding"
            }
            if (static_cast<size_t>(frame->getByteLength()) <= maxMessageSize)
            {
                putFrame(frame);
            }
            else
            {
                EV_ERROR << "Buffer received message with larger size than maxMessageSize" << endl;
            }
        }
        else
        {
            throw cRuntimeError("received Message on gate in that is no EtherFrame");
        }
    }
}

void Buffer::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "maxMessageSize"))
    {
        this->maxMessageSize = static_cast<size_t>(parameterULongCheckRange(par("maxMessageSize"),
                MIN_ETHERNET_FRAME_BYTES, MAX_ETHERNET_FRAME_BYTES));
    }
    if (!parname || !strcmp(parname, "destination_gates"))
    {
        destinationGates.clear();
        std::vector<cGate*> gates = parameterToGateList(par("destination_gates"), DELIMITERS);
        for (std::vector<cGate*>::const_iterator gate_it = gates.begin(); gate_it != gates.end(); ++gate_it)
        {
            if (findContainingNode((*gate_it)->getOwnerModule()) != findContainingNode(this))
            {
                throw cRuntimeError(
                        "Configuration problem of parameter destination_gates in module %s: Gate: %s is not in node %s! Maybe a copy-paste problem?",
                        this->getFullName(), (*gate_it)->getFullName(), findContainingNode(this)->getFullName());
            }
            destinationGates.push_back(*gate_it);
        }
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"

void Buffer::enqueue(__attribute__((unused)) EtherFrame *newFrame)
{
    throw cRuntimeError("Buffer::enqueue not implemented");
}

EtherFrame * Buffer::dequeue()
{
    throw cRuntimeError("Buffer::dequeue not implemented");
}

#pragma GCC diagnostic pop

long Buffer::getRequiredBandwidth()
{
    return -1;
}

size_t Buffer::getMaxMessageSize()
{
    return this->maxMessageSize;
}
