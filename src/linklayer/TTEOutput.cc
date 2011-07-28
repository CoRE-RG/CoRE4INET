
#include "TTEOutput.h"


#include <Buffer.h>
#include <TTDoubleBuffer.h>

using namespace TTEthernetModel;

Define_Module(TTEOutput);

TTEOutput::TTEOutput()
{
	framesRequested=0;
}

TTEOutput::~TTEOutput()
{

}

void TTEOutput::initialize()
{
}

void TTEOutput::handleMessage(cMessage *msg)
{
	if(msg->arrivedOn("TTin")){
		if(framesRequested){
			framesRequested--;
			send(msg,gateBaseId("out"));
		}
		else{
			ttQueue.insert(msg);
		}
	}
	//Frames arrived on in are best-effort frames
	else if(msg->arrivedOn("in")){
		// If there are framesRequested the MAC layer is currently idle
		if(framesRequested){
			//TODO: Check whether allowed to send
			framesRequested--;
			send(msg,gateBaseId("out"));
		}
		else{
			beQueue.insert(msg);
		}
	}

}

void TTEOutput::finish()
{
}

void TTEOutput::requestPacket(){
	Enter_Method("requestPacket()");
	//Feed the MAC layer with the next frame

	//TTFrames
	if(!ttQueue.isEmpty()){
		framesRequested--;
		send((cMessage*)ttQueue.pop(),gateBaseId("out"));
	}
	//RCFrames
	else if(!rcQueue.isEmpty()){
		framesRequested--;
		send((cMessage*)rcQueue.pop(),gateBaseId("out"));
	}
	//BEFrames
	else if(!beQueue.isEmpty()){
		framesRequested--;
		send((cMessage*)beQueue.pop(),gateBaseId("out"));
	}
	else{
		//If there is no frame available for transmission increase framesRequested
		framesRequested++;
	}
}

int TTEOutput::getNumPendingRequests(){
	return framesRequested;
}

bool TTEOutput::isEmpty(){
	return beQueue.isEmpty() && rcQueue.isEmpty() && ttQueue.isEmpty();
}
void TTEOutput::clear(){
	beQueue.clear();
	rcQueue.clear();
	ttQueue.clear();
}


