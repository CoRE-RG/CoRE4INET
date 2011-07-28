namespace TTEthernetModel;

message SchedulerMessage {
}

message SchedulerEvent extends SchedulerMessage {
    @customize(true);
}

enum SchedulerMessageKind {
    NEW_CYCLE=0;
    ACTION_TIME_EVENT=1;
    TIMER_EVENT=2;
}