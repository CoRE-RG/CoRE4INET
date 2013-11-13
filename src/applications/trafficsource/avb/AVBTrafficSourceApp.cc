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
#include "Buffer.h"
#include <Timer.h>
#include <ModuleAccess.h>

#define AVB_MINPAYLOADSIZE 46
#define AVB_MINPACKETSIZE 88
#define AVB_OVERHEADSIZE 42
#define AVB_SRP_ADVERTISESIZE 25
#define AVB_SRP_READYSIZE 8
#define AVB_CLASSMEASUREMENTINTERVAL_US 125.00

namespace CoRE4INET {

Define_Module(AVBTrafficSourceApp);

void AVBTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();
    Timed::initialize();

    talker = par("talker").boolValue();
    streamID = par("streamID").longValue();
    intervalFrames = par("intervalFrames").longValue();
    payload = par("payload").longValue();

    if(payload <= AVB_MINPACKETSIZE)
    {
        frameSize = AVB_MINPACKETSIZE;
    }
    else
    {
        frameSize = payload + AVB_OVERHEADSIZE;
    }

    isStreaming = false;

    avbCTC = (AVBIncoming*) getParentModule()->getSubmodule("avbCTC");

    Buffer *srpInBuffer = dynamic_cast<Buffer*>(getParentModule()->getSubmodule("srpIn"));
    std::string dg = srpInBuffer->par("destination_gates");
    if(dg.empty())
        srpInBuffer->par("destination_gates") = this->gate("SRPin")->getFullPath();
    else
        srpInBuffer->par("destination_gates") = dg + "," + this->gate("SRPin")->getFullPath();

    srpOutBuffer = dynamic_cast<Buffer*>(getParentModule()->getSubmodule("srpOut"));

    avbOutCTC = getParentModule()->getSubmodule("avbCTC");

    if(talker && par("enabled").boolValue())
    {
        avbCTC->talker = true;
        SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
        tick = findModuleWhereverInNode("oscillator",getParentModule())->par("tick").doubleValue();
        event->setTimer(par("advertise_time").doubleValue()/tick);
        event->setDestinationGate(gate("schedulerIn"));
        getTimer()->registerEvent(event);
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
            outFrame->setByteLength(AVB_SRP_ADVERTISESIZE);

            sendDirect(outFrame, srpOutBuffer->gate("in"));
        }
    }
    else if(msg->arrivedOn("SRPin"))
    {
        std::string msgClass = msg->getClassName();
        //TODO fix that
        if(msgClass.compare("CoRE4INET::SRPFrame") == 0)
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
                    outFrame->setByteLength(AVB_SRP_READYSIZE);

                    sendDirect(outFrame, srpOutBuffer->gate("in"));
                }
            }
        }
    }
    delete msg;
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
    sendDirect(outFrame, avbOutCTC->gate("in"));

    //class measurement interval = 125us
    double interval = (AVB_CLASSMEASUREMENTINTERVAL_US / intervalFrames) / 1000000.00;
    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
    event->setTimer(ceil(interval/tick));
    event->setDestinationGate(gate("schedulerIn"));
    getTimer()->registerEvent(event);
}

} /* namespace CoRE4INET */
