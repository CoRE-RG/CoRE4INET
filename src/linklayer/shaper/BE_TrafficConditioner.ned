package ttethernet.linklayer.shaper;

import inet.linklayer.IOutputQueue;

simple BE_Shaper like IOutputQueue
{
    parameters:
        @class(BEShaper);
        @display("i=block/classifier");
        //Statistic of the queue length of best-effort frames
        @statistic[beQueueLength](title="BE-Queue Length"; record=vector; interpolationmode=sample-hold);

    gates:
        //Input for best-effort frames from the upper layer (EtherLLC or IMacRelayUnit)
        input in @labels(EtherFrame);
        //Output to the lower layer (MAC layer)
        output out @labels(EtherFrame);
}
