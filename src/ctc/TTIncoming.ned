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
        //Beginning of the receive window in number of ticks (-1 means no receive window)
        int receive_window_start @unit(tick);
        //End of the receive window in number of ticks (-1 means no receive window)
        int receive_window_end @unit(tick);
        //permanence point in time in number of ticks (-1 means no permanence point, frame is relayed immediately)
        int permanence_pit @unit(tick);
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
