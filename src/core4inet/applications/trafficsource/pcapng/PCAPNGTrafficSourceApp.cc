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

namespace CoRE4INET {

Define_Module(PCAPNGTrafficSourceApp);


PCAPNGTrafficSourceApp::PCAPNGTrafficSourceApp() {
    this->enabled = false;
    this->startTime = 0;
    this->pcapngFilename = "";
    this->pcapngReader = PCAPNGReader();
    this->overrideDestAddress = inet::MACAddress();
    this->overrideSrcAddress = inet::MACAddress();

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
        this->destAddress.setAddress(par("destAddress").stringValue());
    }
    if (!parname || !strcmp(parname, "overrideDestAddress"))
    {
        this->overrideDestAddress.setAddress(par("overrideDestAddress").stringValue());
    }
    if (!parname || !strcmp(parname, "overrideSrcAddress"))
    {
        this->overrideSrcAddress.setAddress(par("overrideSrcAddress").stringValue());
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
    inet::EthernetIIFrame *nextEtherFrame = pcapngReader.getNextEthernetIIFrame();
    if (nextEtherFrame == nullptr) {
        return;
    }

    nextEtherFrame->setDest(this->destAddress);
    //nextEtherFrame->setSrc(this->srcAddress);
    for (std::list<BGBuffer*>::const_iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); ++buf)
    {
        // TODO statistiken
        //emit(this->..., nextEtherFrame);
        sendDirect(nextEtherFrame, (*buf)->gate("in"));
    }
}

void PCAPNGTrafficSourceApp::scheduleNextMessage(cMessage *msg)
{
    simtime_t nextSendTime = pcapngReader.getNextSimTime();
    simtime_t currentTime = simTime();
    if (!pcapngReader.endOfFileReached()) {
        scheduleAt(nextSendTime + startTime, msg); //TODO: Use scheduler of the node to support its modeled inaccuracy
    }
}

} // CoRE4INET
