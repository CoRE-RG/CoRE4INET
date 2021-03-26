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

#include <core4inet/linklayer/corruption/ieee8021qbv/selection/CorruptIEEE8021QbvSelectionTiming.h>
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvSelectionTiming);

CorruptIEEE8021QbvSelectionTiming::CorruptIEEE8021QbvSelectionTiming()
{
    this->selfMessageIds = std::vector<uint64_t>();
}

void CorruptIEEE8021QbvSelectionTiming::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvSelectionBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "delayTime"))
    {
        this->delayTime = parameterDoubleCheckRange(par("delayTime"), 0, SIMTIME_MAX.dbl());
    }
    if (!parname || !strcmp(parname, "allowOtherTrafficDuringDelay"))
    {
        this->allowOtherTrafficDuringDelay = par("allowOtherTrafficDuringDelay").boolValue();
    }
    if (!parname || !strcmp(parname, "maxOtherTrafficDelayTime"))
    {
        this->maxOtherTrafficDelayTime = parameterDoubleCheckRange(par("maxOtherTrafficDelayTime"), 0, SIMTIME_MAX.dbl());
    }
}

void CorruptIEEE8021QbvSelectionTiming::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
    if (stage == 0)
    {
        WATCH(this->delayTime);
        WATCH_VECTOR(this->selfMessageIds);
    }
}

void CorruptIEEE8021QbvSelectionTiming::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (this->removeDelayedMessageId(msg->getId()))
        {
            if (this->allowOtherTrafficDuringDelay || (this->maxOtherTrafficDelayTime > 0 && msg->getTimestamp() > this->maxOtherTrafficDelayTime))
            {
                this->outMessages.push_back(msg);
            }
            else
            {
                this->send(msg, "out");
            }
        }
        else
        {
            CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
        }
    }
    else if (msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Delay");
            this->getParentModule()->bubble("Delay");
            this->corruptionCount++;
            msg->setName((std::string(msg->getName()) + " (Delayed)").c_str());
            this->selfMessageIds.push_back(msg->getId());
            msg->setTimestamp(this->getDelayTime());
            scheduleAt(simTime() + msg->getTimestamp(), msg);
            if (this->allowOtherTrafficDuringDelay || (this->maxOtherTrafficDelayTime > 0 && msg->getTimestamp() > this->maxOtherTrafficDelayTime))
            {
                this->framesRequested++;
                this->selectFrame();
            }
        }
        else
        {
            CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
        }
    }
    else
    {
        CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
    }
}

simtime_t CorruptIEEE8021QbvSelectionTiming::getDelayTime()
{
    this->handleParameterChange("delayTime");
    return this->delayTime;
}

bool CorruptIEEE8021QbvSelectionTiming::removeDelayedMessageId(uint64_t messageId)
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
