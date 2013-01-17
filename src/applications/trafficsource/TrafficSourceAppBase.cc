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

#include "TrafficSourceAppBase.h"
#include "CTFrame.h"
#include "TTFrame_m.h"
#include "RCFrame_m.h"
#include "TTE4INETDefs.h"

namespace TTEthernetModel {

Define_Module( TrafficSourceAppBase);

void TrafficSourceAppBase::initialize()
{
    scheduleAt(simTime(), new cMessage("ACTIVATOR!"));
}

void TrafficSourceAppBase::sendMessage(){
    int ctID = par("ct_id").longValue();
    if(ctID == -1){

    }
    else{
        std::list<Buffer*> buffer = buffers[ctID];
        if(buffer.size()==0){
            ev.printf("No buffer with such CT \n");
            bubble("No buffer with such CT");
            getDisplayString().setTagArg("i2", 0, "status/excl3");
            getDisplayString().setTagArg("tt", 0, "WARNING: No buffer with such CT");
            getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
            getParentModule()->getDisplayString().setTagArg("tt", 0, "No buffer with such CT");
        }
        else{
            for(std::list<Buffer*>::iterator buf = buffer.begin();
                       buf!=buffer.end();buf++){
                CTFrame *frame;
                if(dynamic_cast<TTBuffer*>(*buf)){
                    frame = new TTFrame("");
                }
                else if(dynamic_cast<RCBuffer*>(*buf)){
                    frame = new RCFrame("");
                }
                else{
                    continue;
                }
                frame->setByteLength(par("payload").longValue()+ETHER_MAC_FRAME_BYTES);
                //Padding
                if(frame->getByteLength()<MIN_ETHERNET_FRAME_BYTES){
                    frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
                }
                frame->setCtID(ctID);
                //TODO Error check
                Incoming* in = (Incoming *)(*buf)->gate("in")->getPathStartGate()->getOwner();
                //TODO Better name for Frame
                frame->setName((*buf)->getName());
                sendDirect(frame, in->gate("in"));
            }
        }
    }
}


} //namespace
