//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "AVBTrafficSourceApp.h"
#include "HelperFunctions.h"
#include <CTFrame_m.h>
#include <SRPFrame_m.h>
#include "TTEScheduler.h"
#include "Buffer.h"

namespace TTEthernetModel {

Define_Module(AVBTrafficSourceApp);

void AVBTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();

    talker = par("talker").boolValue();
    if(talker)
    {
        TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("tteScheduler");
        SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
        event->setTimer(par("advertise_time").doubleValue()/tteScheduler->par("tick").doubleValue());
        event->setDestinationGate(gate("schedulerIn"));
        tteScheduler->registerEvent(event);
    }

}

void AVBTrafficSourceApp::handleMessage(cMessage* msg)
{
    if(msg->arrivedOn("schedulerIn"))
    {
        ev.printf("Talker Advertise");
        bubble("Talker Advertise");

        SRPFrame *frame = new SRPFrame("Talker Advertise", IEEE802CTRL_DATA);

        Buffer *bgBuffer = (Buffer*) getParentModule()->getSubmodule("bgOut");
        bgBuffer->par("destination_gates") = bgBuffer->gate("out")->getFullPath();
        sendDirect(frame, bgBuffer->gate("in"));
    }
    else
    {

    }

}

} /* namespace TTEthernetModel */
