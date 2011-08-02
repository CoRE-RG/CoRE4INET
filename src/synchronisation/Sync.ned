package ttethernet.synchronisation;

import ttethernet.linklayer.IPort;

//
// Synchronisation module
//
// @todo NOT YET IMPLEMENTED
//
// @see IPort
//
// @author Till Steinbach
simple Sync like IPort
{
    parameters:
        @display("i=block/timer");
        
    gates:
        //Input for time-triggered traffic
        input TTin @directIn @labels(CTFrame);
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
}
