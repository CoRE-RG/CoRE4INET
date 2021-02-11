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

#include <core4inet/linklayer/corruption/ieee8021qbv/queueing/CorruptIEEE8021QbvQueueingManipulation.h>

#include "inet/linklayer/ethernet/Ethernet.h"
//CoRE4INET
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvQueueingManipulation);

void CorruptIEEE8021QbvQueueingManipulation::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvQueueingBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "manipulationDestAddress"))
    {
        if (par("manipulationDestAddress").stdstringValue().empty())
        {
            this->manipulationDestAddress = inet::MACAddress::UNSPECIFIED_ADDRESS;
        }
        else
        {
            this->manipulationDestAddress.setAddress(par("manipulationDestAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "manipulationSrcAddress"))
    {
        if (par("manipulationSrcAddress").stdstringValue().empty())
        {
            this->manipulationSrcAddress = inet::MACAddress::UNSPECIFIED_ADDRESS;
        }
        else
        {
            this->manipulationSrcAddress.setAddress(par("manipulationSrcAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "manipulationPriority"))
    {
        if (par("manipulationPriority").intValue() >= 0)
        {
            this->manipulationPriority = static_cast<uint8_t>(parameterLongCheckRange(par("manipulationPriority"), 0, MAX_Q_PRIORITY));

            this->manipulationWithQTagPriority = true;
        }
        else
        {
            this->manipulationWithQTagPriority = false;
        }
    }
    if (!parname || !strcmp(parname, "manipulationPriority"))
    {
        if (par("manipulationVid").intValue() >= 0)
        {
            this->manipulationVid = static_cast<uint16_t>(parameterLongCheckRange(par("manipulationVid"), 0, MAX_VLAN_ID));
            this->manipulationWithQTagVid = true;
        }
        else
        {
            this->manipulationWithQTagVid = false;
        }
    }
    if (!parname || !strcmp(parname, "manipulationPayload"))
    {
        this->manipulationPayload = parameterULongCheckRange(par("manipulationPayload"), 0, MAX_ETHERNET_DATA_BYTES);
    }
}

void CorruptIEEE8021QbvQueueingManipulation::initialize()
{
    CorruptIEEE8021QbvQueueingBase::initialize();
}

void CorruptIEEE8021QbvQueueingManipulation::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Manipulation");
            this->getParentModule()->bubble("Manipulation");
            this->corruptionCount++;
            if (inet::EthernetIIFrame* frame = dynamic_cast<inet::EthernetIIFrame*>(msg))
            {
                cPacket* payload = frame->decapsulate();
                if (this->manipulationDestAddress != inet::MACAddress::UNSPECIFIED_ADDRESS)
                {
                    frame->setDest(this->manipulationDestAddress);
                }
                if (this->manipulationSrcAddress != inet::MACAddress::UNSPECIFIED_ADDRESS)
                {
                    frame->setSrc(this->manipulationSrcAddress);
                }
                if (frame->getEtherType() == 0x8100)
                {
                    if (EthernetIIFrameWithQTag* qframe = dynamic_cast<EthernetIIFrameWithQTag*>(frame))
                    {
                        if (this->manipulationWithQTagPriority)
                        {
                            qframe->setPcp(this->manipulationPriority);
                        }
                        if (this->manipulationWithQTagVid)
                        {
                            qframe->setVID(this->manipulationVid);
                        }
                        qframe->setByteLength(ETHER_MAC_FRAME_BYTES+4);
                    }
                    else
                    {
                        throw cRuntimeError("Ethertype is 0x8100 but message type is not EthernetIIFrameWithQTag");
                    }
                }
                else
                {
                    frame->setByteLength(ETHER_MAC_FRAME_BYTES);
                }
                if (this->getManipulationPayloadBytes() > 0)
                {
                    payload->setByteLength(this->manipulationPayload);
                }
                frame->encapsulate(payload);
                //Padding
                if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
                {
                    frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
                }
                frame->setName((std::string(frame->getName()) + " (Manipulated)").c_str());
            }
        }
    }
    CorruptIEEE8021QbvQueueingBase::handleMessage(msg);
}

size_t CorruptIEEE8021QbvQueueingManipulation::getManipulationPayloadBytes()
{
    this->handleParameterChange("manipulationPayload");
    return this->manipulationPayload;
}

} //namespace
