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

#include "AVBTrafficSinkApp.h"

#include "SRPTable.h"

namespace CoRE4INET {

Define_Module(AVBTrafficSinkApp);

void AVBTrafficSinkApp::initialize()
{
    TrafficSinkApp::initialize();
    SRPTable *srpTable = (SRPTable *) getParentModule()->getSubmodule("srpTable");
    if (srpTable)
    {
        srpTable->subscribe("talkerRegistered", this);
    }
}

void AVBTrafficSinkApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent
    ();
    if (id == registerSignal("talkerRegistered"))
    {
        SRPTable::TalkerEntry *tentry = (SRPTable::TalkerEntry*) obj;

        //If talker for the desired stream, register Listener
        if (tentry->streamId == (unsigned int)par("streamID").longValue())
        {
            SRPTable *srpTable = (SRPTable *) src;

            //TODO Minor: try to get VLAN
            srpTable->updateListenerWithStreamId(tentry->streamId, this, 0);
        }
    }
}

} //namespace
