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

#include "AVBAttackTrafficSourceApp.h"

namespace CoRE4INET {

Define_Module(AVBAttackTrafficSourceApp);

void AVBAttackTrafficSourceApp::initialize()
{
    AVBTrafficSourceApp::initialize();
}


void AVBAttackTrafficSourceApp::sendAVBFrame()
{
    if (this->attackPattern == 0)
    {
        AVBTrafficSourceApp::sendAVBFrame();
    }
    else
    {
        char frameNname[10];
        sprintf(frameNname, "Stream %lu", streamID);
        AVBFrame *outFrame = new AVBFrame(frameNname);
        outFrame->setTimestamp();
        outFrame->setStreamID(streamID);
        outFrame->setDest(multicastMAC);
        outFrame->setVID(vlan_id);
        cPacket *payloadPacket = new cPacket;
        payloadPacket->setTimestamp();
        payloadPacket->setByteLength(static_cast<int64_t>(getPayloadBytes()));
        outFrame->encapsulate(payloadPacket);
        //Padding
        if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
        {
            outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
        }
        sendDirect(outFrame, this->getParentModule()->getSubmodule("phy", 0)->gate("Backdoorin"));
        scheduleInterval();
    }
}

void AVBAttackTrafficSourceApp::scheduleInterval()
{
    if (this->attackPattern == 0)
    {
        AVBTrafficSourceApp::scheduleInterval();
    }
    else if (this->attackPattern == 1)
    {
        simtime_t tick = check_and_cast<Oscillator*>(findModuleWhereverInNode("oscillator", getParentModule()))->getPreciseTick();
        simtime_t interval = ((getPayloadBytes() / 1500.0) * 0.000125) + par("intervalInaccurracy").doubleValue();
        if (interval < 0)
            interval = 0;
        SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
        event->setTimer(static_cast<uint64_t>(ceil(interval / tick)));
        event->setDestinationGate(gate("schedulerIn"));
        getTimer()->registerEvent(event);
    }
}

void AVBAttackTrafficSourceApp::handleParameterChange(const char* parname)
{
    AVBTrafficSourceApp::handleParameterChange(parname);
    if(!parname || !strcmp(parname, "attackPattern"))
    {
        if (!strcmp(par("attackPattern"), "No"))
        {
            this->attackPattern = 0;
        }
        else if (!strcmp(par("attackPattern"), "SimpleSpam"))
        {
            this->attackPattern = 1;
        }
        else
        {
            throw cRuntimeError("Parameter attackPattern of %s is %s and is only allowed to be \"No\" or \"SimpleSpam\"", getFullPath().c_str(), par("attackPattern").stringValue());
        }
    }
}

} //namespace
