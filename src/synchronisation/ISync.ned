package ttethernet.synchronisation;

import ttethernet.linklayer.IPort;

//
// Synchronisation module interface
//
// @see IPort
//
// @author Till Steinbach
moduleinterface ISync extends IPort
{
    parameters:
        @display("i=block/timer");
        
    gates:
        //Input for scheduler messages
        input schedulerIn @directIn;
}
