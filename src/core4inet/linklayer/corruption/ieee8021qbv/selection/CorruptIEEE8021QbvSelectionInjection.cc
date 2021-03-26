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

#include <core4inet/linklayer/corruption/ieee8021qbv/selection/CorruptIEEE8021QbvSelectionInjection.h>

#include "inet/linklayer/ethernet/Ethernet.h"
//CoRE4INET
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvSelectionInjection);

void CorruptIEEE8021QbvSelectionInjection::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvSelectionBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "injectionInterval"))
    {
        this->injectionInterval = parameterDoubleCheckRange(par("injectionInterval"), 0, SIMTIME_MAX.dbl());
    }
}

void CorruptIEEE8021QbvSelectionInjection::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
    if (stage == 0)
    {
        this->handleParameterChange(nullptr);
        cMessage* msg = new cMessage("Trigger injection");
        this->selfMessageId = msg->getId();
        scheduleAt(simTime() + this->getInjectionInterval(), msg);
    }
}

void CorruptIEEE8021QbvSelectionInjection::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg->getId() == this->selfMessageId)
    {
        this->bubble("Inject");
        this->getParentModule()->bubble("Inject");
        this->performCorruption();
        outMessages.push_back(this->createInjectionMessage());
        scheduleAt(simTime() + this->getInjectionInterval(), msg);
    }
    else
    {
        CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
    }
}

simtime_t CorruptIEEE8021QbvSelectionInjection::getInjectionInterval()
{
    this->handleParameterChange("injectionInterval");
    return this->injectionInterval;
}

cMessage* CorruptIEEE8021QbvSelectionInjection::createInjectionMessage()
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
