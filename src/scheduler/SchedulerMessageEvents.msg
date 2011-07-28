cplusplus {{
#include "SchedulerEvent.h"
}}

namespace TTEthernetModel;

class SchedulerEvent;

message SchedulerActionTimeEvent extends SchedulerEvent {
    unsigned int action_time;
}

message SchedulerTimerEvent extends SchedulerEvent {
    unsigned int timer;
}
