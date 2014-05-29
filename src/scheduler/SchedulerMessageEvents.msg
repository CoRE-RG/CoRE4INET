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
cplusplus {{
    //CoRE4INET
    #include "CoRE4INET_SchedulerEvent.h"
}}

namespace CoRE4INET;

class SchedulerEvent;

//
// Message used for events of TTEScheduler that are triggered at a specified time in cycle (action_time).
// Should be created with message kind SchedulerMessageKind = ACTION_TIME_EVENT
//
// @see SchedulerMessageKind, SchedulerEvent
//
// @author Till Steinbach
message SchedulerActionTimeEvent extends SchedulerEvent {
        // Action time in cycle for the event in number of ticks
        uint32_t action_time;
        //force execution in next cycle at the earliest
        bool next_cycle;
}

//
// Message used for events of TTEScheduler that are triggered after a specified time (timer).
// Should be created with message kind SchedulerMessageKind = TIMER_EVENT
//
// @see SchedulerMessageKind, SchedulerEvent
//
// @author Till Steinbach
message SchedulerTimerEvent extends SchedulerEvent {
        // Time after that the event is triggered in number of ticks
        uint64_t timer;
}
