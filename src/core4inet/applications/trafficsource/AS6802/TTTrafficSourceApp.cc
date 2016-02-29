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

#include "core4inet/applications/trafficsource/AS6802/TTTrafficSourceApp.h"

//CoRE4INET
#include "core4inet/base/NotifierConsts.h"
#include "core4inet/utilities/ConfigFunctions.h"
//INET
#include "inet/common/ModuleAccess.h"
//Auto-generated Messages
#include "core4inet/synchronisation/base/SyncNotification_m.h"

namespace CoRE4INET {

Define_Module(TTTrafficSourceApp);

TTTrafficSourceApp::TTTrafficSourceApp() :
        moduloCycle(0)
{
    this->synchronized = false;
    this->modulo = 1;
    this->moduloCycle = 0;
}

void TTTrafficSourceApp::initialize()
{
    CTTrafficSourceAppBase::initialize();

    handleParameterChange(nullptr);
    synchronized = false;

    inet::findContainingNode(this)->subscribe(NF_SYNC_STATE_CHANGE, this);
}

void TTTrafficSourceApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0))
    {
        if (isEnabled())
        {
            SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event",
                    ACTION_TIME_EVENT);
            event->setAction_time(
                    static_cast<uint32_t>(par("action_time").doubleValue() / getOscillator()->getPreciseTick()));
            event->setDestinationGate(gate("schedulerIn"));

            if (event->getAction_time() >= getPeriod()->getCycleTicks())
            {
                throw cRuntimeError("The action_time (%d ticks) starts outside of the period (%d ticks)",
                        event->getAction_time(), getPeriod()->getCycleTicks());
            }

            getPeriod()->registerEvent(event);
        }
        delete msg;
    }
    else if (msg && msg->arrivedOn("schedulerIn"))
    {
        if (getEnvir()->isGUI())
        {
            getDisplayString().removeTag("i2");
        }
        moduloCycle++;
        if (synchronized && moduloCycle == this->modulo)
        {
            sendMessage();
            moduloCycle = 0;
        }

        SchedulerActionTimeEvent *event = check_and_cast<SchedulerActionTimeEvent *>(msg);
        event->setNext_cycle(true);
        getPeriod()->registerEvent(event);
    }
    else
    {
        delete msg;
    }
}

void TTTrafficSourceApp::receiveSignal(__attribute__((unused)) cComponent *src, __attribute__((unused)) simsignal_t id,
        cObject *obj, __attribute__((unused)) cObject *details)
{
    Enter_Method_Silent
    ();
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

void TTTrafficSourceApp::handleParameterChange(const char* parname)
{
    CTTrafficSourceAppBase::handleParameterChange(parname);
    Scheduled::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "modulo"))
    {
        this->modulo = static_cast<unsigned int>(parameterULongCheckRange(par("modulo"), 0, ULONG_MAX));
    }
}

}
//namespace
