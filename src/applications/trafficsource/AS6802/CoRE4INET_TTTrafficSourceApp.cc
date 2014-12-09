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
}

void TTTrafficSourceApp::initialize()
{
    CTTrafficSourceAppBase::initialize();

    if (par("enabled").boolValue())
    {
        Scheduled::initialize();

        SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
        event->setAction_time(
                (uint32_t) (par("action_time").doubleValue()
                        / findModuleWhereverInNode("oscillator", getParentModule())->par("tick").doubleValue()));
        event->setDestinationGate(gate("schedulerIn"));

        if (event->getAction_time() >= (uint32_t) period->par("cycle_ticks").longValue())
        {
            throw cRuntimeError("The action_time (%d ticks) starts outside of the period (%d ticks)", event->getAction_time(),
                    period->par("cycle_ticks").longValue());
        }

        period->registerEvent(event);
    }
    synchronized = false;
    ASSERT2(findContainingNode(this)!=NULL,
            "TrafficSource is not inside a Node (Node must be marked by @node property in ned module)");
    findContainingNode(this)->subscribe(NF_SYNC_STATE_CHANGE, this);
}

void TTTrafficSourceApp::handleMessage(cMessage *msg)
{

    if (msg->arrivedOn("schedulerIn"))
    {
        moduloCycle++;
        if (synchronized && moduloCycle == (unsigned int) par("modulo").longValue())
        {
            sendMessage();
            moduloCycle = 0;
        }

        SchedulerActionTimeEvent *event = check_and_cast<SchedulerActionTimeEvent *>(msg);
        event->setNext_cycle(true);
        period->registerEvent(event);
    }
    else
    {
        delete msg;
    }
}

void TTTrafficSourceApp::receiveSignal(__attribute__((unused)) cComponent *src, __attribute__((unused)) simsignal_t id, cObject *obj)
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

} //namespace
