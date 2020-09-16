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

#include "Injection.h"

namespace CoRE4INET {

Define_Module(Injection);

Injection::Injection()
{
    this->savedMessages = std::deque<cMessage*>();
}

Injection::~Injection()
{
    while(!this->savedMessages.empty())
    {
        delete this->savedMessages.front();
        savedMessages.pop_front();
    }
}

void Injection::initialize(int stage)
{
    IEEE8021QbvSelection::initialize(stage);
    if (stage == 0)
    {
        this->numberOfSavedMessages = 10;
        cMessage* msg = new cMessage("Trigger injection");
        this->selfMessageId = msg->getId();
        scheduleAt(simTime() + 0.001, msg);
    }
}

void Injection::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg->getId() == this->selfMessageId)
    {
        if (!this->savedMessages.empty())
        {
            cMessage* injectMsg = this->savedMessages[rand() % this->savedMessages.size()]->dup();
            injectMsg->setName((std::string(injectMsg->getName()) + "(Injected)").c_str());
            messages.push(injectMsg);
        }
        scheduleAt(simTime() + 0.001, msg);
    }
    else if (msg->arrivedOn("in"))
    {
        this->savedMessages.push_back(msg->dup());
        if(this->savedMessages.size() > this->numberOfSavedMessages)
        {
            delete this->savedMessages.front();
            savedMessages.pop_front();
        }
        IEEE8021QbvSelection::handleMessage(msg);
    }
    else
    {
        IEEE8021QbvSelection::handleMessage(msg);
    }
}

void Injection::selectFrame()
{
    if (this->framesRequested > 0 && this->messages.size() > 0)
    {
        this->framesRequested--;
        cMessage* msg = messages.front();
        messages.pop();
        this->send(msg, "out");
    }
    else
    {
        IEEE8021QbvSelection::selectFrame();
    }
}

} //namespace
