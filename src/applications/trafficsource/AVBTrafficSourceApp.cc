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
#include <AVBFrame_m.h>
#include "TTEScheduler.h"
#include "Buffer.h"

namespace TTEthernetModel {

Define_Module(AVBTrafficSourceApp);

void AVBTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();

    talker = par("talker").boolValue();
    streamID = par("streamID").longValue();

    Buffer *srpInBuffer = (Buffer*) getParentModule()->getSubmodule("srpIn");
    srpInBuffer->par("destination_gates") = this->gate("SRPin")->getFullPath();

    srpOutBuffer = (Buffer*) getParentModule()->getSubmodule("srpOut");

    avbOutCTC = getParentModule()->getSubmodule("avbCTC");

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
        bubble("Talker Advertise");

        SRPFrame *outFrame = new SRPFrame("Talker Advertise", IEEE802CTRL_DATA);
        outFrame->setStreamID(streamID);

        sendDirect(outFrame, srpOutBuffer->gate("in"));
    }
    else if(msg->arrivedOn("SRPin"))
    {
        std::string msgClass = msg->getClassName();
        if(msgClass.compare("TTEthernetModel::SRPFrame") == 0)
        {
            SRPFrame *inFrame = (SRPFrame*) msg;
            std::string srpType = inFrame->getName();
            bubble(inFrame->getName());
            if(talker)
            {
                if(srpType.compare("Listener Ready") == 0)
                {
                    AVBFrame *outFrame = new AVBFrame();
                    sendDirect(outFrame, avbOutCTC->gate("in"));
                }
            }
            //Listener:
            else
            {
                if(srpType.compare("Talker Advertise") == 0)
                {
                    SRPFrame *outFrame = new SRPFrame("Listener Ready", IEEE802CTRL_DATA);
                    outFrame->setStreamID(inFrame->getStreamID());

                    sendDirect(outFrame, srpOutBuffer->gate("in"));
                }

            }
        }
        else
        {
            delete msg;
        }
    }

}

} /* namespace TTEthernetModel */
