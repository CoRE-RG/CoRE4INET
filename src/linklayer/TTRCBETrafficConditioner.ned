package ttethernet.linklayer;

import inet.linklayer.IOutputQueue;
import inet.linklayer.ITrafficConditioner;

simple TT_RC_BE_TrafficConditioner extends RC_BE_TrafficConditioner
{
    parameters:
        @class(TT_RC_BE_TrafficConditioner);
        @display("i=block/classifier");
        //Statistic of the queue length of time-triggered frames
        @statistic[ttQueueLength](title="TT-Queue Length"; record=vector; interpolationmode=sample-hold);
		//Comma seperated list of TTBuffers that send messages to this port
        string tt_buffers = default("");
    gates:        
        //Input for time-triggered frames from the buffers
        input TTin @labels(TTFrame);
}
