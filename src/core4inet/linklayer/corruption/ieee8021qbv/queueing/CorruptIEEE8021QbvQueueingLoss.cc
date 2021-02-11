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

#include <core4inet/linklayer/corruption/ieee8021qbv/queueing/CorruptIEEE8021QbvQueueingLoss.h>

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvQueueingLoss);

void CorruptIEEE8021QbvQueueingLoss::initialize()
{
    CorruptIEEE8021QbvQueueingBase::initialize();
}

void CorruptIEEE8021QbvQueueingLoss::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Loss");
            this->getParentModule()->bubble("Loss");
            this->corruptionCount++;
            delete msg;
        }
        else
        {
            CorruptIEEE8021QbvQueueingBase::handleMessage(msg);
        }
    }
    else
    {
        CorruptIEEE8021QbvQueueingBase::handleMessage(msg);
    }
}

} //namespace
