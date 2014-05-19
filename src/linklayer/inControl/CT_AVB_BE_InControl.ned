package core4inet.linklayer.inControl;

//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when avb or critical traffic to the CTC module (via sendDirect).
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple CT_AVB_BE_InControl extends CT_BE_InControl
{
    parameters:
        @display("i=block/classifier");
        @class(CT_AVB_BE_InControl);
}
