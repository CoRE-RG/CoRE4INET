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

#include "CoRE4INET_BGTrafficSinkApp.h"

//CoRE4INET
#include "CoRE4INET_BGBuffer.h"

namespace CoRE4INET {

Define_Module(BGTrafficSinkApp);

BGTrafficSinkApp::BGTrafficSinkApp(){
    received = 0;
}

void BGTrafficSinkApp::initialize()
{
    TrafficSinkApp::initialize();

    if (par("srcAddress").stdstringValue() == "auto")
    {
        // change module parameter from "auto" to concrete address
        par("srcAddress").setStringValue(MACAddress::UNSPECIFIED_ADDRESS.str());
    }
    address = MACAddress(par("srcAddress").stringValue());
}

void BGTrafficSinkApp::handleMessage(cMessage *msg)
{
    if (EtherFrame *frame = dynamic_cast<EtherFrame*>(msg))
    {
        if (address.isUnspecified() || frame->getSrc() == address)
        {
            if((!received && par("replyFirst").boolValue()) || par("reply").boolValue()){
                EtherFrame *reply = new EthernetIIFrame("Reply");
                reply->setDest(frame->getSrc());
                reply->setByteLength(frame->getByteLength());
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
