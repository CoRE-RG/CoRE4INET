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
#include "CoRE4INET_Defs.h"
#include "CoRE4INET_NotifierConsts.h"
#include "CoRE4INET_SRPTable.h"
#include "CoRE4INET_ConfigFunctions.h"

//INET Auto-Generated Messages
#include "EtherFrame_m.h"

namespace CoRE4INET {

Define_Module(AVBTrafficSinkApp);

AVBTrafficSinkApp::AVBTrafficSinkApp()
{
    this->srpTable = nullptr;
    this->vlan_id = 0;
    this->streamID = 0;
    updateInterval = 0;
    retryInterval = 0;
}

void AVBTrafficSinkApp::initialize()
{
    TrafficSinkApp::initialize();

    srpTable = check_and_cast_nullable<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
    if (!srpTable)
    {
        throw cRuntimeError("Parent module does not contain a srpTable module");
    }
    srpTable->subscribe(NF_AVB_TALKER_REGISTERED, this);
    srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);

    getDisplayString().setTagArg("i2", 0, "status/hourglass");
}

void AVBTrafficSinkApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent
    ();

    if (id == NF_AVB_TALKER_REGISTERED)
    {
        SRPTable::TalkerEntry *tentry = check_and_cast<SRPTable::TalkerEntry*>(obj);

        //If talker for the desired stream, register Listener
        if (tentry->streamId == static_cast<uint64_t>(par("streamID").longValue())
                && tentry->vlan_id == static_cast<uint16_t>(par("vlan_id").longValue()))
        {
            SRPTable *signal_srpTable = check_and_cast<SRPTable *>(src);

            signal_srpTable->updateListenerWithStreamId(tentry->streamId, this, tentry->vlan_id);
            getDisplayString().setTagArg("i2", 0, "status/hourglass");
            if (updateInterval != 0)
            {
                scheduleAt(simTime() + updateInterval, new cMessage("updateSubscription"));
            }
        }
    }
    else if (id == NF_AVB_LISTENER_REGISTRATION_TIMEOUT)
    {
        SRPTable::ListenerEntry *lentry = check_and_cast<SRPTable::ListenerEntry*>(obj);
        if (lentry->streamId == static_cast<uint64_t>(par("streamID").longValue())
                && lentry->vlan_id == static_cast<uint16_t>(par("vlan_id").longValue()))
        {
            if (lentry->module == this)
            {
                getDisplayString().setTagArg("i2", 0, "status/hourglass");
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
    if (msg && msg->isSelfMessage())
    {
        srpTable->updateListenerWithStreamId(static_cast<uint64_t>(par("streamID").longValue()), this,
                static_cast<uint16_t>(par("vlan_id").longValue()));
        getDisplayString().setTagArg("i2", 0, "status/active");
        if (updateInterval > 0)
        {
            scheduleAt(simTime() + updateInterval, msg);
        }
    }
    else
    {
        //Received an EtherFrame so the source seems to be active
        if (dynamic_cast<EtherFrame*>(msg))
        {
            getDisplayString().setTagArg("i2", 0, "status/active");
        }
        TrafficSinkApp::handleMessage(msg);
    }
}

void AVBTrafficSinkApp::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "updateInterval"))
    {
        this->updateInterval = parameterDoubleCheckRange(par("updateInterval"), 0, DBL_MAX);
    }
    if (!parname || !strcmp(parname, "retryInterval"))
    {
        this->retryInterval = parameterDoubleCheckRange(par("retryInterval"), 0, DBL_MAX);
    }
    if (!parname || !strcmp(parname, "streamID"))
    {
        this->streamID = parameterULongCheckRange(par("streamID"), 0, static_cast<unsigned long>(MAX_STREAM_ID));
    }
    if (!parname || !strcmp(parname, "vlan_id"))
    {
        this->vlan_id = static_cast<unsigned short>(parameterULongCheckRange(par("vlan_id"), 0, MAX_VLAN_ID));
    }
}

} //namespace
