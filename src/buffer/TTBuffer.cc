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

#include "TTBuffer.h"
#include <CTFrame_m.h>
#include <TTEScheduler.h>
#include <SchedulerMessageEvents_m.h>

using namespace TTEthernetModel;

Define_Module(TTBuffer);

void TTBuffer::initialize()
{
	Buffer::initialize();
	ev << "Initialize TTBuffer" << endl;
    // TODO - Generated method body

	//Test:
	CTFrame *frame = new CTFrame("CT-ID=100");
	frame->setDest("03 04 05 06 00 64");
	frame->setCtID(100);
	enqueue(frame);
	//ENDE TEST


	//Register Event
	TTEScheduler *tteScheduler = (TTEScheduler*)getParentModule()->getSubmodule("tteScheduler");
	SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("TTBuffer Scheduler Event",ACTION_TIME_EVENT);
	event->setAction_time(par("sendWindowStart"));
	event->setDestinationGate(gate("schedulerIn"));
	tteScheduler->registerEvent(event);

	setIsEmpty(true);
}

void TTBuffer::handleMessage(cMessage *msg)
{
	Buffer::handleMessage(msg);

	if(msg->arrivedOn("schedulerIn") && msg->getKind() == ACTION_TIME_EVENT){
		cMessage *outgoingMessage = dequeue();
		if(outgoingMessage){
			//Send Message
			for (std::list<cGate*>::iterator gate = destinationGates.begin();
					gate != destinationGates.end(); ++gate) {
				sendDirect(outgoingMessage->dup(), *gate);
			}
			recordPacketSent();
			delete outgoingMessage;
		}
		//Reregister scheduler
		TTEScheduler *tteScheduler = (TTEScheduler*)getParentModule()->getSubmodule("tteScheduler");
		tteScheduler->registerEvent((SchedulerEvent *)msg);
	}
}
