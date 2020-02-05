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

#include "core4inet/applications/trafficsink/base/BGTrafficSinkApp.h"

//CoRE4INET
#include "core4inet/buffer/base/BGBuffer.h"

namespace CoRE4INET {

Define_Module(BGTrafficSinkApp);

BGTrafficSinkApp::BGTrafficSinkApp(){
    received = 0;
}

void BGTrafficSinkApp::initialize()
{
    TrafficSinkApp::initialize();

    handleParameterChange(nullptr);
}

void BGTrafficSinkApp::handleParameterChange(const char* parname)
{
    TrafficSinkApp::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "srcAddress"))
    {
        if (par("srcAddress").stdstringValue() == "auto")
        {
            // change module parameter from "auto" to concrete address
            par("srcAddress").setStringValue(inet::MACAddress::UNSPECIFIED_ADDRESS.str());
        }
        address = inet::MACAddress(par("srcAddress").stringValue());
    }
}

void BGTrafficSinkApp::handleMessage(cMessage *msg)
{
    if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg))
    {
        if (address.isUnspecified() || frame->getSrc() == address)
        {
            if((!received && par("replyFirst").boolValue()) || par("reply").boolValue()){
                inet::EtherFrame *reply = new inet::EthernetIIFrame("Reply",7);
                reply->setDest(frame->getSrc());
                cPacket* payload = new cPacket("Reply");
                //Payloadsize:
                if(frame->hasEncapsulatedPacket()){
                    payload->setByteLength(frame->getEncapsulatedPacket()->getByteLength());
                }
                else{
                    payload->setByteLength(frame->getByteLength()-ETHER_MAC_FRAME_BYTES);
                }
                reply->encapsulate(payload);
                for (std::list<BGBuffer*>::const_iterator buf = bgbuffers.begin();
                            buf != bgbuffers.end(); ++buf) {
                    sendDirect(reply->dup(), (*buf)->gate("in"));
                }
                delete reply;
            }
            received++;
            TrafficSinkApp::handleMessage(msg);
        }
        else
        {
            delete msg;
        }
    }
    else
    {
        delete msg;
    }
}

} //namespace
