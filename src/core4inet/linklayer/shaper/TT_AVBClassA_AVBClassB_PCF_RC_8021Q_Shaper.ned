package core4inet.linklayer.shaper;

//A Shaper that handles TT, AVB, PCF, RC and IEEE 802.1Q traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - time-triggered
// - AVB Class A
// - AVB Class B
// - PCF
// - rate-constrained
// - IEEE 802.1Q
simple TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper extends TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper
{
    parameters:
        @display("i=block/classifier");
        @class(TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper);
        //Signal emitted when queue length of the rc queue changes, contains new queue length
        @signal[q*QueueLength](type=unsigned long);
        //Statistic of the queue length of rate-constrained frames
        @statisticTemplate[qQueueLength](title="Q-Queue Length ($name)"; record=vector; interpolationmode=sample-hold);
        
		//Untagged VLAN. Outgoing frames with this VLAN get untagged
        int untaggedVID = default(0);
        //Interface allows frames with this VLAN to leave the port
        string taggedVIDs = default("0");
        //Default Priority. Frames without Q-tag will be treated with this priority
        int defaultPriority = default(0);
    gates:
}
