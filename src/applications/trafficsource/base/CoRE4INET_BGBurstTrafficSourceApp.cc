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

#include "CoRE4INET_BGBurstTrafficSourceApp.h"

//CoRE4INET
#include "CoRE4INET_BGBuffer.h"
#include "CoRE4INET_ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(BGBurstTrafficSourceApp);

BGBurstTrafficSourceApp::BGBurstTrafficSourceApp()
{
    this->burstSize = 0;
}

void BGBurstTrafficSourceApp::sendMessage()
{

    for (std::list<BGBuffer*>::const_iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); ++buf)
    {
        unsigned long size_left = this->burstSize;
        while (size_left > 0)
        {
            inet::EthernetIIFrame *frame = new inet::EthernetIIFrame("Best-Effort Traffic", 7); //kind 7 = black

            frame->setDest(this->getDestAddress());

            cPacket *payload_packet = new cPacket();
            if (size_left >= getPayloadBytes())
            {
                payload_packet->setByteLength(static_cast<int64_t>(getPayloadBytes()));
                size_left -= getPayloadBytes();
            }
            else
            {
                payload_packet->setByteLength(static_cast<int64_t>(size_left));
                size_left = 0;
            }
            frame->setByteLength(ETHER_MAC_FRAME_BYTES);
            frame->encapsulate(payload_packet);
            //Padding
            if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
            {
                frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
            }
            sendDirect(frame, (*buf)->gate("in"));
        }
    }

}

void BGBurstTrafficSourceApp::handleParameterChange(const char* parname)
{
    BGTrafficSourceApp::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "burstSize"))
    {
        this->burstSize = parameterULongCheckRange(par("burstSize"), 1, ULONG_MAX, true);
    }
}

unsigned long BGBurstTrafficSourceApp::getBurstSize(){
    return this->burstSize;
}

}
//namespace
