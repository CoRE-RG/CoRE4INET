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

//std
#include <queue>
#include <deque>
//OMNeT++
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selection/IEEE8021QbvSelection.h"
//INET
#include "inet/linklayer/common/MACAddress.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class Injection : public virtual IEEE8021QbvSelection
{
  private:
    inet::MACAddress destAddress;
    bool addQTag;
    uint8_t priority;
    uint16_t vid;
    simtime_t injectionInterval;
    size_t payload;
    std::queue<cMessage*> outMessages;
    uint64_t selfMessageId;

  public:
    Injection();
    virtual ~Injection();

  protected:
    virtual void handleParameterChange(const char* parname) override;
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void selectFrame() override;

  private:
    simtime_t getInjectionInterval();
    size_t  getPayloadBytes();
    cMessage* createInjectionMessage();
};

} //namespace

#endif
