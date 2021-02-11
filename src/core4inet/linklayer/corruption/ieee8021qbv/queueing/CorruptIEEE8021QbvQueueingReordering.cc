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

#include <core4inet/linklayer/corruption/ieee8021qbv/queueing/CorruptIEEE8021QbvQueueingReordering.h>
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/utilities/customWatch.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvQueueingReordering);

CorruptIEEE8021QbvQueueingReordering::CorruptIEEE8021QbvQueueingReordering()
{
    this->outMessages = std::vector<cMessage*>();
    this->takenMessages = std::map<cMessage*, uint32_t>();
}

CorruptIEEE8021QbvQueueingReordering::~CorruptIEEE8021QbvQueueingReordering()
{
    while(!this->outMessages.empty())
    {
        delete this->outMessages.front();
        this->outMessages.erase(this->outMessages.begin());
    }
    for (std::map<cMessage*, uint32_t>::iterator it = this->takenMessages.begin(); it != this->takenMessages.end();)
    {
        delete it->first;
        this->takenMessages.erase(it++);
    }
}

void CorruptIEEE8021QbvQueueingReordering::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvQueueingBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "numberOfFramesBeforeInjection"))
    {
        this->numberOfFramesBeforeInjection = parameterULongCheckRange(par("numberOfFramesBeforeInjection"), 0, std::numeric_limits<uint32_t>::max());
    }
    if (!parname || !strcmp(parname, "matchStreamForFrameCounting"))
    {
        this->matchStreamForFrameCounting = par("matchStreamForFrameCounting").boolValue();
    }
    if (!parname || !strcmp(parname, "injectTakenFramesWithRandomOrder"))
    {
        this->injectTakenFramesWithRandomOrder = par("injectTakenFramesWithRandomOrder").boolValue();
    }
}

void CorruptIEEE8021QbvQueueingReordering::initialize()
{
    CorruptIEEE8021QbvQueueingBase::initialize();
    WATCH_KEYPTRMAP(this->takenMessages);
}

void CorruptIEEE8021QbvQueueingReordering::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Reorder");
            this->getParentModule()->bubble("Reorder");
            this->corruptionCount++;
            msg->setName((std::string(msg->getName()) + " (Reordered)").c_str());
            this->takenMessages[msg] = 0;
        }
        else
        {
            if (this->matchStreamForFrameCounting && this->match(msg))
            {
                this->incrementPassedFramesCounters();
            }
            else if (!this->matchStreamForFrameCounting)
            {
                this->incrementPassedFramesCounters();
            }
            CorruptIEEE8021QbvQueueingBase::handleMessage(msg);
            this->injectReadyMessages(this->getNumberOfFramesBeforeInjection());
        }
    }
    else
    {
        CorruptIEEE8021QbvQueueingBase::handleMessage(msg);
    }
}

uint32_t CorruptIEEE8021QbvQueueingReordering::getNumberOfFramesBeforeInjection()
{
    this->handleParameterChange("numberOfFramesBeforeInjection");
    return this->numberOfFramesBeforeInjection;
}

void CorruptIEEE8021QbvQueueingReordering::incrementPassedFramesCounters()
{
    for (std::map<cMessage*, uint32_t>::iterator it = this->takenMessages.begin(); it != this->takenMessages.end(); it++)
    {
        it->second++;
    }
}

void CorruptIEEE8021QbvQueueingReordering::injectReadyMessages(uint32_t minPassedFrames)
{
    for (std::map<cMessage*, uint32_t>::iterator it = this->takenMessages.begin(); it != this->takenMessages.end();)
    {
        if (it->second >= minPassedFrames)
        {
            this->outMessages.push_back(it->first);
            this->takenMessages.erase(it++);
        }
        else
        {
            ++it;
        }
    }
    if (this->injectTakenFramesWithRandomOrder)
    {
        // Fisher–Yates shuffle:
        for (int i = this->outMessages.size()-1; i > 0; i--)
        {
            int j = this->getRNG(0)->intRand(i+1);
            cMessage* msg = this->outMessages[i];
            this->outMessages[i] = this->outMessages[j];
            this->outMessages[j] = msg;
        }
    }
    while(!this->outMessages.empty())
    {
        CorruptIEEE8021QbvQueueingBase::handleMessage(this->outMessages.front());
        this->outMessages.erase(this->outMessages.begin());
    }
}

} //namespace
