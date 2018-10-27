package core4inet.linklayer.shaper;

// A Shaper that handles TT, AVB, PCF, RC and IEEE 802.1Q traffic with an additional backdoor
// This shaper handles traffic in the following order (highest to lowest priority):
// - messages arriving through backdoor
// - time-triggered
// - AVB Class A
// - AVB Class B
// - PCF
// - rate-constrained
// - IEEE 802.1Q
simple Backdoor_TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper extends TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper
{
    parameters:
        @display("i=block/classifier");
        @class(Backdoor_TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper);
        
        //Signal emitted when queue length of the be queue changes, contains new queue length
        @signal[BackdoorQueueLength](type=unsigned long; unit=packets);
        //Signal emitted when queue size of the be queue changes, contains new queue size in bytes
        @signal[BackdoorQueueSize](type=unsigned long; unit=B);
        
        //Statistic of the queue length of backdoor frames
        @statistic[BackdoorQueueLength](title="Backdoor-Queue Length"; unit=packets; record=vector,stats; interpolationmode=sample-hold);
		//Statistic of the queue length of backdoor frames
        @statistic[BackdoorQueueSize](title="Backdoor-Queue Size"; unit=B; record=vector,stats; interpolationmode=sample-hold);
        
    gates:
        input Backdoorin @labels(EtherFrame);
}
