package ttethernet.ctc;

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
simple RCIncoming extends Incoming
{
    parameters:
        //RCIncoming is implemented by the RCIncoming C++ Class
        @class(RCIncoming);
        // Bandwidth allocation gap in number of ticks (Changes to this parameter will get active for future frames only)
        int bag;
        //Not used
        int jitter;
}
