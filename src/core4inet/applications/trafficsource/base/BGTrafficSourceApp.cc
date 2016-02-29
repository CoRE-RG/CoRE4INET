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

#include "core4inet/applications/trafficsource/base/BGTrafficSourceApp.h"

//CoRE4INET
#include "core4inet/buffer/base/BGBuffer.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(BGTrafficSourceApp);

simsignal_t BGTrafficSourceApp::sigSendInterval = registerSignal("intervalSignal");


BGTrafficSourceApp::BGTrafficSourceApp()
{
    this->sendInterval = 0;
    this->parametersInitialized = false;
}

void BGTrafficSourceApp::initialize()
{
    TrafficSourceAppBase::initialize();
}

void BGTrafficSourceApp::handleMessage(cMessage *msg)
{

    if (msg->isSelfMessage())
    {
        if (getEnvir()->isGUI())
        {
            getDisplayString().removeTag("i2");
        }
        sendMessage();
        scheduleAt(simTime() + this->sendInterval, msg);
        emit(sigSendInterval,this->sendInterval);
        handleParameterChange("sendInterval");
    }
    else
    {
        delete msg;
    }
}

void BGTrafficSourceApp::sendMessage()
{
    for (std::list<BGBuffer*>::const_iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); ++buf)
    {
        inet::EthernetIIFrame *frame = new inet::EthernetIIFrame("Best-Effort Traffic", 7); //kind 7 = black

        frame->setDest(this->destAddress);

        cPacket *payload_packet = new cPacket();
        payload_packet->setByteLength(static_cast<int64_t>(getPayloadBytes()));
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

void BGTrafficSourceApp::handleParameterChange(const char* parname)
{
    TrafficSourceAppBase::handleParameterChange(parname);

    if (!parname && !parametersInitialized)
    {
        parametersInitialized = true;
    }

    if (!parname || !strcmp(parname, "sendInterval"))
    {
        this->sendInterval = parameterDoubleCheckRange(par("sendInterval"), 0, SIMTIME_MAX.dbl(), true);
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
}

inet::MACAddress BGTrafficSourceApp::getDestAddress()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->destAddress;
}

}
//namespace
