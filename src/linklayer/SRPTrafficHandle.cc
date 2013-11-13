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

#define ETHERAPP_CLI_SAP  0xf0
#define ETHERAPP_SRV_SAP  0xf1
#define ETHERAPP_BUFFER_SAP  0xe0

namespace CoRE4INET {

Define_Module(SRPTrafficHandle);

void SRPTrafficHandle::initialize()
{
    localSAP = ETHERAPP_BUFFER_SAP;
    remoteSAP = ETHERAPP_BUFFER_SAP;
    destMACAddressUnicast.setAddress("000000000000");
    destMACAddressBroadcast.setAddress("FFFFFFFFFFFF");
    srcMACAddress.setAddress("000000000000");

    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
    etherctrl->setDsap(localSAP);
    cMessage *msg = new cMessage("register_DSAP", IEEE802CTRL_REGISTER_DSAP);
    msg->setControlInfo(etherctrl);
    send(msg, "lowerLayerOut");
}

void SRPTrafficHandle::handleMessage(cMessage *msg)
{
    std::string msgClass = msg->getClassName();
    //TODO fix that
    if(msgClass.compare("CoRE4INET::SRPFrame") == 0)
    {
        SRPFrame *inFrame = (SRPFrame*) msg;
        if(msg->arrivedOn("SRPin"))
        {
            std::string srpType = inFrame->getName();
            if(srpType.compare("Talker Advertise") == 0)
            {
                Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
                etherctrl->setSsap(localSAP);
                etherctrl->setDsap(remoteSAP);
                etherctrl->setDest(destMACAddressBroadcast);
                inFrame->setControlInfo(etherctrl);
                send(inFrame, "lowerLayerOut");
            }

            if(srpType.compare("Listener Ready") == 0 ||
               srpType.compare("Listener Ready Failed") == 0 ||
               srpType.compare("Listener Failed") == 0)
            {
                Ieee802Ctrl *etherctrl;
                if(inFrame->getControlInfo() == NULL)
                {
                    etherctrl = new Ieee802Ctrl();
                }
                else
                {
                    etherctrl = (Ieee802Ctrl*)inFrame->getControlInfo();
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
            if(inFrame->getControlInfo() != NULL)
            {
                Ieee802Ctrl *etherctrl = (Ieee802Ctrl*)inFrame->getControlInfo();
                inFrame->setSrc(etherctrl->getSrc());
            }
            send(inFrame,"SRPout");
        }
    }
    else
    {
        if(msg->arrivedOn("SRPin"))
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
