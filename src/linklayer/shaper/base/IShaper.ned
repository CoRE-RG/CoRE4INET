package ttethernet.linklayer.shaper.base;


import inet.linklayer.IOutputQueue;

//
// Interface for real-time Ethernet traffic shapers
//
// @see BE_Shaper, PCF_RC_BE_Shaper, TT_PCF_RC_BE_Shaper, IOutputQueue
//
moduleinterface IShaper extends IOutputQueue
{
    @display("i=block/classifier");
}
