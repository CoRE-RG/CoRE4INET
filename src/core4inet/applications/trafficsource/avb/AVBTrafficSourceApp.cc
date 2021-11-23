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

#include "core4inet/applications/trafficsource/avb/AVBTrafficSourceApp.h"

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/utilities/HelperFunctions.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
#include "core4inet/base/NotifierConsts.h"
#include "core4inet/utilities/ConfigFunctions.h"
//INET
#include "inet/linklayer/ethernet/Ethernet.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/ethernet/EtherMACFullDuplex.h"
//Auto-generated Messages
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"

namespace CoRE4INET {

Define_Module(AVBTrafficSourceApp);

AVBTrafficSourceApp::AVBTrafficSourceApp()
{
    this->isStreaming = false;
    this->srClass = SR_CLASS::A;
    this->streamID = 0;
    this->frameSize = 0;
    this->intervalFrames = 0;
    this->vlan_id = 0;
    this->avbOutCTC = nullptr;
    this->multicastMAC = generateAutoMulticastAddress();
}

void AVBTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();
    Timed::initialize();

    if (getPayloadBytes() <= (MIN_ETHERNET_FRAME_BYTES - ETHER_MAC_FRAME_BYTES - ETHER_8021Q_TAG_BYTES))
    {
        frameSize = MIN_ETHERNET_FRAME_BYTES;
    }
    else
    {
        frameSize = getPayloadBytes() + ETHER_MAC_FRAME_BYTES + ETHER_8021Q_TAG_BYTES;
    }

    avbOutCTC = getParentModule()->getSubmodule("avbCTC");

}

