namespace TTEthernetModel;

//
// abstract base message for TTEScheduler.
//
// @see TTEScheduler
//
// @author Till Steinbach
message SchedulerMessage {
}

//
// Message used for events of TTEScheduler with SchedulerMessageKind = NEW_CYCLE
//
// @see SchedulerMessageKind
//
// @author Till Steinbach
message SchedulerEvent extends SchedulerMessage {
    @customize(true);
}

//
// Enum for different SchedulerEvent messages 
//
// @see SchedulerEvent
//
// @author Till Steinbach
enum SchedulerMessageKind {
    // Event that signals the beginning of a new cycle
    NEW_CYCLE=0;
    // Event with a specified action time
    ACTION_TIME_EVENT=1;
    // Event that is triggered after a specified amount of time
    TIMER_EVENT=2;
}