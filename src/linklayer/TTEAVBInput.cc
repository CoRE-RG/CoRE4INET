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

#include "TTEAVBInput.h"
#include "TTEScheduler.h"
#include "Buffer.h"

#include <iostream>

namespace TTEthernetModel {

Define_Module(TTEAVBInput);

TTEAVBInput::TTEAVBInput() : TTEInput::TTEInput()
{

}

void TTEAVBInput::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        EtherFrame *frame = (EtherFrame*) msg;

        int i = msg->findPar("received");
        cMsgPar* par;
        if( i >=0 )
            par = &msg->par(i);
        else
            par = &msg->addPar("received");
        par->setLongValue(((TTEScheduler*)getParentModule()->getParentModule()->getSubmodule("tteScheduler"))->getTicks());

        i = msg->findPar("received_total");
        if( i >=0 )
            par = &msg->par(i);
        else
            par = &msg->addPar("received_total");
        par->setLongValue(((TTEScheduler*)getParentModule()->getParentModule()->getSubmodule("tteScheduler"))->getTotalTicks());


        i = msg->findPar("received_port");
        if( i >=0 )
            par = &msg->par(i);
        else
            par = &msg->addPar("received_port");
        par->setLongValue(getParentModule()->getIndex());

        //Auf CTCs verteilen oder BE traffic
        if (isCT(frame))
        {
            std::map<uint16, std::list<Incoming *> >::iterator incomingList = incomings.find(getCTID(frame));
            if (incomingList != incomings.end())
            {
                //Send to all CTCs for the CT-ID
                for (std::list<Incoming*>::iterator incoming = incomingList->second.begin(); incoming
                        != incomingList->second.end(); incoming++)
                {
                    sendDirect(frame->dup(), (*incoming)->gate("in"));
                }
                delete frame;
            }
            else
            {
                emit(ctDroppedSignal, 1);
                hadError=true;
                if(ev.isGUI()){
                    bubble("No matching buffer configured");
                    getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                    getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                }
                delete frame;
            }
        }
        //Sonst BE
        else
        {
            if(promiscuous || frame->getDest().isMulticast())
            {
                send(msg, "out");
            }
            else
            {
                MACAddress address;
                address.setAddress(frame->getArrivalGate()->getPathStartGate()->getOwnerModule()->par("address"));
                if(frame->getDest().equals(address))
                {
                    send(msg, "out");
                }
                else
                {
                    delete msg;
                }
            }
        }
    }
}

} /* namespace TTEthernetModel */
