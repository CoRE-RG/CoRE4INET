package ttethernet.linklayer.inControl;


import inet.linklayer.IOutputQueue;

//
// Interface for a module that controls incoming real-time Ethernet traffic
//
// @see TTEInput, IOutputQueue
//
moduleinterface IInControl extends IOutputQueue
{
    @display("i=block/classifier");
}
