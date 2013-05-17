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

#include "TrafficSinkApp.h"

#include "CTFrame.h"

namespace TTEthernetModel {

Define_Module(TrafficSinkApp);

simsignal_t TrafficSinkApp::rxPkSignal = SIMSIGNAL_NULL;
simsignal_t TrafficSinkApp::latencySignal = SIMSIGNAL_NULL;

void TrafficSinkApp::initialize(){
    rxPkSignal = registerSignal("rxPk");
    latencySignal = registerSignal("latency");
}

void TrafficSinkApp::handleMessage(cMessage *msg)
{
    TTEApplicationBase::handleMessage(msg);

    if(msg->arrivedOn("RCin") || msg->arrivedOn("TTin"))
    {
        CTFrame *ctframe = dynamic_cast<CTFrame*>(msg);
        if(ctframe){
            emit(rxPkSignal, 1L);
            //Get most inner encapsulated packet for end-to-end latency
            cPacket *innerPacket = ctframe;
            cPacket *tmpPacket;
            while((tmpPacket = innerPacket->decapsulate()) != NULL){
                //delete the packet that contained the encapsulated
                delete innerPacket;
                innerPacket = tmpPacket;
            }
            emit(latencySignal, simTime()-innerPacket->getCreationTime());
            delete innerPacket;
        }
        else{
            delete msg;
        }
    }
    else
    {
        delete msg;
    }
}

} //namespace
