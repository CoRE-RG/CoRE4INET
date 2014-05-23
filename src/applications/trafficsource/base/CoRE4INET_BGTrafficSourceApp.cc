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

#include "CoRE4INET_BGTrafficSourceApp.h"
#include "CoRE4INET_Defs.h"
#include "CoRE4INET_BGBuffer.h"

namespace CoRE4INET {

Define_Module(BGTrafficSourceApp);

void BGTrafficSourceApp::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage()) {
        sendMessage();
        scheduleAt(simTime() + par("sendInterval").doubleValue(), msg);
    } else {
        delete msg;
    }
}

void BGTrafficSourceApp::sendMessage() {
    for (std::list<BGBuffer*>::iterator buf = bgbuffers.begin();
            buf != bgbuffers.end(); buf++) {
        EthernetIIFrame *frame = new EthernetIIFrame("Best-Effort Traffic");

        MACAddress address;
        if (par("destAddress").stdstringValue() == "auto") {
            // assign automatic address
            address = MACAddress::generateAutoAddress();

            // change module parameter from "auto" to concrete address
            par("destAddress").setStringValue(address.str());
        } else {
            address.setAddress(par("destAddress").stringValue());
        }

        frame->setDest(address);

        cPacket *payload = new cPacket;
        payload->setByteLength(par("payload").longValue());
        frame->setByteLength(ETHER_MAC_FRAME_BYTES);
        frame->encapsulate(payload);
        //Padding
        if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
            frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
        }
        sendDirect(frame, (*buf)->gate("in"));
    }

}

} //namespace
