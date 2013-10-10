package ttethernet.linklayer;


//
// Interface of TTEthernet ports. A port is a virtual instance that can receive
// critical traffic through its gates.
//
// Modules implementing IPort are not necessarily physical ports.
//
// @see TTEPHYPort, Sync, IApplication
//
// @author Till Steinbach
moduleinterface IPort
{
    gates:
        //Input for time-triggered traffic
        input TTin @directIn @labels(TTFrame);
        //Input for rate-constrained traffic
        input RCin @directIn @labels(RCFrame);
}