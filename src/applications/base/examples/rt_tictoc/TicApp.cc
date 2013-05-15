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
    event->setAction_time(1000);
    event->setDestinationGate(gate("schedulerIn"));
    tteScheduler->registerEvent(event);
}

void TicApp::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("schedulerIn")){
        CTFrame *frame = new TTFrame("CT-ID=100");
        MACAddress srcAddr;
        srcAddr.setAddress("03 04 05 06 00 64");
        frame->setDest(srcAddr);
        frame->setCtID(100);
        //ENDE TEST
        if (getParentModule()->getSubmodule("VL_TT_100_CTC"))
            sendDirect(frame, getParentModule()->getSubmodule("VL_TT_100_CTC")->gate("in"));

        TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        tteScheduler->registerEvent(event, true);
    }
    else{
        delete msg;
    }
}

}
