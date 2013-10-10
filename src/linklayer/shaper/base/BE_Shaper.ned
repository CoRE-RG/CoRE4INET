package ttethernet.linklayer.shaper.base;

//A Shaper for best-effort messages.
//
//The BE_Shaper only handles best-effort traffic
simple BE_Shaper like IShaper
{
    parameters:
        @class(BE_Shaper);
        @display("i=block/classifier");
        //Statistic of the queue length of best-effort frames
        @statistic[beQueueLength](title="BE-Queue Length"; record=vector; interpolationmode=sample-hold);

    gates:
        //Input for best-effort frames from the upper layer (EtherLLC or IMacRelayUnit)
        input in @labels(EtherFrame);
        //Output to the lower layer (MAC layer)
        output out @labels(EtherFrame);
}
