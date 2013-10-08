cplusplus {{
        #include "SchedulerEvent.h"
}}

namespace TTEthernetModel;

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
