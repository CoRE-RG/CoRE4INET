package ttethernet.ctc;

import ttethernet.utilities.classes.ITimed;
//
// Module for the conformance checks of incoming rate-constrained traffic.
//
// The traffic is checked for conformance with the bag.
//
// @warning Only the bag parameter is used!
//
// @see Incoming,
//
// @author Till Steinbach
simple RCIncoming extends Incoming like ITimed
{
    parameters:
        @display("i=,orange");
        //RCIncoming is implemented by the RCIncoming C++ Class
        @class(RCIncoming);
        // Bandwidth allocation gap in number of ticks (Changes to this parameter will get active for future frames only)
        int bag @unit(tick) = default(0tick);
        //Not used
        int jitter @unit(tick) = default(0tick);
        
        string oscillator = default("oscillator");
        string timer = default("timer");
}
