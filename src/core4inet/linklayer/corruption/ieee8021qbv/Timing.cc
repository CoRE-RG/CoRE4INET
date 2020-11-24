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

void Timing::handleParameterChange(const char* parname)
{
    CorruptIEEE8021QbvSelectionBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "delayTime"))
    {
        this->delayTime = parameterDoubleCheckRange(par("delayTime"), 0, SIMTIME_MAX.dbl());
    }
}

void Timing::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
    if (stage == 0)
    {
        this->handleParameterChange(nullptr);
    }
}

void Timing::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg->getId() == this->selfMessageId)
    {
        if (!this->savedMessages.empty())
        {
            cMessage* delayedMsg = this->savedMessages.front();
            this->savedMessages.pop_front();
            delayedMsg->setName((std::string(delayedMsg->getName()) + " (Delayed)").c_str());
            //this->outMessages.push(delayedMsg);
            this->send(delayedMsg, "out");
        }
        delete msg;
    }
    else if (msg->arrivedOn("in"))
    {
        if (this->performCorruption())
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

} //namespace
