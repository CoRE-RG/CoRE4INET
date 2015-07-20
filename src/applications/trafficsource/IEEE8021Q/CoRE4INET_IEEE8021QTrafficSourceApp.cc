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

#include "CoRE4INET_IEEE8021QTrafficSourceApp.h"

//CoRE4INET
#include "CoRE4INET_Defs.h"
#include "CoRE4INET_BGBuffer.h"
#include "CoRE4INET_ConfigFunctions.h"
#include "EtherFrameWithQTag_m.h"

namespace CoRE4INET {

Define_Module(IEEE8021QTrafficSourceApp);

IEEE8021QTrafficSourceApp::IEEE8021QTrafficSourceApp()
{
    this->sendInterval = 0;
    this->priority = 0;
}

void IEEE8021QTrafficSourceApp::handleMessage(cMessage *msg)
{

    if (msg->isSelfMessage())
    {
        if (ev.isGUI())
        {
            getDisplayString().removeTag("i2");
        }
        sendMessage();
        scheduleAt(simTime() + this->sendInterval, msg);
    }
    else
    {
        delete msg;
    }
}

void IEEE8021QTrafficSourceApp::sendMessage()
{
    for (std::list<BGBuffer*>::const_iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); ++buf)
    {
        EthernetIIFrameWithQTag *frame = new EthernetIIFrameWithQTag("IEEE 802.1Q Traffic");

        frame->setDest(this->destAddress);

        cPacket *payload_packet = new cPacket();
        payload_packet->setByteLength(static_cast<int64_t>(getPayloadBytes()));
        frame->encapsulate(payload_packet);
        frame->setPcp(priority);
        frame->setSchedulingPriority(static_cast<short>(SCHEDULING_PRIORITY_OFFSET_8021Q-priority));
        //Padding
        if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
        {
            frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
        }
        sendDirect(frame, (*buf)->gate("in"));
    }

}

void IEEE8021QTrafficSourceApp::handleParameterChange(const char* parname)
{
    TrafficSourceAppBase::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "sendInterval"))
    {
        this->sendInterval = parameterDoubleCheckRange(par("sendInterval"), 0, MAXTIME.dbl(), true);
    }
    if (!parname || !strcmp(parname, "destAddress"))
    {
        if (par("destAddress").stdstringValue() == "auto")
        {
            // assign automatic address
            this->destAddress = inet::MACAddress::generateAutoAddress();

            // change module parameter from "auto" to concrete address
            par("destAddress").setStringValue(this->destAddress.str());
        }
        else
        {
            this->destAddress.setAddress(par("destAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "priority"))
    {
        this->priority = static_cast<uint8_t>(parameterLongCheckRange(par("priority"), 0, 7));
    }
}

}
//namespace
