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

void Injection::initialize()
{
    this->numberOfSavedMessages = 10;
    scheduleAt(simTime() + 0.001, new cMessage("Trigger injection"));
}

void Injection::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (!this->savedMessages.empty())
        {
            this->bubble("Injection");
            cMessage* injectMsg = this->savedMessages[rand() % this->savedMessages.size()]->dup();
            this->send(injectMsg, "out");
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
}

} //namespace
