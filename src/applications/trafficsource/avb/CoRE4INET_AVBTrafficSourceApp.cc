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

#include "CoRE4INET_AVBTrafficSourceApp.h"

//CoRE4INET
#include "CoRE4INET_Defs.h"
#include "CoRE4INET_HelperFunctions.h"
#include "CoRE4INET_SRPTable.h"
//INET
#include "Ethernet.h"
#include "ModuleAccess.h"
#include "EtherMACFullDuplex.h"
//Auto-generated Messages
#include "AVBFrame_m.h"

namespace CoRE4INET {

Define_Module(AVBTrafficSourceApp);

AVBTrafficSourceApp::AVBTrafficSourceApp()
{
    isStreaming = false;
    multicastMAC = generateAutoMulticastAddress();
}

void AVBTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();
    Timed::initialize();

    if     (par("srClass").str().compare("A") == 0) srClass = SR_CLASS_A;
    else if(par("srClass").str().compare("B") == 0) srClass = SR_CLASS_B;
    else                                            srClass = SR_CLASS_A;

    streamID = (unsigned long) par("streamID").longValue();
    //EtherMACFullDuplex *mac = (EtherMACFullDuplex*)getParentModule()->getSubmodule("phy",0)->getSubmodule("mac");
    //unsigned long macAdress = mac->getMACAddress().getInt();
    //static unsigned short uniqueID = 0;
    //uniqueID++;
    //streamID = (macAdress << 16) + uniqueID;

    intervalFrames = (unsigned int) par("intervalFrames").longValue();
    payload = (unsigned int) par("payload").longValue();

//TODO: Minor: Check these values
    if (payload <= (MIN_ETHERNET_FRAME_BYTES - ETHER_MAC_FRAME_BYTES - ETHER_8021Q_TAG_BYTES))
    {
        frameSize = MIN_ETHERNET_FRAME_BYTES;
    }
    else
    {
        frameSize = payload + ETHER_MAC_FRAME_BYTES + ETHER_8021Q_TAG_BYTES;
    }

    avbOutCTC = getParentModule()->getSubmodule("avbCTC");

    getDisplayString().setTagArg("i2", 0, "status/asleep");

}

void AVBTrafficSourceApp::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0))
    {
        SRPTable *srpTable = check_and_cast_nullable<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
        if (srpTable)
        {
            EV << "Register Talker in node" << std::endl;
            srpTable->subscribe("listenerRegistered", this);
            srpTable->subscribe("listenerUnregistered", this);
            srpTable->subscribe("listenerRegistrationTimeout", this);
            srpTable->updateTalkerWithStreamId(streamID, this, multicastMAC, srClass, frameSize, intervalFrames);
            getDisplayString().setTagArg("i2", 0, "status/hourglass");
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
    char name[10];
    sprintf(name, "Stream %ld", streamID);
    AVBFrame *outFrame = new AVBFrame(name);
    outFrame->setStreamID(streamID);
    outFrame->setDest(multicastMAC);

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

            bubble("Listener registered, start streaming!");
            getDisplayString().setTagArg("i2", 0, "status/active");
            isStreaming = true;
            sendAVBFrame();
        }
    }
    else if ((id == registerSignal("listenerRegistrationTimeout")) || id == registerSignal("listenerUnregistered"))
    {
        SRPTable::ListenerEntry *lentry = (SRPTable::ListenerEntry*) obj;

        //If talker for the desired stream, unregister Listener
        if (lentry->streamId == streamID)
        {
            //check whether there are listeners left
            SRPTable *srpTable = check_and_cast_nullable<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
            if (srpTable->getListenersForStreamId(streamID, 0).size() == 0)
            {
                isStreaming = false;
                bubble("Last listener unregistered, stop streaming!");
                getDisplayString().setTagArg("i2", 0, "status/hourglass");
            }
        }
    }
}

} /* namespace CoRE4INET */
