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

//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(IEEE8021QSyncTrafficSourceApp);

void IEEE8021QSyncTrafficSourceApp::handleParameterChange(const char* parname)
{
    Scheduled::handleParameterChange(parname);
    IEEE8021QTrafficSourceApp::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "actionTime"))
    {
        this->actionTime = parameterDoubleCheckRange(par("actionTime"), 0, SIMTIME_MAX.dbl(), false, true);
    }
}

void IEEE8021QSyncTrafficSourceApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0))
    {
        if (isEnabled())
        {
            SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event",
                    ACTION_TIME_EVENT);
            event->setAction_time(
                    static_cast<uint32_t>(this->actionTime / getOscillator()->getPreciseTick()));
            event->setDestinationGate(gate("schedulerIn"));
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
        if (getEnvir()->isGUI())
        {
            getDisplayString().removeTag("i2");
        }
        IEEE8021QTrafficSourceApp::sendMessage();
        SchedulerActionTimeEvent *event = check_and_cast<SchedulerActionTimeEvent *>(msg);
        event->setNext_cycle(true);
        getPeriod()->registerEvent(event);
    }
    else
    {
        delete msg;
    }
}

} //namespace
