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

#include "Buffer.h"
#include "TTEApplicationBase.h"

using namespace TTEthernetModel;

Define_Module( Buffer);

simsignal_t Buffer::txPkSignal = SIMSIGNAL_NULL;
simsignal_t Buffer::latencySignal = SIMSIGNAL_NULL;

Buffer::~Buffer(){
    destinationGates.clear();
    receiveCallbacks.clear();
    transmitCallbacks.clear();
}

void Buffer::initialize()
{
    ev << "Initialize Buffer" << endl;
    initializeStatistics();

    //Initialize parameter cache
    handleParameterChange(NULL);
}

void Buffer::initializeStatistics()
{
    txPkSignal = registerSignal("txPk");
    latencySignal = registerSignal("latency");
}

void Buffer::recordPacketSent()
{
    emit(txPkSignal, 1L);
}

void Buffer::setIsEmpty(bool empty)
{
    if (empty)
    {
        getDisplayString().setTagArg("i", 1, "black");
    }
    else
    {
        getDisplayString().setTagArg("i", 1, "");
    }
}

void Buffer::addDestinationGate(cGate *destinationGate)
{
    destinationGates.push_back(destinationGate);
}

void Buffer::removeDestinationGate(cGate *destinationGate)
{
    destinationGates.remove(destinationGate);
}

void Buffer::addReceiveCallback(Callback *cb, TTEApplicationBase *application)
{
    receiveCallbacks[application]=cb;
}

Callback* Buffer::getReceiveCallback(TTEApplicationBase *application)
{
    if(receiveCallbacks.find(application) == receiveCallbacks.end())
        return NULL;
    return receiveCallbacks[application];
}

void Buffer::addTransmitCallback(Callback *cb, TTEApplicationBase *application)
{
    transmitCallbacks[application]=cb;
}

Callback* Buffer::getTransmitCallback(TTEApplicationBase *application)
{
    if(transmitCallbacks.find(application) == transmitCallbacks.end())
        return NULL;
    return transmitCallbacks[application];
}

EtherFrame* Buffer::getFrame(){
    return dequeue();
}

void Buffer::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        EtherFrame *frame = check_and_cast<EtherFrame *>(msg);
        //Try to correct destination mac
        if(frame->getDest().isUnspecified()){
            MACAddress mac;
            unsigned long maskedMarker= ctMarker & ctMask;
            mac.setAddressByte(0, maskedMarker>>24);
            mac.setAddressByte(1, maskedMarker>>16);
            mac.setAddressByte(2, maskedMarker>>8);
            mac.setAddressByte(3, maskedMarker);
            mac.setAddressByte(4, ctId>>8);
            mac.setAddressByte(5, ctId);
            frame->setDest(mac);
        }
        emit(latencySignal, simTime()-msg->getCreationTime());
        enqueue((EtherFrame*) frame);
        // Now execute callbacks if there are some
        for(std::map<TTEApplicationBase*,Callback*>::const_iterator iter = receiveCallbacks.begin();
                iter != receiveCallbacks.end(); ++iter){
            iter->first->executeCallback(iter->second);
        }
    }
}

void Buffer::handleParameterChange(const char* parname){
    ctMask = (unsigned long)par("ct_mask").longValue();
    ctMarker = (unsigned long)par("ct_marker").longValue();
    ctId = (unsigned long)par("ct_id").longValue();
}

void Buffer::enqueue(EtherFrame *newFrame)
{
    ev << "Buffer::enqueue not implemented" << endl;
    throw;
}

EtherFrame * Buffer::dequeue()
{
    ev << "Buffer::dequeue not implemented" << endl;
    throw;
}
