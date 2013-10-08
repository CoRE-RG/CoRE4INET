package ttethernet.synchronisation.base;

import ttethernet.linklayer.IPort;
import ttethernet.utilities.classes.Scheduled;

//
// Dummy synchronisation module that corrects the clock with a certain imprecission.
// It uses the simulation time as basis.
//
// @see IPort
//
// @author Till Steinbach
simple DummySync extends Scheduled like ISync
{
    parameters:
        @class(DummySync);
        @display("i=block/timer");
        
        // The time in the cycle (in ticks) when the synchronisation is triggered
        int action_time = default(0);
        
        // The precission of the synchronisation
        double precission @unit(s) = default(500ns);
        
    gates:
        //Input for time-triggered traffic
        input TTin @directIn @labels(CTFrame);
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
        //Input for scheduler messages
        input schedulerIn @directIn;
}
