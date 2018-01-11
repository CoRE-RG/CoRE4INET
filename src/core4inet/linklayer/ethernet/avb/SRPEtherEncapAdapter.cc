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

#include "SRPEtherEncapAdapter.h"

namespace CoRE4INET {

Define_Module(SRPEtherEncapAdapter);


void SRPEtherEncapAdapter::initialize()
{
    portCount = static_cast<size_t>(gate("encapOut", 0)->size());
    WATCH(portCount);
}

void SRPEtherEncapAdapter::handleMessage(cMessage *msg) {
    if (msg && msg->arrivedOn("srpIn")) {
        SRPFrame * srpFrame = check_and_cast<SRPFrame*>(msg);
        ExtendedIeee802Ctrl * controlInfo = dynamic_cast<ExtendedIeee802Ctrl *>(srpFrame->removeControlInfo());
        if (ListenerReady* listenerReady = dynamic_cast<ListenerReady*>(srpFrame)) {
            listenerReady->setControlInfo(controlInfo->dup());
            send(listenerReady, "encapOut", controlInfo->getSwitchPort());
        } else if (TalkerAdvertise* talkerAdvertise = dynamic_cast<TalkerAdvertise*>(srpFrame)) {
            if(controlInfo->getNotSwitchPort() == -1) {
                for (size_t i = 0; i < portCount; i++) {
                    TalkerAdvertise* newtalkerAdvertise = talkerAdvertise->dup();
                    newtalkerAdvertise->setControlInfo(controlInfo->dup());
                    send(newtalkerAdvertise, "encapOut", static_cast<int>(i));
                }
            }
            delete talkerAdvertise;
        } else {
            for (size_t i = 0; i < portCount; ++i) {
                SRPFrame* newSrpFrame = srpFrame->dup();
                newSrpFrame->setControlInfo(controlInfo->dup());
                send(newSrpFrame, "encapOut", static_cast<int>(i));
            }
            delete srpFrame;
        }

        delete controlInfo;
    } else if (msg && msg->arrivedOn("encapIn")) {
        SRPFrame * srpFrame = check_and_cast<SRPFrame*>(msg);
        inet::Ieee802Ctrl * controlInfo = dynamic_cast<inet::Ieee802Ctrl *>(srpFrame->removeControlInfo());
        controlInfo->setSwitchPort(srpFrame->getArrivalGate()->getIndex());
        srpFrame->setControlInfo(controlInfo);
        send(srpFrame, "srpOut");
    } else {
        delete msg;
    }
}

} //namespace
