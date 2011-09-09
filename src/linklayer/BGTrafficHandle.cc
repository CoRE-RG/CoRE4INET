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

#include "BGTrafficHandle.h"
#include "Ieee802Ctrl_m.h"

#define ETHERAPP_BUFFER_SAP  0xe0

namespace TTEthernetModel {

Define_Module(BGTrafficHandle);

void BGTrafficHandle::initialize()
{
    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
    etherctrl->setDsap(ETHERAPP_BUFFER_SAP);
    cMessage *msg = new cMessage("register_DSAP", IEEE802CTRL_REGISTER_DSAP);
    msg->setControlInfo(etherctrl);

    send(msg, "lowerLayerOut");
}

void BGTrafficHandle::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("lowerLayerIn")){
        send(msg, "out");
    }
    else if(msg->arrivedOn("in")){
        Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
        etherctrl->setSsap(ETHERAPP_BUFFER_SAP);
        etherctrl->setDsap(ETHERAPP_BUFFER_SAP);
        msg->setControlInfo(etherctrl);
        send(msg, "lowerLayerOut");
    }
}

} //namespace
