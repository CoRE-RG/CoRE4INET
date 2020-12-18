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

#include "Timing.h"

//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(Timing);

Timing::Timing()
{
    this->selfMessageIds = std::vector<uint64_t>();
}

void Timing::handleParameterChange(const char* parname)
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

void Timing::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
    if (stage == 0)
    {
        WATCH(this->delayTime);
        WATCH_VECTOR(this->selfMessageIds);
    }
}

void Timing::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && this->removeDelayedMessageId(msg->getId()))
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
    else if (msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Delay");
            this->getParentModule()->bubble("Delay");
            msg->setName((std::string(msg->getName()) + " (Delayed)").c_str());
            if (this->allowOtherTrafficDuringDelay || (this->maxOtherTrafficDelayTime > 0 && msg->getTimestamp() > this->maxOtherTrafficDelayTime))
            {
                this->framesRequested++;
                this->selectFrame();
            }
            this->selfMessageIds.push_back(msg->getId());
            msg->setTimestamp(this->getDelayTime());
            scheduleAt(simTime() + msg->getTimestamp(), msg);
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

simtime_t Timing::getDelayTime()
{
    this->handleParameterChange("delayTime");
    return this->delayTime;
}

bool Timing::removeDelayedMessageId(uint64_t messageId)
{
    bool messageIdFound = false;
    bool index = 0;
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
