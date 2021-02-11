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

#ifndef __CORE4INET_LOSS_H_
#define __CORE4INET_LOSS_H_

//CoRE4INET
#include "core4inet/linklayer/corruption/ieee8021qbv/queueing/CorruptIEEE8021QbvQueueingBase.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class CorruptIEEE8021QbvQueueingLoss : public virtual CorruptIEEE8021QbvQueueingBase
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

} //namespace

#endif
