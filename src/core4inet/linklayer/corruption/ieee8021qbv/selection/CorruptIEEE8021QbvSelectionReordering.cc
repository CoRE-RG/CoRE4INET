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

#include <core4inet/linklayer/corruption/ieee8021qbv/selection/CorruptIEEE8021QbvSelectionReordering.h>
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/utilities/customWatch.h"

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvSelectionReordering);

CorruptIEEE8021QbvSelectionReordering::CorruptIEEE8021QbvSelectionReordering()
{
    this->takenMessages = std::map<cMessage*, uint32_t>();
}

CorruptIEEE8021QbvSelectionReordering::~CorruptIEEE8021QbvSelectionReordering()
{
    for (std::map<cMessage*, uint32_t>::iterator it = this->takenMessages.begin(); it != this->takenMessages.end();) // TODO: Random?
    {
        delete it->first;
        this->takenMessages.erase(it++);
    }
}

void CorruptIEEE8021QbvSelectionReordering::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvSelectionBase::handleParameterChange(parname);
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

void CorruptIEEE8021QbvSelectionReordering::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
    if (stage == 0)
    {
        WATCH_KEYPTRMAP(this->takenMessages);
    }
}

void CorruptIEEE8021QbvSelectionReordering::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Reorder");
            this->getParentModule()->bubble("Reorder");
            msg->setName((std::string(msg->getName()) + " (Reordered)").c_str());
            this->takenMessages[msg] = 0;
            this->framesRequested++;
            this->selectFrame();
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
            CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
            this->injectReadyMessages(this->getNumberOfFramesBeforeInjection());
        }
    }
    else
    {
        CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
    }
}

uint32_t CorruptIEEE8021QbvSelectionReordering::getNumberOfFramesBeforeInjection()
{
    this->handleParameterChange("numberOfFramesBeforeInjection");
    return this->numberOfFramesBeforeInjection;
}

void CorruptIEEE8021QbvSelectionReordering::incrementPassedFramesCounters()
{
    for (std::map<cMessage*, uint32_t>::iterator it = this->takenMessages.begin(); it != this->takenMessages.end(); it++)
    {
        it->second++;
    }
}

void CorruptIEEE8021QbvSelectionReordering::injectReadyMessages(uint32_t minPassedFrames)
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
}

} //namespace
