package ttethernet.buffer;

//
// Represents an abstract Buffer for rate-constrained traffic. Messages are sent using the configured
// bandwidth allocation gap.
//
// The RCBuffer registers a timer (SchedulerTimerEvent) at the scheduler module (TTEScheduler) to send its
// Message in conformance with the BAG account.
//
// @warning Do not instantiate the module. Use RCDoubleBuffer or RCQueueBuffer instead! 
// Only the bag parameter is currently used!
//
// @todo The RCBuffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see RCDoubleBuffer, RCQueueBuffer, Buffer, SchedulerTimerEvent, TTEScheduler
//
// @author Till Steinbach
simple RCBuffer extends Buffer
{
    parameters:
        //RCBuffer is implemented by the RCBuffer C++ Class
        @class(RCBuffer);
        @display("i=,orange");
        // Not used
        int max_dispatch_delay = default(0);
        // Bandwidth allocation gap in number of ticks (Changes to this parameter will get active for future frames only)
        int bag = default(0);
        // Not used
        int jitter = default(0);
    gates:
        //Input gate for the incoming SchedulerTimerEvent messages
        input schedulerIn @directIn;
}
