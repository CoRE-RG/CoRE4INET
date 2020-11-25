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
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvSelectionBase);

CorruptIEEE8021QbvSelectionBase::CorruptIEEE8021QbvSelectionBase()
{
    this->outMessages = std::list<cMessage*>();
    this->savedMessages = std::list<cMessage*>();
}

CorruptIEEE8021QbvSelectionBase::~CorruptIEEE8021QbvSelectionBase()
{
    while(!this->outMessages.empty())
    {
        delete this->outMessages.front();
        outMessages.pop_front();
    }
    while(!this->savedMessages.empty())
    {
        delete this->savedMessages.front();
        savedMessages.pop_front();
    }
}

void CorruptIEEE8021QbvSelectionBase::handleParameterChange(const char* parname)
{
    IEEE8021QbvSelection::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "corruptionProbability"))
    {
        this->corruptionProbability = parameterDoubleCheckRange(par("corruptionProbability"), 0, 1);
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
        this->handleParameterChange(nullptr);
        WATCH_PTRLIST(this->outMessages);
        WATCH_PTRLIST(this->savedMessages);
    }
}

void CorruptIEEE8021QbvSelectionBase::selectFrame()
{
    if (this->framesRequested > 0 && this->outMessages.size() > 0)
    {
        this->framesRequested--;
        cMessage* msg = outMessages.front();
        outMessages.pop_front();
        this->send(msg, "out");
    }
    else
    {
        IEEE8021QbvSelection::selectFrame();
    }
}

bool CorruptIEEE8021QbvSelectionBase::performCorruption()
{
    double value = (static_cast<double>(rand()) / (RAND_MAX)); // TODO: OMNeT++ Random funktion benutzen -> fingerprints
    return value <= this->getCorruptionProbability();
}

size_t CorruptIEEE8021QbvSelectionBase::getCorruptionPayloadBytes()
{
    this->handleParameterChange("corruptionPayload");
    return this->corruptionPayload;
}

double CorruptIEEE8021QbvSelectionBase::getCorruptionProbability()
{
    this->handleParameterChange("corruptionProbability");
    return this->corruptionProbability;
}

} //namespace
