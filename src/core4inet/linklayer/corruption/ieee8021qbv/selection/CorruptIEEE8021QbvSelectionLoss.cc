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

#include <core4inet/linklayer/corruption/ieee8021qbv/selection/CorruptIEEE8021QbvSelectionLoss.h>

namespace CoRE4INET {

Define_Module(CorruptIEEE8021QbvSelectionLoss);

void CorruptIEEE8021QbvSelectionLoss::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
}

void CorruptIEEE8021QbvSelectionLoss::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (this->match(msg) && this->performCorruption())
        {
            this->bubble("Loss");
            this->getParentModule()->bubble("Loss");
            delete msg;
            this->framesRequested++;
            this->selectFrame();
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

} //namespace
