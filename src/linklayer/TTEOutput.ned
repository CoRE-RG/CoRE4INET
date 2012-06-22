package ttethernet.linklayer;

import inet.linklayer.IOutputQueue;
//
// Module for outgoing traffic to MAC layer. The module maintains the adherence of priorities
// for all traffic classes.
//
// @todo Statistics for rate-constrained queue lengths (per priority if possible)
// @todo Better documentation of behaviour!
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple TTEOutput like IOutputQueue
{
    parameters:
        @display("i=block/tx");
        //Statistic of the queue length of time-triggered frames
        @statistic[ttQueueLength](title="TT-Queue Length"; record=vector; interpolationmode=sample-hold);
        //Statistic of the queue length of best-effort frames
        @statistic[beQueueLength](title="BE-Queue Length"; record=vector; interpolationmode=sample-hold);
        //Statistic of the queue length of protocol control frames
        @statistic[pcfQueueLength](title="PCF-Queue Length"; record=vector; interpolationmode=sample-hold);
        //Comma seperated list of TTBuffers that send messages to this port
        string tt_buffers = default("");
    gates:
        //Input for best-effort frames from the upper layer (EtherLLC or IMacRelayUnit)
        input in @labels(EtherFrame);
        //Output to the lower layer (MAC layer)
        output out @labels(EtherFrame);

        //Input for time-triggered frames from the buffers
        input TTin @labels(CTFrame);
        //Input for rate-constrained frames from the buffers
        input RCin @labels(CTFrame);
        //Input for protocol control frames from the buffers
        input PCFin @labels(CTFrame);
}
