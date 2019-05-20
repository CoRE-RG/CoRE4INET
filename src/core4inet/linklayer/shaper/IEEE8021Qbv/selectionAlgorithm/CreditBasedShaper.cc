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
}

void CreditBasedShaper::initialize()
{
    Timed::initialize();
    this->handleParameterChange(nullptr);
    this->getParentModule()->getParentModule()->subscribe("transmitState", this);
    WATCH(credit);
}

void CreditBasedShaper::handleParameterChange(const char* parname)
{
    Timed::handleParameterChange(parname);
}

void CreditBasedShaper::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void CreditBasedShaper::receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details)
{
    // TODO
}

} //namespace
