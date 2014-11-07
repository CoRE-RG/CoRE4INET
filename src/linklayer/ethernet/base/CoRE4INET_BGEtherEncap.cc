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

//==============================================================================

#include "CoRE4INET_BGEtherEncap.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

Define_Module(BGEtherEncap);

//==============================================================================

BGEtherEncap::BGEtherEncap() {

}

//==============================================================================

BGEtherEncap::~BGEtherEncap() {
}

//==============================================================================

void BGEtherEncap::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("bgIn"))
    {
        send(msg, gate("lowerLayerOut"));
    }
    else if (msg->arrivedOn("lowerLayerIn"))
    {
        if (gate("bgOut")->isConnected() && gate("bgOut")->isPathOK()) {
            send(msg->dup(), gate("bgOut"));
        }
        if (gate("upperLayerOut")->isConnected() && gate("upperLayerOut")->isPathOK()) {
            EtherEncap::handleMessage(msg->dup());
        }
        delete msg;
    }
    else
    {
        EtherEncap::handleMessage(msg);
    }
}

//==============================================================================

} /* namespace CoRE4INET */
