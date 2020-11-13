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

#include "Reordering.h"

namespace CoRE4INET {

Define_Module(Reordering);

Reordering::Reordering()
{
    this->outMessages = std::queue<cMessage*>();
    this->savedMessages = std::deque<cMessage*>();
}

Reordering::~Reordering()
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

void Reordering::initialize(int stage)
{
    IEEE8021QbvSelection::initialize(stage);
}

void Reordering::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (this->reorder())
        {
            this->bubble("Reorder");
            this->getParentModule()->bubble("Reorder");
            this->savedMessages.push_back(msg);
            this->framesRequested++;
            this->selectFrame();
        }
        else
        {
            IEEE8021QbvSelection::handleMessage(msg);
            if (!this->savedMessages.empty())
            {
                cMessage* reorderedMsg = this->savedMessages.front();
                this->savedMessages.pop_front();
                reorderedMsg->setName((std::string(reorderedMsg->getName()) + " (Reordered)").c_str());
                this->outMessages.push(reorderedMsg);
            }
        }
    }
    else
    {
        IEEE8021QbvSelection::handleMessage(msg);
    }
}

void Reordering::selectFrame()
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

bool Reordering::reorder()
{
    uint32_t value = rand() % 100 + 1;
    return value > 90;
}

} //namespace
