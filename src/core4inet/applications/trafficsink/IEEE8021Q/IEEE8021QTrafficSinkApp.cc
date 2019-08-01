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

#include "IEEE8021QTrafficSinkApp.h"

#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"


namespace CoRE4INET {

Define_Module(IEEE8021QTrafficSinkApp);

simsignal_t IEEE8021QTrafficSinkApp::rxPkQ0Signal = registerSignal("rxPkQ0");
simsignal_t IEEE8021QTrafficSinkApp::rxPkQ1Signal = registerSignal("rxPkQ1");
simsignal_t IEEE8021QTrafficSinkApp::rxPkQ2Signal = registerSignal("rxPkQ2");
simsignal_t IEEE8021QTrafficSinkApp::rxPkQ3Signal = registerSignal("rxPkQ3");
simsignal_t IEEE8021QTrafficSinkApp::rxPkQ4Signal = registerSignal("rxPkQ4");
simsignal_t IEEE8021QTrafficSinkApp::rxPkQ5Signal = registerSignal("rxPkQ5");
simsignal_t IEEE8021QTrafficSinkApp::rxPkQ6Signal = registerSignal("rxPkQ6");
simsignal_t IEEE8021QTrafficSinkApp::rxPkQ7Signal = registerSignal("rxPkQ7");

void IEEE8021QTrafficSinkApp::handleMessage(cMessage *msg)
{
    if (EthernetIIFrameWithQTag *qframe = dynamic_cast<EthernetIIFrameWithQTag*>(msg)){
        if (address.isUnspecified() || qframe->getSrc() == address){
            int pcp = qframe->getPcp();
            switch(pcp){
            case 0:
                emit(rxPkQ0Signal, qframe);
            break;
            case 1:
                emit(rxPkQ1Signal, qframe);
            break;
            case 2:
                emit(rxPkQ2Signal, qframe);
                break;
            case 3:
                emit(rxPkQ3Signal, qframe);
                break;
            case 4:
                emit(rxPkQ4Signal, qframe);
                break;
            case 5:
                emit(rxPkQ5Signal, qframe);
                break;
            case 6:
                emit(rxPkQ6Signal, qframe);
                break;
            case 7:
                emit(rxPkQ7Signal, qframe);
                break;
            }
        }
    }
    BGTrafficSinkApp::handleMessage(msg);
}

} //namespace
