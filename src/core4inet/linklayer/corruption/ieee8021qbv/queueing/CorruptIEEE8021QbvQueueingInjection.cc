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

#include <core4inet/linklayer/corruption/ieee8021qbv/queueing/CorruptIEEE8021QbvQueueingInjection.h>

#include "inet/linklayer/ethernet/Ethernet.h"
//CoRE4INET
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvQueueingInjection);

void CorruptIEEE8021QbvQueueingInjection::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvQueueingBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "injectionInterval"))
    {
        this->injectionInterval = parameterDoubleCheckRange(par("injectionInterval"), 0, SIMTIME_MAX.dbl());
    }
}

void CorruptIEEE8021QbvQueueingInjection::initialize()
{
    CorruptIEEE8021QbvQueueingBase::initialize();
    cMessage* msg = new cMessage("Trigger injection");
    this->selfMessageId = msg->getId();
    scheduleAt(simTime() + this->getInjectionInterval(), msg);
}

void CorruptIEEE8021QbvQueueingInjection::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg->getId() == this->selfMessageId)
    {
        this->bubble("Inject");
        this->getParentModule()->bubble("Inject");
        cMessage* injectMsg = this->createInjectionMessage();
        injectMsg->setArrival(this->getId(), this->gate("in", 0)->getId());
        CorruptIEEE8021QbvQueueingBase::handleMessage(injectMsg);
        scheduleAt(simTime() + this->getInjectionInterval(), msg);
    }
    else
    {
        CorruptIEEE8021QbvQueueingBase::handleMessage(msg);
    }
}

simtime_t CorruptIEEE8021QbvQueueingInjection::getInjectionInterval()
{
    this->handleParameterChange("injectionInterval");
    return this->injectionInterval;
}

cMessage* CorruptIEEE8021QbvQueueingInjection::createInjectionMessage()
{
    cPacket* msg;
    cPacket *payloadPacket = new cPacket();
    payloadPacket->setByteLength(static_cast<int64_t>(this->getCorruptionPayloadBytes()));
    if (this->corruptionWithQTag)
    {
        EthernetIIFrameWithQTag *frame = new EthernetIIFrameWithQTag("IEEE 802.1Q Traffic (Injected)");
        frame->setDest(this->corruptionDestAddress);
        frame->setSrc(this->corruptionSrcAddress);
        frame->encapsulate(payloadPacket);
        frame->setPcp(this->corruptionPriority);
        frame->setVID(this->corruptionVid);
        msg = frame;
    }
    else
    {
        inet::EthernetIIFrame *frame = new inet::EthernetIIFrame("Best-Effort Traffic (Injected)", 7);
        frame->setDest(this->corruptionDestAddress);
        frame->setSrc(this->corruptionSrcAddress);
        frame->encapsulate(payloadPacket);
        msg = frame;
    }
    //Padding
    if (msg->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
    {
        msg->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    return msg;
}

} //namespace
