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

#include "core4inet/applications/trafficsink/avb/AVBTrafficSinkApp.h"

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/base/NotifierConsts.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
#include "core4inet/utilities/ConfigFunctions.h"

//INET Auto-Generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

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

    srpTable = check_and_cast<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
    if (!srpTable)
    {
        throw cRuntimeError("Parent module does not contain a srpTable module");
    }
    srpTable->subscribe(NF_AVB_TALKER_REGISTERED, this);
    srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);

    if (isStatic)
    {
        retryInterval = 0;
    }

    if (getEnvir()->isGUI())
    {
        getDisplayString().setTagArg("i2", 0, "status/hourglass");
    }
}

void AVBTrafficSinkApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj,
        __attribute__((unused)) cObject *details)
{
    Enter_Method_Silent
    ();

    if (id == NF_AVB_TALKER_REGISTERED)
    {
        SRPTable::TalkerEntry *tentry = check_and_cast<SRPTable::TalkerEntry*>(obj);

        //If talker for the desired stream, register Listener
        if (tentry->streamId == static_cast<uint64_t>(par("streamID"))
                && tentry->vlan_id == static_cast<uint16_t>(par("vlan_id")))
        {
            SRPTable *signal_srpTable = check_and_cast<SRPTable *>(src);

            signal_srpTable->updateListenerWithStreamId(tentry->streamId, this, tentry->vlan_id, isStatic);
            if (getEnvir()->isGUI())
            {
                getDisplayString().setTagArg("i2", 0, "status/hourglass");
            }
            if (updateInterval != 0)
            {
                scheduleAt(simTime() + updateInterval, new cMessage("updateSubscription"));
            }
        }
    }
    else if (id == NF_AVB_LISTENER_REGISTRATION_TIMEOUT)
    {
        SRPTable::ListenerEntry *lentry = check_and_cast<SRPTable::ListenerEntry*>(obj);
        if (lentry->streamId == static_cast<uint64_t>(par("streamID"))
                && lentry->vlan_id == static_cast<uint16_t>(par("vlan_id")))
        {
            if (lentry->module == this)
            {
                if (getEnvir()->isGUI())
                {
                    getDisplayString().setTagArg("i2", 0, "status/hourglass");
                }
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
        srpTable->updateListenerWithStreamId(static_cast<uint64_t>(par("streamID")), this, par("vlan_id"), isStatic);
        if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/active");
        }
        if (updateInterval > 0)
        {
            scheduleAt(simTime() + updateInterval, msg);
        }
    }
    else
    {
        //Received an EtherFrame so the source seems to be active
        if (getEnvir()->isGUI() && dynamic_cast<inet::EtherFrame*>(msg))
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
#if LONG_BIT == 32
        this->streamID = parameterULongCheckRange(par("streamID"), 0, static_cast<unsigned long>(MAX_STREAM_ID));
#else
        this->streamID = parameterULongCheckRange(par("streamID"), 0, MAX_STREAM_ID);
#endif
    }
    if (!parname || !strcmp(parname, "vlan_id"))
    {
        this->vlan_id = static_cast<unsigned short>(parameterULongCheckRange(par("vlan_id"), 0, MAX_VLAN_ID));
    }
    if (!parname || !strcmp(parname, "isStatic"))
    {
        this->isStatic = par("isStatic").boolValue();
    }
}

} //namespace
