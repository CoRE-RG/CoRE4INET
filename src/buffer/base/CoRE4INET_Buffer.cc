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
#include "CoRE4INET_Defs.h"

#include "CoRE4INET_HelperFunctions.h"

#include "ModuleAccess.h"

using namespace CoRE4INET;

//Define_Module(Buffer);

simsignal_t Buffer::txPkSignal = registerSignal("txPk");
simsignal_t Buffer::rxPkSignal = registerSignal("rxPk");

Buffer::Buffer(){
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

        maxMessageSize = par("maxMessageSize").longValue();

        if (ev.isGUI())
        {
            //Update displaystring
            getDisplayString().setTagArg("i", 0, "buffer/empty");
        }
    }
}

void Buffer::recordPacketSent(inet::EtherFrame *frame)
{
    emit(txPkSignal, frame);
}

void Buffer::recordPacketReceived(inet::EtherFrame *frame)
{
    emit(rxPkSignal, frame);
}

inet::EtherFrame* Buffer::getFrame()
{
    return dequeue();
}

void Buffer::putFrame(inet::EtherFrame* frame)
{
    enqueue(frame);
}

void Buffer::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        inet::EtherFrame *frame = check_and_cast<inet::EtherFrame *>(msg);
        recordPacketReceived(frame);

        if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
        {
            frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);  // "padding"
        }
        if(frame->getByteLength()<=maxMessageSize){
            putFrame((inet::EtherFrame*) frame);
        }
        else{
            EV_ERROR << "Buffer received message with larger size than maxMessageSize" << endl;
        }
    }
}

void Buffer::handleParameterChange(__attribute((unused)) const char* parname)
{
    maxMessageSize = par("maxMessageSize").longValue();

    destinationGates.clear();
    std::vector<std::string> destinationGatePaths =
            cStringTokenizer(par("destination_gates").stringValue(), DELIMITERS).asVector();
    for (std::vector<std::string>::const_iterator destinationGatePath = destinationGatePaths.begin();
            destinationGatePath != destinationGatePaths.end(); destinationGatePath++)
    {
        cGate* gate = gateByFullPath((*destinationGatePath));
        if (!gate)
        {
            gate = gateByShortPath((*destinationGatePath), this);
        }
        if (gate)
        {
            if (inet::findContainingNode(gate->getOwnerModule()) != inet::findContainingNode(this))
            {
                throw cRuntimeError(
                        "Configuration problem of destination_gates: Gate: %s is not in node %s! Maybe a copy-paste problem?",
                        (*destinationGatePath).c_str(), inet::findContainingNode(this)->getFullName());
            }
            destinationGates.push_back(gate);
        }
        else
        {
            throw cRuntimeError("Configuration problem of destination_gates: Gate: %s could not be resolved!",
                    (*destinationGatePath).c_str());
        }
    }
}

void Buffer::enqueue(__attribute((unused))   inet::EtherFrame *newFrame)
{
    throw cRuntimeError("Buffer::enqueue not implemented");
}

inet::EtherFrame * Buffer::dequeue()
{
    throw cRuntimeError("Buffer::dequeue not implemented");
}

long Buffer::getRequiredBandwidth(){
    return -1;
}
