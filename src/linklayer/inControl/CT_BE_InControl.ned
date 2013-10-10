package ttethernet.linklayer.inControl;

import ttethernet.linklayer.inControl.base.BE_InControl;
import inet.linklayer.IOutputQueue;

//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when critical traffic to the CTC module (via sendDirect).
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple CT_BE_InControl extends BE_InControl
{
    parameters:
        @display("i=block/classifier");
        @class(CT_BE_InControl);
        //Statistic of the amount of packets that were dropped due to no configured buffer/ctc
        @statistic[ctDropped](title="Unconfigured CT dropped"; record=sum);
		//Critical traffic marker of the buffer
        int ct_marker;
        //Critical traffic mask of the buffer
        int ct_mask;
        //Comma seperated list of ctc modules the input uses
        string ct_incomings = default("");
}
