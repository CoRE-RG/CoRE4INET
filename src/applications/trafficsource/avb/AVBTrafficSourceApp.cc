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
#include <SRPFrame_m.h>
#include <AVBFrame_m.h>
#include "Buffer.h"
#include <Timer.h>
#include <ModuleAccess.h>

#include "SRPTable.h"

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
    streamID = (unsigned long) par("streamID").longValue();
    intervalFrames = (unsigned int) par("intervalFrames").longValue();
    payload = (unsigned int) par("payload").longValue();

    if (payload <= AVB_MINPACKETSIZE)
    {
        frameSize = AVB_MINPACKETSIZE;
    }
    else
    {
        frameSize = payload + AVB_OVERHEADSIZE;
    }

    isStreaming = false;

    avbCTC = (AVBIncoming*) getParentModule()->getSubmodule("avbCTC");


    avbOutCTC = getParentModule()->getSubmodule("avbCTC");

}

void AVBTrafficSourceApp::handleMessage(cMessage* msg)
{
    //TEST ONLY:
    if (msg->isSelfMessage() && talker)
    {
        SRPTable *srpTable = (SRPTable *) getParentModule()->getSubmodule("srpTable");
        if (srpTable)
        {
            EV << "Register Talker in node" << std::endl;
            srpTable->subscribe("listenerRegistered", this);
            srpTable->updateTalkerWithStreamId(streamID, this, new MACAddress("00:00:00:00:00:00"), SR_CLASS_A,
                    frameSize, intervalFrames);
        }
        else
        {
            throw cRuntimeError("srpTable module required for stream reservation");
        }
    }

    if (msg->arrivedOn("schedulerIn"))
    {
        if (isStreaming)
        {
            sendAVBFrame();
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
    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
    {
        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    sendDirect(outFrame, avbOutCTC->gate("in"));

    //class measurement interval = 125us
    simtime_t tick = check_and_cast<Oscillator*>(findModuleWhereverInNode("oscillator", getParentModule()))->getTick();
    simtime_t interval = SR_CLASS_A_INTERVAL / intervalFrames;

    //double interval = (AVB_CLASSMEASUREMENTINTERVAL_US / intervalFrames) / 1000000.00;
    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);

    event->setTimer((uint64_t) ceil(interval / tick));
    event->setDestinationGate(gate("schedulerIn"));
    getTimer()->registerEvent(event);
}

void AVBTrafficSourceApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent
    ();
    if (id == registerSignal("listenerRegistered"))
    {
        SRPTable::ListenerEntry *lentry = (SRPTable::ListenerEntry*) obj;

        //If talker for the desired stream, register Listener
        if (lentry->streamId == streamID)
        {
            ev << "Listener for stream " << lentry->streamId << " registered!" << std::endl;

            if (par("enabled").boolValue())
            {
                bubble("Listener registred, start streaming!");
                isStreaming = true;
                avbCTC->talker = true;
                sendAVBFrame();
            }
        }
    }
}

} /* namespace CoRE4INET */
