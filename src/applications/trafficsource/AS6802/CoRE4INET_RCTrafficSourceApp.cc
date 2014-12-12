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
    this->tick = 0;
    this->interval = 0;
}

void RCTrafficSourceApp::initialize()
{
    CTTrafficSourceAppBase::initialize();

    handleParameterChange(NULL);
    if (isEnabled())
    {
        SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);

        Timer *timer = dynamic_cast<Timer*>(findModuleWhereverInNode("timer", getParentModule()));
        if (!timer)
        {
            throw cRuntimeError("Cannot find timer module. Timer is required to run RCTrafficSourceApp");
        }

        Oscillator* oscillator = dynamic_cast<Oscillator*>(findModuleWhereverInNode("oscillator", getParentModule()));
        if (!oscillator)
        {
            throw cRuntimeError(
                    "Cannot find oscillator module in Node. Oscillator is required to calculate action time");
        }

        tick = oscillator->par("tick").doubleValue();
        event->setTimer((uint64_t) (par("interval").doubleValue() / tick));
        event->setDestinationGate(gate("schedulerIn"));
        timer->registerEvent(event);
    }
}

void RCTrafficSourceApp::handleMessage(cMessage *msg)
{

    CTTrafficSourceAppBase::handleMessage(msg);
    if (msg->arrivedOn("schedulerIn"))
    {
        sendMessage();

        Timer *timer = dynamic_cast<Timer*>(msg->getSenderModule());
        if(!timer){
            throw cRuntimeError("Message arrived at schedulerIn, but is no message from a timer module");
        }
        else{
            SchedulerTimerEvent *event = (SchedulerTimerEvent *) msg;
            event->setTimer((uint64_t) (this->interval / tick));
            timer->registerEvent(event);
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

    if (!parname || !strcmp(parname, "interval"))
    {
        this->interval = parameterDoubleCheckRange(par("interval"), 0, MAXTIME.dbl(), true);
    }
}

} //namespace
