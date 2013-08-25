package ttethernet.linklayer;

import inet.linklayer.IOutputQueue;

//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when critical traffic to the CTC module (via sendDirect).
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple TTEInput like IOutputQueue
{
    parameters:
        @display("i=block/classifier");
        //Statistic of the amount of packets that were dropped due to no configured buffer/ctc
        @statistic[ctDropped](title="Unconfigured CT dropped"; record=sum);
        // if true, all packets are received, otherwise only the ones with matching destination MAC address (This does not affect CT-Frames)
        bool promiscuous = default(false);
        //Critical traffic marker of the buffer
        int ct_marker;
        //Critical traffic mask of the buffer
        int ct_mask;
        //Comma seperated list of ctc modules the input uses
        string incomings = default("");
    gates:
        //Input from the lower layer (MAC layer)
        input in @labels(EtherFrame);
        //Output for best-effort frames to the upper layer (EtherLLC or IMacRelayUnit)
        output out @labels(EtherFrame);

}
