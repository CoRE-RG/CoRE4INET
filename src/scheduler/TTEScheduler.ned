package ttethernet.scheduler;

//
// TTEthernet scheduler module. The module allows to register Events using the
// registerEvent(SchedulerEvent) method. Allowed Events are:
// - SchedulerActionTimeEvent: Event that is triggered at a specified time in the cycle
// - SchedulerTimerEvent: Event that is triggered after a specified time
//
// The Scheduler can be asked for the current time with the getTicks() method.
// The cycle is configured by the parameters tick and cycle_ticks.
//
// @see SchedulerTimerEvent, SchedulerActionTimeEvent, SchedulerTimerEvent
//
// @author Till Steinbach
simple TTEScheduler
{
    parameters:
        @display("i=block/cogwheel");
        // Length of a tick
        double tick @unit(s) = 80ns;
        // Number of ticks for one cycle
        int cycle_ticks=37500;
}
