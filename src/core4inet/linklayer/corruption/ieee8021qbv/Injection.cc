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

#include "Injection.h"

//CoRE4INET
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"
#include "core4inet/utilities/ConfigFunctions.h"
//INET
#include "inet/linklayer/ethernet/Ethernet.h"

namespace CoRE4INET {

Define_Module(Injection);

Injection::Injection()
{
    this->outMessages = std::queue<cMessage*>();
}

Injection::~Injection()
{
    while(!this->outMessages.empty())
    {
        delete this->outMessages.front();
        outMessages.pop();
    }
}

void Injection::handleParameterChange(const char* parname)
{
    IEEE8021QbvSelection::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "destAddress"))
    {
        if (par("destAddress").stdstringValue() == "auto")
        {
            this->destAddress = inet::MACAddress::generateAutoAddress();
            par("destAddress").setStringValue(this->destAddress.str());
        }
        else
        {
            this->destAddress.setAddress(par("destAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "addQTag"))
    {
        this->addQTag = par("addQTag").boolValue();
    }
    if (!parname || !strcmp(parname, "priority"))
    {
        this->priority = static_cast<uint8_t>(parameterLongCheckRange(par("priority"), 0, MAX_Q_PRIORITY));
    }
    if (!parname || !strcmp(parname, "vid"))
    {
        this->vid = static_cast<uint16_t>(parameterLongCheckRange(par("vid"), 0, MAX_VLAN_ID));
    }
    if (!parname || !strcmp(parname, "injectionInterval"))
    {
        this->injectionInterval = parameterDoubleCheckRange(par("injectionInterval"), 0, SIMTIME_MAX.dbl());
    }
    if (!parname || !strcmp(parname, "payload"))
    {
        this->payload = parameterULongCheckRange(par("payload"), 0, MAX_ETHERNET_DATA_BYTES);
    }
}

void Injection::initialize(int stage)
{
    IEEE8021QbvSelection::initialize(stage);
    if (stage == 0)
    {
        this->handleParameterChange(nullptr);
        cMessage* msg = new cMessage("Trigger injection");
        this->selfMessageId = msg->getId();
        scheduleAt(simTime() + this->getInjectionInterval(), msg);
    }
}

void Injection::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg->getId() == this->selfMessageId)
    {
        this->bubble("Inject");
        this->getParentModule()->bubble("Inject");
        outMessages.push(this->createInjectionMessage());
        scheduleAt(simTime() + this->getInjectionInterval(), msg);
    }
    else
    {
        IEEE8021QbvSelection::handleMessage(msg);
    }
}

void Injection::selectFrame()
{
    if (this->framesRequested > 0 && this->outMessages.size() > 0)
    {
        this->framesRequested--;
        cMessage* msg = outMessages.front();
        outMessages.pop();
        this->send(msg, "out");
    }
    else
    {
        IEEE8021QbvSelection::selectFrame();
    }
}

simtime_t Injection::getInjectionInterval()
{
    this->handleParameterChange("injectionInterval");
    return this->injectionInterval;
}

size_t  Injection::getPayloadBytes()
{
    this->handleParameterChange("payload");
    return this->payload;
}

cMessage* Injection::createInjectionMessage()
{
    cPacket* msg;
    cPacket *payload_packet = new cPacket();
    payload_packet->setByteLength(static_cast<int64_t>(this->getPayloadBytes()));
    if (this->addQTag)
    {
        EthernetIIFrameWithQTag *frame = new EthernetIIFrameWithQTag("IEEE 802.1Q Traffic (Injected)");
        frame->setDest(this->destAddress);
        frame->encapsulate(payload_packet);
        frame->setPcp(priority);
        frame->setVID(this->vid);
        msg = frame;
    }
    else
    {
        inet::EthernetIIFrame *frame = new inet::EthernetIIFrame("Best-Effort Traffic (Injected)", 7);
        frame->setDest(this->destAddress);
        frame->encapsulate(payload_packet);
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
