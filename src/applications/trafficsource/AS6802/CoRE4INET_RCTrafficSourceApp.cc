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

#include "CoRE4INET_RCTrafficSourceApp.h"

//CoRE4INET
#include "CoRE4INET_Timer.h"
#include "CoRE4INET_ConfigFunctions.h"
//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

Define_Module(RCTrafficSourceApp);

RCTrafficSourceApp::RCTrafficSourceApp()
{
    this->interval = 0;
}

void RCTrafficSourceApp::initialize()
{
    CTTrafficSourceAppBase::initialize();

    handleParameterChange(nullptr);
    if (isEnabled())
    {
        SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);

        event->setTimer(static_cast<uint64_t>(this->interval / getOscillator()->getPreciseTick()));
        event->setDestinationGate(gate("schedulerIn"));
        getTimer()->registerEvent(event);
    }
}

void RCTrafficSourceApp::handleMessage(cMessage *msg)
{

    CTTrafficSourceAppBase::handleMessage(msg);
    if (msg->arrivedOn("schedulerIn"))
    {
        sendMessage();

        if (SchedulerTimerEvent *event = dynamic_cast<SchedulerTimerEvent *>(msg))
        {
            event->setTimer(static_cast<uint64_t>(this->interval / getOscillator()->getPreciseTick()));
            getTimer()->registerEvent(event);
        }
        else{
            throw cRuntimeError("Message on schedulerIn is of wrong type");
        }
    }
    else
    {
        delete msg;
    }
}

void RCTrafficSourceApp::handleParameterChange(const char* parname)
{
    CTTrafficSourceAppBase::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "interval"))
    {
        this->interval = parameterDoubleCheckRange(par("interval"), 0, MAXTIME.dbl(), true);
    }
}

}
 //namespace
