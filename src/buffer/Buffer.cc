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

using namespace TTEthernetModel;


Define_Module(Buffer);


simsignal_t Buffer::txPkSignal = SIMSIGNAL_NULL;


Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

void Buffer::initialize()
{
	ev << "Initialize Buffer" << endl;
	initializeStatistics();
}

void Buffer::initializeStatistics()
{
	txPkSignal = registerSignal("txPk");
}

void Buffer::recordPacketSent(){
	emit(txPkSignal, 1L);
}

void Buffer::setIsEmpty(bool empty){
	if(empty){
		getDisplayString().setTagArg("i", 1, "black");
	}
	else{
		getDisplayString().setTagArg("i", 1, "");
	}
}

void Buffer::addDestinationGate(cGate *destinationGate)
{
	destinationGates.push_back(destinationGate);
}

void Buffer::removeDestinationGate(cGate *destinationGate){
	destinationGates.remove(destinationGate);
}

void Buffer::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
    	enqueue((EtherFrame*)msg);
    }
}

void Buffer::enqueue(EtherFrame *newFrame){
	ev << "Buffer::enqueue not implemented" << endl;
	throw;
}

EtherFrame * Buffer::dequeue(){
	ev << "Buffer::dequeue not implemented" << endl;
	throw;
}
