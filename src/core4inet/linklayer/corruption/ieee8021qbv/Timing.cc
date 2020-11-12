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
    this->outMessages = std::queue<cMessage*>();
    this->savedMessages = std::deque<cMessage*>();
}

Timing::~Timing()
{
    while(!this->outMessages.empty())
    {
        delete this->outMessages.front();
        outMessages.pop();
    }
    while(!this->savedMessages.empty())
    {
        delete this->savedMessages.front();
        savedMessages.pop_front();
    }
}

void Timing::handleParameterChange(const char* parname)
{
    IEEE8021QbvSelection::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "delayTime"))
    {
        this->delayTime = parameterDoubleCheckRange(par("delayTime"), 0, SIMTIME_MAX.dbl());
    }
}

void Timing::initialize(int stage)
{
    IEEE8021QbvSelection::initialize(stage);
}

void Timing::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg->getId() == this->selfMessageId)
    {
        if (!this->savedMessages.empty())
        {
            cMessage* delayedMsg = this->savedMessages.front();
            this->savedMessages.pop_front();
            delayedMsg->setName((std::string(delayedMsg->getName()) + "(Delayed)").c_str());
            //this->outMessages.push(delayedMsg);
            this->send(delayedMsg, "out");
        }
        delete msg;
    }
    else if (msg->arrivedOn("in"))
    {
        if (this->delay())
        {
            this->bubble("Delay");
            this->getParentModule()->bubble("Delay");
            this->savedMessages.push_back(msg);
            //this->framesRequested++; All following frames have to wait?
            //this->selectFrame();
            cMessage* msg = new cMessage("Trigger delayed message");
            this->selfMessageId = msg->getId();
            scheduleAt(simTime() + this->getDelayTime(), msg);
        }
        else
        {
            IEEE8021QbvSelection::handleMessage(msg);
        }
    }
    else
    {
        IEEE8021QbvSelection::handleMessage(msg);
    }
}

void Timing::selectFrame()
{
    if (this->framesRequested > 0 && this->outMessages.size() > 0)
    {
        this->framesRequested--;
        cMessage* msg = outMessages.front();
        outMessages.pop();
        this->send(msg, "out");
    }
    else
    {
        IEEE8021QbvSelection::selectFrame();
    }
}

simtime_t Timing::getDelayTime()
{
    this->handleParameterChange("delayTime");
    return this->delayTime;
}

bool Timing::delay()
{
    uint32_t value = rand() % 100 + 1;
    return value > 90;
}

} //namespace
