package ttethernet.linklayer.shaper;

import inet.linklayer.IOutputQueue;

//A Shaper that handles PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - PCF
// - rate-constrained
// - best-effort
simple PCF_RC_BE_Shaper extends BE_Shaper
{
    parameters:
        @class(PCF_RC_BE_Shaper);
		//Statistic of the queue length of protocol control frames
        @statistic[pcfQueueLength](title="PCF-Queue Length"; record=vector; interpolationmode=sample-hold);
    gates:        
        //Input for rate-constrained frames from the buffers
        input RCin @labels(RCFrame);
        //Input for protocol control frames from the buffers
        input PCFin @labels(PCFrame);
}
