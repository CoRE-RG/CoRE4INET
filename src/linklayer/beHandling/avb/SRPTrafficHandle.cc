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

#include "SRPTrafficHandle.h"
#include "Ieee802Ctrl_m.h"
#include "SRPFrame_m.h"

#include "SRPTable.h"

#define ETHERAPP_BUFFER_SAP  0xe0

namespace CoRE4INET {

Define_Module(SRPTrafficHandle);

void SRPTrafficHandle::initialize()
{
    localSAP = ETHERAPP_BUFFER_SAP;
    remoteSAP = ETHERAPP_BUFFER_SAP;

    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
    etherctrl->setDsap(localSAP);
    cMessage *msg = new cMessage("register_DSAP", IEEE802CTRL_REGISTER_DSAP);
    msg->setControlInfo(etherctrl);
    send(msg, "lowerLayerOut");
}

void SRPTrafficHandle::handleMessage(cMessage *msg)
{
    if (SRPFrame *inFrame = dynamic_cast<SRPFrame*>(msg))
    {
        if (msg->arrivedOn("SRPin"))
        {
            if (dynamic_cast<TalkerAdvertise*>(inFrame))
            {
                Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
                etherctrl->setSsap(localSAP);
                etherctrl->setDsap(remoteSAP);
                etherctrl->setDest(MACAddress::BROADCAST_ADDRESS);
                inFrame->setControlInfo(etherctrl);
                send(inFrame, "lowerLayerOut");
            }

            if (dynamic_cast<ListenerReady*>(inFrame) || dynamic_cast<ListenerReadyFailed*>(inFrame))
            {
                Ieee802Ctrl *etherctrl;
                if (inFrame->getControlInfo() == NULL)
                {
                    etherctrl = new Ieee802Ctrl();
                }
                else
                {
                    etherctrl = (Ieee802Ctrl*) inFrame->getControlInfo();
                    etherctrl->setDest(inFrame->getDest());
                }
                inFrame->removeControlInfo();
                etherctrl->setSsap(localSAP);
                etherctrl->setDsap(remoteSAP);
                inFrame->setControlInfo(etherctrl);

                send(inFrame, "lowerLayerOut");
            }
        }
        else
        {
            if (inFrame->getControlInfo() != NULL)
            {
                Ieee802Ctrl *etherctrl = (Ieee802Ctrl*) inFrame->getControlInfo();
                inFrame->setSrc(etherctrl->getSrc());
            }
            send(inFrame, "SRPout");
        }
    }
    else
    {
        if (msg->arrivedOn("SRPin"))
        {
            Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
            etherctrl->setSsap(localSAP);
            etherctrl->setDsap(remoteSAP);
            msg->setControlInfo(etherctrl);
            send(msg, "lowerLayerOut");
        }
        else
        {
            BGTrafficHandle::handleMessage(msg);
        }
    }
}

} /* namespace CoRE4INET */
