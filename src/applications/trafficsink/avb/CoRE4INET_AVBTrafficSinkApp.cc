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

#include "CoRE4INET_AVBTrafficSinkApp.h"

//CoRE4INET
#include "CoRE4INET_SRPTable.h"
//INET Auto-Generated Messages
#include "EtherFrame_m.h"

namespace CoRE4INET {

Define_Module(AVBTrafficSinkApp);

void AVBTrafficSinkApp::initialize()
{
    TrafficSinkApp::initialize();
    SRPTable *srpTable = check_and_cast_nullable<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
    if (srpTable)
    {
        srpTable->subscribe("talkerRegistered", this);
        srpTable->subscribe("listenerRegistrationTimeout", this);
    }
    getDisplayString().setTagArg("i2", 0, "status/hourglass");
}

void AVBTrafficSinkApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent
    ();
    if (id == registerSignal("talkerRegistered"))
    {
        SRPTable::TalkerEntry *tentry = check_and_cast<SRPTable::TalkerEntry*>(obj);

        //If talker for the desired stream, register Listener
        if (tentry->streamId == (unsigned int) par("streamID").longValue())
        {
            SRPTable *srpTable = check_and_cast<SRPTable *>(src);

            //TODO Minor: try to get VLAN
            srpTable->updateListenerWithStreamId(tentry->streamId, this, 0);
            getDisplayString().setTagArg("i2", 0, "status/hourglass");
            simtime_t updateInterval = par("updateInterval").doubleValue();
            if (updateInterval != 0)
            {
                scheduleAt(simTime() + updateInterval, new cMessage("updateSubscription"));
            }
        }
    }
    else if (id == registerSignal("listenerRegistrationTimeout"))
    {
        SRPTable::ListenerEntry *lentry = check_and_cast<SRPTable::ListenerEntry*>(obj);
        if (lentry->streamId == (unsigned int) par("streamID").longValue())
        {
            if (lentry->module == this)
            {
                getDisplayString().setTagArg("i2", 0, "status/hourglass");
                simtime_t retryInterval = par("retryInterval").doubleValue();
                if (retryInterval != 0)
                {
                    scheduleAt(simTime() + retryInterval, new cMessage("retrySubscription"));
                }
            }
        }
    }
}

void AVBTrafficSinkApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        SRPTable *srpTable = check_and_cast_nullable<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
        srpTable->updateListenerWithStreamId((unsigned int) par("streamID").longValue(), this, 0);
        getDisplayString().setTagArg("i2", 0, "status/active");
        simtime_t updateInterval = par("updateInterval").doubleValue();
        if (updateInterval != 0)
        {
            scheduleAt(simTime() + updateInterval, msg);
        }
    }
    else
    {
        if (dynamic_cast<EtherFrame*>(msg))
        {
            getDisplayString().setTagArg("i2", 0, "status/active");
        }
        TrafficSinkApp::handleMessage(msg);
    }
}

} //namespace
