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

#include "IEEE8021QReservedTrafficSourceApp.h"

#include "core4inet/base/NotifierConsts.h"
#include "core4inet/utilities/HelperFunctions.h"
#include "core4inet/utilities/ModuleAccess.h"
#include "core4inet/utilities/ConfigFunctions.h"
//INET
#include "inet/linklayer/ethernet/Ethernet.h"

namespace CoRE4INET {

Define_Module(IEEE8021QReservedTrafficSourceApp);

IEEE8021QReservedTrafficSourceApp::IEEE8021QReservedTrafficSourceApp()
{
}

void IEEE8021QReservedTrafficSourceApp::initialize()
{
    IEEE8021QTrafficSourceApp::initialize();
    Timed::initialize();

    if (getPayloadBytes() <= (MIN_ETHERNET_FRAME_BYTES - ETHER_MAC_FRAME_BYTES - ETHER_8021Q_TAG_BYTES))
    {
        this->frameSize = MIN_ETHERNET_FRAME_BYTES;
    }
    else
    {
        this->frameSize = getPayloadBytes() + ETHER_MAC_FRAME_BYTES + ETHER_8021Q_TAG_BYTES;
    }

    this->srpTable = dynamic_cast<SRPTable *>(getModuleByPath(par("srpTable")));
    if (!srpTable)
    {
        throw cRuntimeError("srpTable module required for stream reservation");
    }
}

void IEEE8021QReservedTrafficSourceApp::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0))
    {
        EV_INFO << "Register Talker in node" << std::endl;
        this->srpTable->subscribe(NF_AVB_LISTENER_REGISTERED, this);
        this->srpTable->subscribe(NF_AVB_LISTENER_UNREGISTERED, this);
        this->srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);
        this->srpTable->updateTalkerWithStreamId(streamID, this, destAddress, srClass, frameSize,
                intervalFrames, vid, priority, isStatic);

        //Is static config active and listeners already registered for this stream?
        if(this->isStatic){
            if(this->srpTable->getListenersForStreamId(this->streamID, this->vid).empty()){
                //add a listener
                this->srpTable->updateListenerWithStreamId(this->streamID, getParentModule()->getSubmodule("phy", 0), this->vid, this->isStatic);
            }
            this->isStreaming = true;
            scheduleInterval();
            if (getEnvir()->isGUI())
            {
                bubble("Listener registered, start streaming!");
                getDisplayString().setTagArg("i2", 0, "status/active");
            }
        }
        else if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/hourglass");
        }
    }

    if (msg->arrivedOn("schedulerIn"))
    {
        if (this->isStreaming)
        {
            sendMessage();
            scheduleInterval();
        }
    }
    delete msg;
}

simtime_t IEEE8021QReservedTrafficSourceApp::getSendInterval()
{
    simtime_t interval = par("sendInterval").doubleValue();
    if(interval.isZero())
    {
        interval = (getIntervalForClass(this->srClass) / this->intervalFrames) + par("intervalInaccurracy").doubleValue();
    }
    if (interval < 0)
    {
            interval = 0;
    }
    return interval;
}

void IEEE8021QReservedTrafficSourceApp::scheduleInterval()
{
    //class measurement interval A=125us B=250us
    simtime_t tick = getOscillator()->getPreciseTick();
    simtime_t interval = getSendInterval();
    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
    event->setTimer(static_cast<uint64_t>(ceil(interval / tick)));
    event->setDestinationGate(gate("schedulerIn"));
    getTimer()->registerEvent(event);
}

void IEEE8021QReservedTrafficSourceApp::receiveSignal(cComponent* src,
        simsignal_t id, cObject* obj, cObject* details)
{
    Enter_Method_Silent();
    if (id == NF_AVB_LISTENER_REGISTERED)
    {
        SRPTable::ListenerEntry *lentry = dynamic_cast<SRPTable::ListenerEntry*>(obj);

        //If talker for the desired stream, register Listener
        if (lentry && lentry->streamId == this->streamID && lentry->vlan_id == this->vid)
        {
            EV_INFO << "Listener for stream " << lentry->streamId << " registered!" << std::endl;

            if (getEnvir()->isGUI())
            {
                bubble("Listener registered, start streaming!");
                getDisplayString().setTagArg("i2", 0, "status/active");
            }
            this->isStreaming = true;
            SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
            event->setTimer(0);
            event->setDestinationGate(gate("schedulerIn"));
            getTimer()->registerEvent(event);
        }
    }
    else if (id == NF_AVB_LISTENER_REGISTRATION_TIMEOUT || id == NF_AVB_LISTENER_UNREGISTERED)
    {
        SRPTable::ListenerEntry *lentry = dynamic_cast<SRPTable::ListenerEntry*>(obj);

        //If talker for the desired stream, unregister Listener
        if (lentry && lentry->streamId == this->streamID && lentry->vlan_id == this->vid)
        {
            //check whether there are listeners left
            if (srpTable->getListenersForStreamId(this->streamID, this->vid).size() == 0)
            {
                this->isStreaming = false;
                if (getEnvir()->isGUI())
                {
                    bubble("Last listener unregistered, stop streaming!");
                    getDisplayString().setTagArg("i2", 0, "status/hourglass");
                }
            }
        }
    }
}

void IEEE8021QReservedTrafficSourceApp::handleParameterChange(
        const char* parname)
{
    if (!parname || !strcmp(parname, "destAddress"))
    {
        if (par("destAddress").stdstringValue() == "auto")
        {
            // assign automatic address
            this->destAddress = generateAutoMulticastAddress();

            // change module parameter from "auto" to concrete address
            par("destAddress").setStringValue(this->destAddress.str());
        }
        else
        {
            this->destAddress.setAddress(par("destAddress").stringValue());
        }
    }
    //need to override the dest address value as we need a multicast destination address
    IEEE8021QTrafficSourceApp::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "srClass"))
    {
        if (strcmp(par("srClass").stringValue(), "A") == 0)
        {
            this->srClass = SR_CLASS::A;
        }
        else if (strcmp(par("srClass").stringValue(), "B") == 0)
        {
            this->srClass = SR_CLASS::B;
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
    if (!parname || !strcmp(parname, "isStatic"))
    {
        this->isStatic = par("isStatic").boolValue();
    }
}


} //namespace
