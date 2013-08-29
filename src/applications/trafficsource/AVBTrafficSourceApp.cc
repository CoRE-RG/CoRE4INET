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
    intervalFrames = par("intervalFrames").longValue();
    payload = par("payload").longValue();

    if(payload <= 46)
    {
        frameSize = 64;
    }
    else
    {
        frameSize = payload + 18;
    }

    isStreaming = false;

    avbCTC = (AVBIncoming*) getParentModule()->getSubmodule("avbCTC");

    Buffer *srpInBuffer = (Buffer*) getParentModule()->getSubmodule("srpIn");
    std::string dg = srpInBuffer->par("destination_gates");
    if(dg.empty())
        srpInBuffer->par("destination_gates") = this->gate("SRPin")->getFullPath();
    else
        srpInBuffer->par("destination_gates") = dg + "," + this->gate("SRPin")->getFullPath();

    srpOutBuffer = (Buffer*) getParentModule()->getSubmodule("srpOut");

    avbOutCTC = getParentModule()->getSubmodule("avbCTC");

    if(talker)
    {
        avbCTC->talker = true;
        TTEScheduler *scheduler = (TTEScheduler*) getParentModule()->getSubmodule("scheduler");
        SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
        event->setTimer(par("advertise_time").doubleValue()/scheduler->par("tick").doubleValue());
        event->setDestinationGate(gate("schedulerIn"));
        scheduler->registerEvent(event);
    }
}

void AVBTrafficSourceApp::handleMessage(cMessage* msg)
{
    if(msg->arrivedOn("schedulerIn"))
    {
        if(isStreaming)
        {
            sendAVBFrame();
        }
        else
        {
            bubble("Talker Advertise");

            SRPFrame *outFrame = new SRPFrame("Talker Advertise", IEEE802CTRL_DATA);
            outFrame->setStreamID(streamID);
            outFrame->setMaxFrameSize(frameSize);
            outFrame->setMaxIntervalFrames(intervalFrames);
            outFrame->setByteLength(25);

            sendDirect(outFrame, srpOutBuffer->gate("in"));
        }
        delete msg;
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
                if(srpType.compare("Listener Ready") == 0 || srpType.compare("Listener Ready Failed") == 0)
                {
                    if(!isStreaming)
                    {
                        isStreaming = true;
                        avbCTC->setAVBPortReservation(0, avbCTC->calcBandwith(frameSize, intervalFrames) + avbCTC->getAVBPortReservation(0) );
                        sendAVBFrame();
                    }
                }
            }
            //Listener:
            else
            {
                if(srpType.compare("Talker Advertise") == 0 && streamID == inFrame->getStreamID())
                {
                    SRPFrame *outFrame = new SRPFrame("Listener Ready", IEEE802CTRL_DATA);
                    outFrame->setStreamID(inFrame->getStreamID());
                    outFrame->setByteLength(8);

                    sendDirect(outFrame, srpOutBuffer->gate("in"));
                    delete msg;
                }

            }
        }
        else
        {
            delete msg;
        }
    }
}

void AVBTrafficSourceApp::sendAVBFrame()
{
    AVBFrame *outFrame = new AVBFrame("");
    outFrame->setStreamID(streamID);

    cPacket *payloadPacket = new cPacket;
    payloadPacket->setByteLength(payload);
    outFrame->encapsulate(payloadPacket);
    //Padding
    if(outFrame->getByteLength()<MIN_ETHERNET_FRAME_BYTES){
        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    //outFrame->setByteLength(frameSize);
    sendDirect(outFrame, avbOutCTC->gate("in"));

    //class measurement interval = 125us
    double interval = (125.00 / intervalFrames) / 1000000.00;
    TTEScheduler *scheduler = (TTEScheduler*) getParentModule()->getSubmodule("scheduler");
    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
    event->setTimer(interval/scheduler->par("tick").doubleValue());
    event->setDestinationGate(gate("schedulerIn"));
    scheduler->registerEvent(event);
}

} /* namespace TTEthernetModel */
