
#include "TTEOutput.h"


#include <Buffer.h>
#include <RCBuffer.h>

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
	else if(msg->arrivedOn("RCin")){
        if(framesRequested){
            //TODO: Check whether allowed to send
            framesRequested--;

            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(msg->getSenderModule());
            if(rcBuffer)
                rcBuffer->resetBag();
            send(msg,gateBaseId("out"));
        }
        else{
            int priority = msg->getSenderModule()->par("priority").longValue();
            if(priority > 0 && priority < NUM_RC_PRIORITIES){
                rcQueue[priority].insert(msg);
            }
            else{
                rcQueue[0].insert(msg);
                ev << "Priority missing!" << endl;
            }
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
	framesRequested++;

	//TTFrames
	if(!ttQueue.isEmpty()){
		framesRequested--;
		send((cMessage*)ttQueue.pop(),gateBaseId("out"));
		return;
	}
	//RCFrames
    for(int i=0;i<NUM_RC_PRIORITIES;i++){
        if(!rcQueue[i].isEmpty()){
            //TODO: Check whether allowed to send
            framesRequested--;
            EtherFrame *message = (EtherFrame*)rcQueue[i].pop();
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
            if(rcBuffer)
                rcBuffer->resetBag();
            send(message,gateBaseId("out"));
            return;
        }
    }
	//BEFrames
	if(!beQueue.isEmpty()){
	    //TODO: Check whether allowed to send
		framesRequested--;
		send((cMessage*)beQueue.pop(),gateBaseId("out"));
		return;
	}
}

int TTEOutput::getNumPendingRequests(){
	return framesRequested;
}

bool TTEOutput::isEmpty(){
    bool empty=true;
    empty&=ttQueue.isEmpty();
    for(int i=0;i<NUM_RC_PRIORITIES;i++){
        empty&=rcQueue[i].isEmpty();
    }
    empty&=beQueue.isEmpty();
	return empty;
}
void TTEOutput::clear(){
	beQueue.clear();
	for(int i=0;i<NUM_RC_PRIORITIES;i++){
        rcQueue[i].clear();
    }
	ttQueue.clear();
}


