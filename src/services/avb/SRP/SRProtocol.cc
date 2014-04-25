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

#include "AVBDefs.h"

#include "ExtendedIeee802Ctrl_m.h"
#include "EtherLLC.h"

#define ETHERAPP_BUFFER_SAP  0xe1

namespace CoRE4INET {

Define_Module(SRProtocol);

void SRProtocol::initialize()
{
    localSAP = ETHERAPP_BUFFER_SAP;
    remoteSAP = ETHERAPP_BUFFER_SAP;

    srpTable = (SRPTable *) getParentModule()->getSubmodule("srpTable");
    if (!srpTable)
    {
        throw cRuntimeError("srpTable module required for stream reservation");
    }
    srpTable->subscribe("talkerRegistered", this);
    srpTable->subscribe("listenerRegistered", this);
}

void SRProtocol::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (TalkerAdvertise* talkerAdvertise = dynamic_cast<TalkerAdvertise*>(msg))
        {
            Ieee802Ctrl *etherctrl = dynamic_cast<Ieee802Ctrl *>(msg->removeControlInfo());
            if (!etherctrl)
            {
                error("packet `%s' from lower layer received without Ieee802Ctrl", msg->getName());
            }
            int arrivedOn = etherctrl->getSwitchPort();
            //TODO Major: Work around, this can be removed when we have an Extended LLC!
            if (arrivedOn < 0)
            {
                arrivedOn = 0;
            }
            cModule *port = getParentModule()->getSubmodule("phy", arrivedOn);
            //TODO Minor: try to get VLAN
            srpTable->updateTalkerWithStreamId(talkerAdvertise->getStreamID(), port, &etherctrl->getSrc(), SR_CLASS_A,
                    talkerAdvertise->getMaxFrameSize(), talkerAdvertise->getMaxIntervalFrames(), 0);
            delete etherctrl;
        }
        else if (ListenerReady* listenerReady = dynamic_cast<ListenerReady*>(msg))
        {
            Ieee802Ctrl *etherctrl = dynamic_cast<Ieee802Ctrl *>(msg->removeControlInfo());
            if (!etherctrl)
                error("packet `%s' from lower layer received without Ieee802Ctrl", msg->getName());
            //TODO Minor: try to get VLAN
            //srpTable->updateTalkerWithStreamId(talkerAdvertise->getStreamID(), this, &etherctrl->getSrc(),
            //        SR_CLASS_A, talkerAdvertise->getMaxFrameSize(), talkerAdvertise->getMaxIntervalFrames(), 0);
            //TODO: Update Table if enough bandwidth
            delete etherctrl;
        }
    }
    delete msg;
}

void SRProtocol::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent
    ();
    if (id == registerSignal("talkerRegistered"))
    {
        SRPTable::TalkerEntry *tentry = (SRPTable::TalkerEntry*) obj;

        TalkerAdvertise *talkerAdvertise = new TalkerAdvertise("Talker Advertise", IEEE802CTRL_DATA);
        talkerAdvertise->setStreamID(tentry->streamId);
        talkerAdvertise->setMaxFrameSize(tentry->framesize);
        talkerAdvertise->setMaxIntervalFrames(tentry->intervalFrames);

        ExtendedIeee802Ctrl *etherctrl = new ExtendedIeee802Ctrl();
        etherctrl->setSsap(localSAP);
        etherctrl->setDsap(remoteSAP);
        etherctrl->setEtherType(MSRP_ETHERTYPE);
        etherctrl->setDest(SRP_ADDRESS);
        talkerAdvertise->setControlInfo(etherctrl);

        etherctrl->setSwitchPort(SWITCH_PORT_BROADCAST);
        //If talker was received from phy we have to exclude the incoming
        if (strcmp(tentry->module->getName(), "phy") == 0)
        {
            etherctrl->setNotSwitchPort(tentry->module->getIndex());
        }

        send(talkerAdvertise, gate("out"));
    }
    else if (id == registerSignal("listenerRegistered"))
    {
        SRPTable::ListenerEntry *lentry = (SRPTable::ListenerEntry*) obj;

        SRPFrame *listenerReady = new ListenerReady("Listener Ready", IEEE802CTRL_DATA);
        listenerReady->setStreamID(lentry->streamId);

        ExtendedIeee802Ctrl *etherctrl = new ExtendedIeee802Ctrl();
        etherctrl->setSsap(localSAP);
        etherctrl->setDsap(remoteSAP);
        etherctrl->setEtherType(MSRP_ETHERTYPE);
        etherctrl->setDest(SRP_ADDRESS);
        listenerReady->setControlInfo(etherctrl);

        //Get Talker Port
        SRPTable *srpTable = (SRPTable *) src;
        srpTable->

        etherctrl->setSwitchPort(SWITCH_PORT_BROADCAST);
    }
}

} /* namespace CoRE4INET */
