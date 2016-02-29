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

#include "core4inet/applications/trafficsink/base/TrafficSinkApp.h"

//INET Auto-Generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

Define_Module(TrafficSinkApp);

simsignal_t TrafficSinkApp::rxPkSignal = registerSignal("rxPk");

void TrafficSinkApp::handleMessage(cMessage *msg)
{
    ApplicationBase::handleMessage(msg);

    if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg))
    {
        emit(rxPkSignal, frame);
    }
    delete msg;
}

} //namespace
