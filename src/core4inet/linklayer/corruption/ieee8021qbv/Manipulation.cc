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

#include "Manipulation.h"

//INET
#include "inet/linklayer/common/MACAddress.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

Define_Module(Manipulation);

void Manipulation::initialize(int stage)
{
    CorruptIEEE8021QbvSelectionBase::initialize(stage);
}

void Manipulation::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in"))
    {
        if (this->performCorruption())
        {
            if(inet::EthernetIIFrame* frame = dynamic_cast<inet::EthernetIIFrame*>(msg))
            {
                frame->setSrc(inet::MACAddress("FF-FF-FF-FF-FF-FF"));
                frame->setName((std::string(frame->getName()) + " (Manipulated)").c_str());
            }
        }
    }
    CorruptIEEE8021QbvSelectionBase::handleMessage(msg);
}

} //namespace
