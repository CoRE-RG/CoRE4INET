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

#include "CoRE4INET_TTTrafficSourceApp.h"

//CoRE4INET
#include "CoRE4INET_NotifierConsts.h"
#include "CoRE4INET_ConfigFunctions.h"
//INET
#include "ModuleAccess.h"
//Auto-generated Messages
#include "SyncNotification_m.h"

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

    handleParameterChange(NULL);
    if (isEnabled())
    {
        Scheduled::initialize();

        SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);

        if (findContainingNode(this) == NULL)
        {
            throw cRuntimeError(
                    "TrafficSource is not inside a Node (Node must be marked by @node property in ned module)");
        }

        Oscillator* oscillator = dynamic_cast<Oscillator*>(findModuleWhereverInNode("oscillator", getParentModule()));
        if (!oscillator)
        {
            throw cRuntimeError(
                    "Cannot find oscillator module in Node. Oscillator is required to calculate action time");
        }

        event->setAction_time((uint32_t) (par("action_time").doubleValue() / oscillator->par("tick").doubleValue()));
        event->setDestinationGate(gate("schedulerIn"));

        if (event->getAction_time() >= getPeriod()->getCycleTicks())
        {
            throw cRuntimeError("The action_time (%d ticks) starts outside of the period (%d ticks)",
                    event->getAction_time(), getPeriod()->getCycleTicks());
        }

        getPeriod()->registerEvent(event);
    }
    synchronized = false;

    findContainingNode(this)->subscribe(NF_SYNC_STATE_CHANGE, this);
}

void TTTrafficSourceApp::handleMessage(cMessage *msg)
{

    if (msg && msg->arrivedOn("schedulerIn"))
    {
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

void TTTrafficSourceApp::receiveSignal(__attribute__((unused))      cComponent *src, __attribute__((unused))      simsignal_t id,
        cObject *obj)
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

    if (!parname || !strcmp(parname, "modulo"))
    {
        this->modulo = (unsigned int) parameterULongCheckRange(par("modulo"), 0, ULONG_MAX);
    }
}

}
//namespace
