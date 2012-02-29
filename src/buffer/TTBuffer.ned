package ttethernet.buffer;

//
// Represents an abstract Buffer for time-triggerd traffic. Messages are sent using the configured
// send window.
//
// The TTBuffer registers a timer (SchedulerActionTimeEvent) at the scheduler module (TTEScheduler) to send its
// Message in conformance with the send window.
//
// @warning Do not instantiate the module. Use TTDoubleBuffer or TTQueueBuffer instead!
//
// @todo The TTBuffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see TTDoubleBuffer, TTQueueBuffer, Buffer, SchedulerActionTimeEvent, TTEScheduler
//
// @author Till Steinbach
simple TTBuffer extends Buffer
{
    parameters:
        //TTBuffer is implemented by the TTBuffer C++ Class
        @class(TTBuffer);
        @display("i=,red");
        //Beginning of the send window in number of ticks (Changes to this parameter will get active for future scheduled frames only)
        int sendWindowStart=default(0);
        //End of the send window in number of ticks
        int sendWindowEnd=default(0);
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;

}
