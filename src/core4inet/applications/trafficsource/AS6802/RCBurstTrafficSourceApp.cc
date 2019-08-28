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

#include "core4inet/applications/trafficsource/AS6802/RCBurstTrafficSourceApp.h"

//CoRE4INET
#include "core4inet/scheduler/timer/Timer.h"
#include "core4inet/utilities/ConfigFunctions.h"
//INET
#include "inet/common/ModuleAccess.h"

namespace CoRE4INET {

Define_Module(RCBurstTrafficSourceApp);

RCBurstTrafficSourceApp::RCBurstTrafficSourceApp()
{
    this->interval = 0;
    this->burstInterval = 0;
    framesBurstedCnt = 0;
}

void RCBurstTrafficSourceApp::initialize()
{
    CTTrafficSourceAppBase::initialize();

    handleParameterChange(nullptr);
}

void RCBurstTrafficSourceApp::handleMessage(cMessage *msg)
{

    CTTrafficSourceAppBase::handleMessage(msg);
    if (msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0))
    {
        if (isEnabled())
        {
            SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);

            event->setTimer(static_cast<uint64_t>(this->interval / getOscillator()->getPreciseTick()));
            event->setDestinationGate(gate("schedulerIn"));
            getTimer()->registerEvent(event);
        }
        delete msg;
    }
    else if (msg->arrivedOn("schedulerIn"))
    {
        if (framesBurstedCnt < static_cast<unsigned int>(par("nrOfFramesInOneBurst")))
        {
            getDisplayString().removeTag("i2");
            sendMessage();
            framesBurstedCnt++;

            if (SchedulerTimerEvent *event = dynamic_cast<SchedulerTimerEvent *>(msg))
            {
                event->setTimer(static_cast<uint64_t>(this->interval / getOscillator()->getPreciseTick()));
                getTimer()->registerEvent(event);
            }
            else
            {
                throw cRuntimeError("Message on schedulerIn is of wrong type");
            }
        }
        else
        {
            if (SchedulerTimerEvent *event = dynamic_cast<SchedulerTimerEvent *>(msg))
            {
                event->setTimer(static_cast<uint64_t>(this->burstInterval / getOscillator()->getPreciseTick()));
                getTimer()->registerEvent(event);
                framesBurstedCnt = 0;
            }
            else
            {
                throw cRuntimeError("Message on schedulerIn is of wrong type");
            }
        }
    }
    else
    {
        delete msg;
    }
}

void RCBurstTrafficSourceApp::handleParameterChange(const char* parname)
{
    CTTrafficSourceAppBase::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "interval"))
    {
        this->interval = parameterDoubleCheckRange(par("interval"), 0, SIMTIME_MAX.dbl(), true);
    }
    if (!parname || !strcmp(parname, "burstInterval"))
    {
        this->burstInterval = parameterDoubleCheckRange(par("burstInterval"), 0, SIMTIME_MAX.dbl(), true);
    }
}

}
 //namespace

