package ttethernet.synchronisation.base;

import ttethernet.linklayer.IPort;
import ttethernet.utilities.classes.IScheduled;

//
// Synchronisation module interface
//
// @see IPort
//
// @author Till Steinbach
moduleinterface ISync extends IPort, IScheduled
{
    parameters:
        @display("i=block/timer");
    gates:
        //Input for scheduler messages
        input schedulerIn @directIn;
}
