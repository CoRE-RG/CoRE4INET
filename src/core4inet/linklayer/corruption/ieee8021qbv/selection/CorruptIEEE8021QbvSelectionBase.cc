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

#include "CorruptIEEE8021QbvSelectionBase.h"

//INET
#include "inet/linklayer/ethernet/Ethernet.h"
//CoRE4INET
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvSelectionBase);

simsignal_t CorruptIEEE8021QbvSelectionBase::corruptionSignal = registerSignal("corruption");

CorruptIEEE8021QbvSelectionBase::CorruptIEEE8021QbvSelectionBase()
{
    this->outMessages = std::vector<cMessage*>();
    this->lastCorruptionTime = 0;
}

CorruptIEEE8021QbvSelectionBase::~CorruptIEEE8021QbvSelectionBase()
{
    while(!this->outMessages.empty())
    {
        delete this->outMessages.front();
        this->outMessages.erase(this->outMessages.begin());
    }
}

void CorruptIEEE8021QbvSelectionBase::handleParameterChange(const char* parname)
{
    IEEE8021QbvSelection::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "corruptionProbability"))
    {
        this->corruptionProbability = parameterDoubleCheckRange(par("corruptionProbability"), 0, 1);
    }
    if (!parname || !strcmp(parname, "corruptionMinInterval"))
    {
        this->corruptionMinInterval = parameterDoubleCheckRange(par("corruptionMinInterval"), 0, SIMTIME_MAX.dbl());
    }
    if (!parname || !strcmp(parname, "corruptionDestAddress"))
    {
        if (par("corruptionDestAddress").stdstringValue().empty())
        {
            this->corruptionDestAddress = inet::MACAddress::UNSPECIFIED_ADDRESS;
        }
        else
        {
            this->corruptionDestAddress.setAddress(par("corruptionDestAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "corruptionSrcAddress"))
    {
        if (par("corruptionSrcAddress").stdstringValue().empty())
        {
            this->corruptionSrcAddress = inet::MACAddress::UNSPECIFIED_ADDRESS;
        }
        else
        {
            this->corruptionSrcAddress.setAddress(par("corruptionSrcAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "corruptionPriority") || !strcmp(parname, "corruptionVid"))
    {
        if (par("corruptionPriority").intValue() >= 0 && par("corruptionVid").intValue() >= 0)
        {
            this->corruptionPriority = static_cast<uint8_t>(parameterLongCheckRange(par("corruptionPriority"), 0, MAX_Q_PRIORITY));
            this->corruptionVid = static_cast<uint16_t>(parameterLongCheckRange(par("corruptionVid"), 0, MAX_VLAN_ID));
            this->corruptionWithQTag = true;
        }
        else
        {
            this->corruptionWithQTag = false;
        }
    }
    if (!parname || !strcmp(parname, "corruptionPayload"))
    {
        this->corruptionPayload = parameterULongCheckRange(par("corruptionPayload"), 0, MAX_ETHERNET_DATA_BYTES);
    }
}

void CorruptIEEE8021QbvSelectionBase::initialize(int stage)
{
    IEEE8021QbvSelection::initialize(stage);
    if (stage == 0)
    {
        this->corruptionCount = 0;
        WATCH(this->corruptionCount);
        WATCH_PTRVECTOR(this->outMessages);
    }
}

void CorruptIEEE8021QbvSelectionBase::finish()
{
    IEEE8021QbvSelection::finish();
    this->recordScalar("corruptions", this->corruptionCount);
}

void CorruptIEEE8021QbvSelectionBase::selectFrame()
{
    if (this->framesRequested > 0 && this->outMessages.size() > 0)
    {
        this->framesRequested--;
        cMessage* msg = this->outMessages.front();
        this->outMessages.erase(this->outMessages.begin());
        this->send(msg, "out");
    }
    else
    {
        IEEE8021QbvSelection::selectFrame();
    }
}

bool CorruptIEEE8021QbvSelectionBase::performCorruption()
{
    bool performCorruption = false;
    if ((simTime() - this->lastCorruptionTime) >= this->getCorruptionMinInterval())
    {
        if (this->getRNG(0)->doubleRandIncl1() <= this->getCorruptionProbability())
        {
            performCorruption = true;
            this->lastCorruptionTime = simTime();
            this->corruptionCount++;
            this->emit(this->corruptionSignal, true);
        }
    }
    return performCorruption;
}

size_t CorruptIEEE8021QbvSelectionBase::getCorruptionPayloadBytes()
{
    this->handleParameterChange("corruptionPayload");
    return this->corruptionPayload;
}

bool CorruptIEEE8021QbvSelectionBase::match(cMessage *msg)
{
    if (inet::EthernetIIFrame* frame = dynamic_cast<inet::EthernetIIFrame*>(msg))
    {
        if (this->corruptionDestAddress != inet::MACAddress::UNSPECIFIED_ADDRESS && this->corruptionDestAddress != frame->getDest())
        {
            return false;
        }
        if (this->corruptionSrcAddress != inet::MACAddress::UNSPECIFIED_ADDRESS && this->corruptionSrcAddress != frame->getSrc())
        {
            return false;
        }
        if (this->corruptionWithQTag)
        {
            if (frame->getEtherType() == 0x8100)
            {
                if (EthernetIIFrameWithQTag* qframe = dynamic_cast<EthernetIIFrameWithQTag*>(frame))
                {
                    if (this->corruptionPriority != qframe->getPcp())
                    {
                        return false;
                    }
                    if (this->corruptionVid != qframe->getVID())
                    {
                        return false;
                    }
                }
                else
                {
                    throw cRuntimeError("Ethertype is 0x8100 but message type is not EthernetIIFrameWithQTag");
                }
            }
            else if (!(this->corruptionPriority == 0 && this->corruptionVid == 0))
            {
                return false;
            }
        }
        if (this->getCorruptionPayloadBytes() > 0 && this->corruptionPayload != frame->getEncapsulatedPacket()->getByteLength())
        {
            return false;
        }
        return true;
    }
    return false;
}

double CorruptIEEE8021QbvSelectionBase::getCorruptionProbability()
{
    this->handleParameterChange("corruptionProbability");
    return this->corruptionProbability;
}

double CorruptIEEE8021QbvSelectionBase::getCorruptionMinInterval()
{
    this->handleParameterChange("corruptionMinInterval");
    return this->corruptionMinInterval;
}

} //namespace
