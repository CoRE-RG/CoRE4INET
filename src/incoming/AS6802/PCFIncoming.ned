package ttethernet.incoming.AS6802;

import ttethernet.incoming.base.Incoming;

//
// Module for the conformance checks of incoming protocol control frames.
//
// The traffic is checked for conformance with pcfType.
//
// @warning Only the bag parameter is used!
//
// @see Incoming,
//
// @author Lazar Todorov, Till Steinbach
simple PCFIncoming extends Incoming
{
    parameters:
        @display("i=,green");
        //PCFIncoming is implemented by the PCFIncoming C++ Class
        @class(PCFIncoming);
        //Allowed PCF-Type for this CTC (CS = 1; IN = 2; CA = 3)
        int pcfType=default(0);
}
