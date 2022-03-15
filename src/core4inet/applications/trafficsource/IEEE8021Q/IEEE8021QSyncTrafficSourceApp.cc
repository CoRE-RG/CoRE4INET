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

#include "IEEE8021QSyncTrafficSourceApp.h"

//INET
#include "inet/common/ModuleAccess.h"
//CoRE4INET
#include "core4inet/base/NotifierConsts.h"
#include "core4inet/utilities/ConfigFunctions.h"
//Auto-generated Messages
#include "core4inet/synchronisation/base/SyncNotification_m.h"

namespace CoRE4INET {

Define_Module(IEEE8021QSyncTrafficSourceApp);

IEEE8021QSyncTrafficSourceApp::IEEE8021QSyncTrafficSourceApp()
{
    this->synchronized = false;
    this->nextCycle = 0;
}

void IEEE8021QSyncTrafficSourceApp::initialize()
{
    Scheduled::initialize();
    IEEE8021QTrafficSourceApp::initialize();
    this->handleParameterChange(nullptr);
    inet::findContainingNode(this)->subscribe(NF_SYNC_STATE_CHANGE, this);
}

void IEEE8021QSyncTrafficSourceApp::handleParameterChange(const char* parname)
{
    Scheduled::handleParameterChange(parname);
    IEEE8021QTrafficSourceApp::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "actionTime"))
    {
        this->actionTime = parameterDoubleCheckRange(par("actionTime"), 0, SIMTIME_MAX.dbl(), false, true);
    }
    if (!parname || !strcmp(parname, "modulo"))
    {
        this->modulo = static_cast<unsigned int>(parameterULongCheckRange(par("modulo"), 0, ULONG_MAX));
    }
}

void IEEE8021QSyncTrafficSourceApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0))
    {
        if (isEnabled())
        {
            SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
            event->setAction_time(static_cast<uint32_t>(ceil(this->actionTime / getOscillator()->getPreciseTick())));
            event->setDestinationGate(this->gate("schedulerIn"));
            if (event->getAction_time() >= getPeriod()->getCycleTicks())
            {
                throw cRuntimeError("The actionTime (%d ticks) starts outside of the period (%d ticks)",
                        event->getAction_time(), getPeriod()->getCycleTicks());
            }
            getPeriod()->registerEvent(event);
        }
        delete msg;
    }
    else if (msg && msg->arrivedOn("schedulerIn"))
    {
        if (this->isEnabled())
        {
            if (getEnvir()->isGUI())
            {
                getDisplayString().removeTag("i2");
            }
            uint32_t currentCycle = getPeriod()->getCycles();
            if(this->synchronized && this->nextCycle <= currentCycle) {
                IEEE8021QTrafficSourceApp::sendMessage();
                this->nextCycle = currentCycle + this->modulo;
            }
            SchedulerActionTimeEvent *event = check_and_cast<SchedulerActionTimeEvent*>(msg);
            event->setNext_cycle(true);
            getPeriod()->registerEvent(event);
        }
        else
        {
            if (getEnvir()->isGUI())
            {
                getDisplayString().setTagArg("i2", 0, "status/stop");
            }
            delete msg;
        }
    }
    else
    {
        delete msg;
    }
}

void IEEE8021QSyncTrafficSourceApp::receiveSignal(__attribute__((unused)) cComponent *src, __attribute__((unused)) simsignal_t id, cObject *obj, __attribute__((unused)) cObject *details)
{
    Enter_Method_Silent();
    if (SyncNotification *notification = dynamic_cast<SyncNotification *>(obj))
    {
        if (notification->getKind() == SYNC)
        {
            synchronized = true;
        }
        else
        {
            synchronized = false;
        }
    }
}

} //namespace
