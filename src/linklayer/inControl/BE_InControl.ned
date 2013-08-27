package ttethernet.linklayer.inControl;

import inet.linklayer.IOutputQueue;

//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when critical traffic to the CTC module (via sendDirect).
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple BE_InControl like IInControl
{
    parameters:
        @display("i=block/classifier");
        @class(BE_InControl);
        // if true, all packets are received, otherwise only the ones with matching destination MAC address (This does not affect CT-Frames)
        bool promiscuous = default(false);
    gates:
        //Input from the lower layer (MAC layer)
        input in @labels(EtherFrame);
        //Output for best-effort frames to the upper layer (EtherLLC or IMacRelayUnit)
        output out @labels(EtherFrame);

}
