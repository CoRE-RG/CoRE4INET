package core4inet.linklayer.shaper;

//A Shaper that handles TT, AVB, PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - time-triggered
// - AVB Class A
// - AVB Class B
// - PCF
// - rate-constrained
// - best-effort
simple TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper extends TT_AVBClassA_PCF_RC_BE_Shaper
{
    parameters:
        @display("i=block/classifier");
        @class(TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper);
        //Signal emitted when queue length of the avb queue changes, contains new queue length
        @signal[avbBQueueLength](type=unsigned long);
        //Statistic of the queue length of time-triggered frames
        @statistic[avbBQueueLength](title="AVBB-Queue Length"; record=vector; interpolationmode=sample-hold);

    gates:
        //Input for AVB class B frames from the buffers
        input AVBBin @labels(TTFrame);
}
