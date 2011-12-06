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
        //Statistic of the current drift (Difference of configured and actual tick length)
        @statistic[currentDrift](title="Current drift"; record=vector);
        //Statistic of the beginning of a new cycle
        @statistic[newCycle](title="Start of cycle"; record=count,vector);
        // Length of a tick
        double tick @unit(s) = 80ns;
        // Maximum clock drift (e.g 16ps for 200ppm at 80ns per tick)
        double max_drift @unit(s) = 16ps;
        // Maximum clock drift change per cycle
        double max_drift_change @unit(s) = 1ps;
        // Current length of a tick (with imprecission)
        double current_tick @unit(s) = tick;
        // Number of ticks for one cycle
        int cycle_ticks=37500;
}
