package ttethernet.ctc;

//
// Module for the conformance checks of incoming time-triggered traffic.
//
// The traffic is checked for conformance with the receive window and afterwards
// delayed until the permanence point in time (permanence_pit). Therefore it registers a
// timer message (SchedulerActionTimeEvent) with the schduler module (TTEScheduler)
//
// @see Incoming, SchedulerActionTimeEvent, TTEScheduler
//
// @author Till Steinbach
simple TTIncoming extends Incoming
{
    parameters:
        @display("i=,red");
        //TTIncoming is implemented by the TTIncoming C++ Class
        @class(TTIncoming);
        //Beginning of the receive window in number of ticks
        int receive_window_start;
        //End of the receive window in number of ticks
        int receive_window_end;
        //permanence point in time in number of ticks
        int permanence_pit;
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
