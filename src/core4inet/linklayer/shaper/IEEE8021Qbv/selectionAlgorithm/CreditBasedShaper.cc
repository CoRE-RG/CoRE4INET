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

#include "CreditBasedShaper.h"

namespace CoRE4INET {

Define_Module(CreditBasedShaper);

simsignal_t CreditBasedShaper::creditSignal = registerSignal("credit");

CreditBasedShaper::CreditBasedShaper()
{
    this->credit = 0;
    this->queueLength = 0;
}

void CreditBasedShaper::initialize()
{
    IEEE8021QbvSelectionAlgorithm::initialize();
    Timed::initialize();
    this->handleParameterChange(nullptr);
    this->getParentModule()->getSubmodule("queue", this->getIndex())->subscribe("length", this);
    this->getParentModule()->getParentModule()->subscribe("transmitState", this);
    WATCH(credit);
    WATCH(queueLength);
}

void CreditBasedShaper::handleParameterChange(const char* parname)
{
    IEEE8021QbvSelectionAlgorithm::handleParameterChange(parname);
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
}

void CreditBasedShaper::handleMessage(cMessage *msg)
{
    // TODO
}

void CreditBasedShaper::receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details)
{
    if (strncmp(getSignalName(signalID), "transmitState", 14) == 0)
    {
        inet::EtherMACBase::MACTransmitState macTransmitState = static_cast<inet::EtherMACBase::MACTransmitState>(l);
        std::string macts = "MACts:= " + std::to_string(macTransmitState);
        this->bubble(macts.c_str());
        // TODO
    }
}

void CreditBasedShaper::receiveSignal(cComponent *source, simsignal_t signalID, unsigned long l, cObject *details)
{
    if (strncmp(getSignalName(signalID), "length", 18) == 0)
    {
        this->queueLength = l;
        std::string ql = "ql:= " + std::to_string(this->queueLength);
        this->bubble(ql.c_str());
        // TODO
    }
}

void CreditBasedShaper::idleSlope(simtime_t duration)
{
    if (duration > 0)
    {
        unsigned long reservedBandwith = this->srpTable->getBandwidthForModuleAndSRClass(this->getParentModule()->getParentModule(), this->srClass);
        this->credit += static_cast<int>(ceil(static_cast<double>(reservedBandwith) * duration.dbl()));
    }
}

void CreditBasedShaper::sendSlope(simtime_t duration)
{
    if (duration > 0)
    {

    }
}

} //namespace
