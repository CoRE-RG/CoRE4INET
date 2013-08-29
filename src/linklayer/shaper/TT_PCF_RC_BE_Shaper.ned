package ttethernet.linklayer.shaper;

import inet.linklayer.IOutputQueue;

//A Shaper that handles TT, PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - time-triggered
// - PCF
// - rate-constrained
// - best-effort
simple TT_PCF_RC_BE_Shaper extends PCF_RC_BE_Shaper
{
    parameters:
        @display("i=block/classifier");
        @class(TT_PCF_RC_BE_Shaper);
        //Statistic of the queue length of time-triggered frames
        @statistic[ttQueueLength](title="TT-Queue Length"; record=vector; interpolationmode=sample-hold);
        //Comma seperated list of TTBuffers that send messages to this port
        string tt_buffers = default("");
    gates:        
        //Input for time-triggered frames from the buffers
        input TTin @labels(TTFrame);
}
