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

#include "core4inet/applications/trafficsource/avb/AVBCustomIntervalTrafficSourceApp.h"

//CoRE4INET
#include "core4inet/utilities/ModuleAccess.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(AVBCustomIntervalTrafficSourceApp);

AVBCustomIntervalTrafficSourceApp::AVBCustomIntervalTrafficSourceApp()
{
    this->interval = SimTime(0);
}

void AVBCustomIntervalTrafficSourceApp::scheduleInterval()
{
    //custom interval
    simtime_t tick =
            check_and_cast<Oscillator*>(findModuleWhereverInNode("oscillator", getParentModule()))->getPreciseTick();
    simtime_t next_send = (this->interval / getIntervalFrames()) + par("intervalInaccurracy").doubleValue();
    if (next_send < 0)
        next_send = 0;

    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
    event->setTimer(static_cast<uint64_t>(ceil(next_send / tick)));
    event->setDestinationGate(gate("schedulerIn"));
    getTimer()->registerEvent(event);
}

void AVBCustomIntervalTrafficSourceApp::handleParameterChange(const char* parname)
{
    AVBTrafficSourceApp::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "interval"))
    {
        this->interval = SimTime(parameterDoubleCheckRange(par("intervalFrames"), 0, std::numeric_limits<double>::max(), true, false));
    }
}

} /* namespace CoRE4INET */
