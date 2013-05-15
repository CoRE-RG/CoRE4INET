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

#include "TicApp.h"
#include "TTEScheduler.h"
#include "TTFrame_m.h"

namespace TTEthernetModel {

Define_Module(TicApp);

void TicApp::initialize()
{
    TTEApplicationBase::initialize();

    TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
    event->setAction_time(12250);
    event->setDestinationGate(gate("schedulerIn"));
    tteScheduler->registerEvent(event);
}

void TicApp::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("schedulerIn")){
        CTFrame *frame = new TTFrame("Tic");
        frame->setCtID(100);

        EV << "Sending Tic Message\n";
        std::list<Buffer*> buffer = buffers[frame->getCtID()];
        for(std::list<Buffer*>::iterator buf = buffer.begin();
                               buf!=buffer.end();buf++){
            Incoming* in = (Incoming *)(*buf)->gate("in")->getPathStartGate()->getOwner();
            sendDirect(frame->dup(), in->gate("in"));
        }
        delete frame;

        TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        tteScheduler->registerEvent(event, true);
    }
    else{
        delete msg;
    }
}

}
