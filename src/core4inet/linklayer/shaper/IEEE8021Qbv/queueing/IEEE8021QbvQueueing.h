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

#ifndef __CORE4INET_IEEE8021QBVQUEUEING_H_
#define __CORE4INET_IEEE8021QBVQUEUEING_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selection/IEEE8021QbvSelection.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @author Philipp Meyer
 */
class IEEE8021QbvQueueing : public cSimpleModule
{
  private:
    /**
     * @brief Untagged VLAN.
     * Untagged incoming frames get tagged with this VLAN. Outgoing frames with this VLAN get untagged.
     */
    uint16_t untaggedVID;
    /**
     * @brief Tagged VLANs.
     * Only outgoing frames with one of the VLANs in this list are transmitted. Default is "0" to allow for untagged frames
     */
    std::vector<int> taggedVIDs;
    unsigned int numPCP;
    unsigned int defaultPCP;

  protected:
    virtual void initialize();
    virtual void handleParameterChange(const char* parname);
    virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif
