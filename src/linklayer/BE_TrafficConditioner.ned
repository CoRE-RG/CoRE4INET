package ttethernet.linklayer;

import inet.linklayer.IOutputQueue;
import inet.linklayer.ITrafficConditioner;

simple BE_TrafficConditioner like IOutputQueue, ITrafficConditioner
{
    parameters:
        @class(BETrafficConditioner);
        @display("i=block/classifier");
        //Statistic of the queue length of best-effort frames
        @statistic[beQueueLength](title="BE-Queue Length"; record=vector; interpolationmode=sample-hold);

    gates:
        //Input for best-effort frames from the upper layer (EtherLLC or IMacRelayUnit)
        input in @labels(EtherFrame);
        //Output to the lower layer (MAC layer)
        output out @labels(EtherFrame);
}
