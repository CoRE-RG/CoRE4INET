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

#include "core4inet/applications/trafficsource/IEEE8021Q/IEEE8021QBurstTrafficSourceApp.h"

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/buffer/base/BGBuffer.h"
#include "core4inet/utilities/ConfigFunctions.h"
//Auto-generated messages
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"

namespace CoRE4INET {

Define_Module(IEEE8021QBurstTrafficSourceApp);

IEEE8021QBurstTrafficSourceApp::IEEE8021QBurstTrafficSourceApp()
{
    this->priority = 0;
    this->vid = 0;
}

void IEEE8021QBurstTrafficSourceApp::sendMessage()
{

    for (std::list<BGBuffer*>::const_iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); ++buf)
    {
        unsigned long size_left = this->getBurstSize();
        while (size_left > 0)
        {
            EthernetIIFrameWithQTag *frame = new EthernetIIFrameWithQTag("IEEE 802.1Q Burst Traffic");

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
            frame->encapsulate(payload_packet);
            frame->setPcp(priority);
            frame->setVID(this->vid);
            frame->setSchedulingPriority(static_cast<short>(SCHEDULING_PRIORITY_OFFSET_8021Q - priority));
            //Padding
            if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
            {
                frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
            }
            sendDirect(frame, (*buf)->gate("in"));
        }
    }
}

void IEEE8021QBurstTrafficSourceApp::handleParameterChange(const char* parname)
{
    BGBurstTrafficSourceApp::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "priority"))
    {
        this->priority = static_cast<uint8_t>(parameterLongCheckRange(par("priority"), 0, 7));
    }
    if (!parname || !strcmp(parname, "vid"))
    {
        this->vid = static_cast<uint16_t>(parameterLongCheckRange(par("vid"), 0, MAX_VLAN_ID));
    }
}

} /* namespace CoRE4INET */
