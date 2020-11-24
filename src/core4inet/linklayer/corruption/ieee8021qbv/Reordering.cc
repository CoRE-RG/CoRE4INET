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

void Reordering::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
}

void Reordering::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (this->performCorruption())
        {
            this->bubble("Reorder");
            this->getParentModule()->bubble("Reorder");
            this->savedMessages.push_back(msg);
            this->framesRequested++;
            this->selectFrame();
        }
        else
        {
            CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
            while (!this->savedMessages.empty())
            {
                cMessage* reorderedMsg = this->savedMessages.front();
                this->savedMessages.pop_front();
                reorderedMsg->setName((std::string(reorderedMsg->getName()) + " (Reordered)").c_str());
                this->outMessages.push_back(reorderedMsg);
            }
        }
    }
    else
    {
        CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
    }
}

} //namespace
