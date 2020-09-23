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

#include <core4inet/applications/trafficsource/pcapng/PCAPNGTrafficSourceApp.h>

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/buffer/base/BGBuffer.h"
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"

namespace CoRE4INET {

Define_Module(PCAPNGTrafficSourceApp);


PCAPNGTrafficSourceApp::PCAPNGTrafficSourceApp() {
    this->enabled = false;
    this->startTime = 0;
    this->pcapngFilename = "";
    this->pcapngReader = PCAPNGReader();
    this->filterDestAddress = inet::MACAddress();
    this->filterSrcAddress = inet::MACAddress();
    this->pcp = -1;

}

PCAPNGTrafficSourceApp::~PCAPNGTrafficSourceApp() {
}

void PCAPNGTrafficSourceApp::initialize()
{
    ApplicationBase::initialize();
    handleParameterChange(nullptr);
    pcapngReader.initialize(pcapngFilename.c_str());
    if (enabled)
    {
        cMessage* startMessage = new cMessage(START_MSG_NAME);
        startMessage->setKind(0);
        scheduleAt(simTime() + par("startTime").doubleValue(), startMessage);
        if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/asleep");
        }
    }
    else
    {
        if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/stop");
        }
    }
}


void PCAPNGTrafficSourceApp::handleParameterChange(const char* parname)
{
    ApplicationBase::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "enabled"))
    {
        this->enabled = par("enabled").boolValue();
    }
    if (!parname || !strcmp(parname, "startTime"))
    {
        this->startTime = SimTime(parameterDoubleCheckRange(par("startTime"), 0, SIMTIME_MAX.dbl()));
    }
    if (!parname || !strcmp(parname, "pcapngFilename"))
    {
        this->pcapngFilename = par("pcapngFilename").stringValue();
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
    if (!parname || !strcmp(parname, "filterDestAddress"))
    {
        if (par("filterDestAddress").stdstringValue() == "auto")
        {
            // assign automatic address
            this->filterDestAddress = inet::MACAddress::generateAutoAddress();
            // change module parameter from "auto" to concrete address
            par("filterDestAddress").setStringValue(this->filterDestAddress.str());
        }
        else
        {
            this->filterDestAddress.setAddress(par("filterDestAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "filterSrcAddress"))
    {
        if (par("filterSrcAddress").stdstringValue() == "auto")
        {
            // assign automatic address
            this->filterSrcAddress = inet::MACAddress::generateAutoAddress();
            // change module parameter from "auto" to concrete address
            par("filterSrcAddress").setStringValue(this->filterSrcAddress.str());
        }
        else
        {
            this->filterSrcAddress.setAddress(par("filterSrcAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "pcp"))
    {
        if (par("pcp").intValue() == -1) {
            this->pcp = -1;
        } else {
            this->pcp = static_cast<int8_t>(parameterLongCheckRange(par("pcp"), 0, MAX_Q_PRIORITY));
        }
    }
}

void PCAPNGTrafficSourceApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (getEnvir()->isGUI())
        {
            getDisplayString().removeTag("i2");
        }

        if (msg->getKind() == 0) { // StartMessage
            msg->setKind(1);
        }
        sendMessage();
        scheduleNextMessage(msg);

    }
    else
    {
        delete msg;
    }
}

void PCAPNGTrafficSourceApp::sendMessage()
{
    for (std::list<BGBuffer*>::const_iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); ++buf)
    {
        inet::EthernetIIFrame *nextEtherFrame = pcapngReader.getNextEthernetIIFrame();
        if (nextEtherFrame == nullptr) {
            return;
        }

        if (pcp == -1) {
            nextEtherFrame->setDest(this->destAddress);
            // TODO statistiken
            //emit(this->..., nextEtherFrame);
            sendDirect(nextEtherFrame, (*buf)->gate("in"));
        } else {
            cPacket *payloadPacket = nextEtherFrame->decapsulate();
            EthernetIIFrameWithQTag *qFrame = new EthernetIIFrameWithQTag("IEEE 802.1Q Traffic");
            qFrame->setDest(this->destAddress);
            qFrame->setPcp(this->pcp);
            //qFrame->setVID(this->vid);
            qFrame->setSchedulingPriority(static_cast<short>(SCHEDULING_PRIORITY_OFFSET_8021Q - pcp));
            qFrame->encapsulate(payloadPacket);
            //Padding
            if (qFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
            {
                qFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
            }
            // TODO statistiken
            //emit(this->..., qFrame);
            sendDirect(qFrame, (*buf)->gate("in"));
            delete(nextEtherFrame);
        }
    }
}

void PCAPNGTrafficSourceApp::scheduleNextMessage(cMessage *msg)
{
    if (!pcapngReader.endOfFileReached()) {
        scheduleAt(pcapngReader.getNextSimTime() + startTime, msg); //TODO: Use scheduler of the node to support its modeled inaccuracy
    }
}

} // CoRE4INET
