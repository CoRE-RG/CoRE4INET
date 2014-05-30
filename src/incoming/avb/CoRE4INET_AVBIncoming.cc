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

#include "CoRE4INET_AVBIncoming.h"

//CoRE4INET
#include "CoRE4INET_SRPTable.h"
//INET
#include "EtherFrame_m.h"

namespace CoRE4INET {

Define_Module(AVBIncoming);

AVBIncoming::AVBIncoming() {
    hadError = false;
}

void AVBIncoming::handleMessage(cMessage* msg) {
    if (msg->arrivedOn("in")) {
        EtherFrame *inFrame = check_and_cast<EtherFrame*>(msg);

        SRPTable *srptable = check_and_cast<SRPTable*>(
                getParentModule()->getSubmodule("srpTable"));
        //TODO: Minor enable VLANs
        std::list<cModule*> listeners = srptable->getListenersForTalkerAddress(
                inFrame->getDest(), 0);
        if (listeners.size() == 0) {
            emit(droppedSignal, inFrame);
        } else {
            for (std::list<cModule*>::const_iterator listener = listeners.begin();
                    listener != listeners.end(); listener++) {
                if (strcmp((*listener)->getName(), "phy") == 0) {
                    sendDelayed(inFrame->dup(),
                            SimTime(
                                    getParentModule()->par("hardware_delay").doubleValue()),
                            gate("AVBout", (*listener)->getIndex()));
                    emit(rxPkSignal, inFrame);
                } else {
                    if ((*listener)->hasGate("AVBin")) {
                        sendDirect(inFrame->dup(), (*listener)->gate("AVBin"));
                        emit(rxPkSignal, inFrame);
                    }
                }
            }
        }
        delete inFrame;
    } else {
        delete msg;
    }
}

} /* namespace CoRE4INET */
