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

#include <core4inet/linklayer/corruption/ieee8021qbv/queueing/CorruptIEEE8021QbvQueueingTiming.h>
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvQueueingTiming);

CorruptIEEE8021QbvQueueingTiming::CorruptIEEE8021QbvQueueingTiming()
{
    this->selfMessageIds = std::vector<uint64_t>();
}

void CorruptIEEE8021QbvQueueingTiming::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvQueueingBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "delayTime"))
    {
        this->delayTime = parameterDoubleCheckRange(par("delayTime"), 0, SIMTIME_MAX.dbl());
    }
}

void CorruptIEEE8021QbvQueueingTiming::initialize()
{
    CorruptIEEE8021QbvQueueingBase::initialize();
    WATCH(this->delayTime);
    WATCH_VECTOR(this->selfMessageIds);
}

void CorruptIEEE8021QbvQueueingTiming::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && this->removeDelayedMessageId(msg->getId()))
    {
        msg->setArrival(this->getId(), this->gate("in", 0)->getId());
        CorruptIEEE8021QbvQueueingBase::handleMessage(msg);
    }
    else if (msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Delay");
            this->getParentModule()->bubble("Delay");
            msg->setName((std::string(msg->getName()) + " (Delayed)").c_str());
            this->selfMessageIds.push_back(msg->getId());
            msg->setTimestamp(this->getDelayTime());
            scheduleAt(simTime() + msg->getTimestamp(), msg);
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

simtime_t CorruptIEEE8021QbvQueueingTiming::getDelayTime()
{
    this->handleParameterChange("delayTime");
    return this->delayTime;
}

bool CorruptIEEE8021QbvQueueingTiming::removeDelayedMessageId(uint64_t messageId)
{
    bool messageIdFound = false;
    uint64_t index = 0;
    for (uint64_t selfMessageId : this->selfMessageIds)
    {
        if (selfMessageId == messageId)
        {
            messageIdFound = true;
            break;
        }
        index++;
    }
    if (messageIdFound)
    {
        this->selfMessageIds.erase(this->selfMessageIds.begin() + index);
    }
    return messageIdFound;
}

} //namespace
