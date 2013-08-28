package ttethernet.linklayer.shaper;

import inet.linklayer.IOutputQueue;

//A Shaper that handles TT, PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - time-triggered
// - AVB Class A
// - PCF
// - rate-constrained
// - best-effort
simple TT_AVBClassA_PCF_RC_BE_Shaper extends TT_PCF_RC_BE_Shaper
{
    parameters:
        @display("i=block/classifier");
        @class(TT_AVBClassA_PCF_RC_BE_Shaper);
        //Statistic of the queue length of time-triggered frames
        @statistic[avbQueueLength](title="AVB-Queue Length"; record=vector; interpolationmode=sample-hold);
    gates:        
        //Input for AVB class A frames from the buffers
        input AVBin @labels(TTFrame);
}