void AVBTrafficSourceApp::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0))
    {
        SRPTable *srpTable = check_and_cast<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
        if (srpTable)
        {
            EV_INFO << "Register Talker in node" << std::endl;
            srpTable->subscribe(NF_AVB_LISTENER_REGISTERED, this);
            srpTable->subscribe(NF_AVB_LISTENER_UNREGISTERED, this);
            srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);
            srpTable->updateTalkerWithStreamId(streamID, this, multicastMAC, srClass, frameSize, intervalFrames,
                    vlan_id, pcp, isStatic);

            //Is static config active and listeners already registered for this stream?
            if(isStatic){
                if(srpTable->getListenersForStreamId(streamID, vlan_id).empty()){
                    //add a listener
                    srpTable->updateListenerWithStreamId(streamID, getParentModule()->getSubmodule("phy", 0), vlan_id, isStatic);
                }
                isStreaming = true;
                scheduleInterval();
            }

            if (getEnvir()->isGUI())
            {
                getDisplayString().setTagArg("i2", 0, "status/hourglass");
            }
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
    std::string frameName = "Stream " + std::to_string(streamID);
    AVBFrame *outFrame = new AVBFrame(frameName.c_str());
    outFrame->setTimestamp();
    outFrame->setStreamID(streamID);
    outFrame->setDest(multicastMAC);
    outFrame->setVID(vlan_id);
    outFrame->setPcp(pcp);

    cPacket *payloadPacket = new cPacket;
    payloadPacket->setTimestamp();
    payloadPacket->setByteLength(static_cast<int64_t>(getPayloadBytes()));
    outFrame->encapsulate(payloadPacket);
    //Padding
    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
    {
        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    sendDirect(outFrame, avbOutCTC->gate("in"));

    scheduleInterval();
}

void AVBTrafficSourceApp::scheduleInterval()
{
    //class measurement interval A=125us B=250us
    simtime_t tick = getOscillator()->getPreciseTick();
    simtime_t interval = (getIntervalForClass(srClass) / getIntervalFrames()) + par("intervalInaccurracy").doubleValue();
    if (interval < 0)
        interval = 0;

    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
    event->setTimer(static_cast<uint64_t>(ceil(interval / tick)));
    event->setDestinationGate(gate("schedulerIn"));
    getTimer()->registerEvent(event);
}

void AVBTrafficSourceApp::receiveSignal(__attribute__((unused))  cComponent *src, simsignal_t id, cObject *obj,
        __attribute__((unused))  cObject *details)
{
    Enter_Method_Silent();
    if (id == NF_AVB_LISTENER_REGISTERED)
    {
        SRPTable::ListenerEntry *lentry = dynamic_cast<SRPTable::ListenerEntry*>(obj);

        //If talker for the desired stream, register Listener
        if (lentry && lentry->streamId == streamID && lentry->vlan_id == vlan_id)
        {
            EV_INFO << "Listener for stream " << lentry->streamId << " registered!" << std::endl;

            if (getEnvir()->isGUI())
            {
                bubble("Listener registered, start streaming!");
                getDisplayString().setTagArg("i2", 0, "status/active");
            }
            if(!isStreaming){
                isStreaming = true;
                SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
                event->setTimer(0);
                event->setDestinationGate(gate("schedulerIn"));
                getTimer()->registerEvent(event);
            }
        }
    }
    else if (id == NF_AVB_LISTENER_REGISTRATION_TIMEOUT || id == NF_AVB_LISTENER_UNREGISTERED)
    {
        SRPTable::ListenerEntry *lentry = dynamic_cast<SRPTable::ListenerEntry*>(obj);

        //If talker for the desired stream, unregister Listener
        if (lentry && lentry->streamId == streamID && lentry->vlan_id == vlan_id)
        {
            //check whether there are listeners left
            SRPTable *srpTable = check_and_cast<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
            if (srpTable->getListenersForStreamId(streamID, vlan_id).size() == 0)
            {
                isStreaming = false;
                if (getEnvir()->isGUI())
                {
                    bubble("Last listener unregistered, stop streaming!");
                    getDisplayString().setTagArg("i2", 0, "status/hourglass");
                }
            }
        }
    }
}

void AVBTrafficSourceApp::handleParameterChange(const char* parname)
{
    TrafficSourceAppBase::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "srClass"))
    {
        if (strcmp(par("srClass").stringValue(), "A") == 0)
        {
            this->srClass = SR_CLASS::A;
            if(par("pcp").intValue() == -1){
                this->pcp = PCP_DEFAULT_SRCLASSA;
            }
        }
        else if (strcmp(par("srClass").stringValue(), "B") == 0)
        {
            this->srClass = SR_CLASS::B;
            if(par("pcp").intValue() == -1){
                this->pcp = PCP_DEFAULT_SRCLASSB;
            }
        }
        else
        {
            throw cRuntimeError("Parameter srClass of %s is %s and is only allowed to be A or B", getFullPath().c_str(),
                    par("srClass").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "streamID"))
    {
#if LONG_BIT == 32
        this->streamID = parameterULongCheckRange(par("streamID"), 0, static_cast<unsigned long>(MAX_STREAM_ID));
#else
        this->streamID = parameterULongCheckRange(par("streamID"), 0, MAX_STREAM_ID);
#endif
    }
    if (!parname || !strcmp(parname, "intervalFrames"))
    {
        this->intervalFrames = static_cast<uint16_t>(parameterULongCheckRange(par("intervalFrames"), 1,
        MAX_INTERVAL_FRAMES));
    }
    if (!parname || !strcmp(parname, "vlan_id"))
    {
        this->vlan_id = static_cast<uint16_t>(parameterULongCheckRange(par("vlan_id"), 0, MAX_VLAN_ID));
    }
    if (!parname || !strcmp(parname, "pcp"))
    {
        if(par("pcp").intValue() != -1){
            this->pcp = static_cast<uint8_t>(parameterULongCheckRange(par("pcp"), 0, MAX_Q_PRIORITY));
        }
    }
    if (!parname || !strcmp(parname, "multicastMAC"))
    {
        const char* macStr = par("multicastMAC").stringValue();
        // if string is not empty or set to auto load the address and hope its valid.
        if(!(!strcmp(macStr, "") || !strcmp(macStr, "auto"))) {
            this->multicastMAC = inet::MACAddress(macStr);
        }
        //check if still unspecified.
        if(multicastMAC.isUnspecified()){
            this->multicastMAC = generateAutoMulticastAddress();
        }
    }
    if (!parname || !strcmp(parname, "isStatic"))
    {
        this->isStatic = par("isStatic").boolValue();
    }

}

} /* namespace CoRE4INET */
