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

#ifndef __CORE4INET_INJECTION_H_
#define __CORE4INET_INJECTION_H_

//CoRE4INET
#include "core4inet/linklayer/corruption/ieee8021qbv/CorruptIEEE8021QbvSelectionBase.h"
//INET
#include "inet/linklayer/common/MACAddress.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class Injection : public virtual CorruptIEEE8021QbvSelectionBase
{
  private:
    inet::MACAddress destAddress;
    bool addQTag;
    uint8_t priority;
    uint16_t vid;
    simtime_t injectionInterval;
    size_t payload;
    uint64_t selfMessageId;

  protected:
    virtual void handleParameterChange(const char* parname) override;
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

  private:
    simtime_t getInjectionInterval();
    size_t  getPayloadBytes();
    cMessage* createInjectionMessage();
};

} //namespace

#endif
