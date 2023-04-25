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

#ifndef __CORE4INET_CORRUPTIEEE8021QBVSELECTIONBASE_H_
#define __CORE4INET_CORRUPTIEEE8021QBVSELECTIONBASE_H_

//std
#include <vector>
//INET
#include "inet/linklayer/common/MACAddress.h"
//CoRE4INET
#include "core4inet/linklayer/shaper/IEEE8021Qbv/queueing/IEEE8021QbvQueueing.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @brief Base class for corrupting network traffic at IEEE 802.1Qbv queueing level
 *
 * @author Philipp Meyer
 */
class CorruptIEEE8021QbvQueueingBase : public virtual IEEE8021QbvQueueing
{
  protected:
    inet::MACAddress corruptionDestAddress;
    inet::MACAddress corruptionSrcAddress;
    bool corruptionWithQTag;
    uint8_t corruptionPriority;
    uint16_t corruptionVid;
    size_t corruptionCount;

  private:
    double corruptionProbability;
    double corruptionMinInterval;
    simtime_t lastCorruptionTime;
    size_t corruptionPayload;
    static simsignal_t corruptionSignal;

  protected:
    virtual void handleParameterChange(const char* parname) override;
    virtual void initialize() override;
    virtual void finish() override;
    virtual bool performCorruption();
    virtual size_t getCorruptionPayloadBytes();
    virtual bool match(cMessage *msg);

  private:
    double getCorruptionProbability();
    double getCorruptionMinInterval();
};

} //namespace

#endif
