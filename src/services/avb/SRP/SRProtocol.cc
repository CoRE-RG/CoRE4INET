//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "SRProtocol.h"

#include "SRPFrame_m.h"

#include "Ieee802Ctrl_m.h"

#define ETHERAPP_BUFFER_SAP  0xe1

namespace CoRE4INET {

Define_Module(SRProtocol);

void SRProtocol::initialize()
{
    localSAP = ETHERAPP_BUFFER_SAP;
    remoteSAP = ETHERAPP_BUFFER_SAP;

    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
    etherctrl->setDsap(localSAP);
    cMessage *msg = new cMessage("register_DSAP", IEEE802CTRL_REGISTER_DSAP);
    msg->setControlInfo(etherctrl);
    send(msg, "out");

    srpTable = (SRPTable *) getParentModule()->getSubmodule("srpTable");
    if (!srpTable)
    {
        throw cRuntimeError("srpTable module required for stream reservation");
    }
    srpTable->subscribe("talkerRegistered", this);
}

void SRProtocol::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (TalkerAdvertise* talkerAdvertise = dynamic_cast<TalkerAdvertise*>(msg))
        {
            Ieee802Ctrl *etherctrl = dynamic_cast<Ieee802Ctrl *>(msg->removeControlInfo());
                if (!etherctrl)
                    error("packet `%s' from lower layer received without Ieee802Ctrl", msg->getName());
            //TODO Minor: try to get VLAN
            srpTable->updateTalkerWithStreamId(talkerAdvertise->getStreamID(), this, &etherctrl->getSrc(),
                    SR_CLASS_A, talkerAdvertise->getMaxFrameSize(), talkerAdvertise->getMaxIntervalFrames(), 0);
        }
    }
}

void SRProtocol::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent
    ();
    if (id == registerSignal("talkerRegistered"))
    {
        SRPTable::TalkerEntry *tentry = (SRPTable::TalkerEntry*) obj;

        //Only send Talker Advertise for Streams that are from this node
        if(tentry->address->isUnspecified()){

            TalkerAdvertise *talkerAdvertise = new TalkerAdvertise("Talker Advertise", IEEE802CTRL_DATA);
            talkerAdvertise->setStreamID(tentry->streamId);
            talkerAdvertise->setMaxFrameSize(tentry->framesize);
            talkerAdvertise->setMaxIntervalFrames(tentry->intervalFrames);

            Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
            etherctrl->setSsap(localSAP);
            etherctrl->setDsap(remoteSAP);
            //etherctrl->setDest(destMACAddress);
            talkerAdvertise->setControlInfo(etherctrl);

            send(talkerAdvertise, gate("out"));
        }
    }
}

} /* namespace CoRE4INET */
