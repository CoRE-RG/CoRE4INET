package ttethernet.linklayer.inControl.base;


import inet.linklayer.IOutputQueue;
import ttethernet.utilities.classes.ITimed;

//
// Interface for a module that controls incoming real-time Ethernet traffic
//
// @see TTEInput, IOutputQueue
//
moduleinterface IInControl extends IOutputQueue,ITimed
{
    @display("i=block/classifier");
}
