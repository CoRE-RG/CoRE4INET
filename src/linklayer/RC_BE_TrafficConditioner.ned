package ttethernet.linklayer;

import inet.linklayer.IOutputQueue;
import inet.linklayer.ITrafficConditioner;

simple RC_BE_TrafficConditioner extends BE_TrafficConditioner
{
    parameters:
        @class(RCTrafficConditioner);
        @display("i=block/classifier");
		//Statistic of the queue length of protocol control frames
        @statistic[pcfQueueLength](title="PCF-Queue Length"; record=vector; interpolationmode=sample-hold);
    gates:        
        //Input for rate-constrained frames from the buffers
        input RCin @labels(RCFrame);
        //Input for protocol control frames from the buffers
        input PCFin @labels(PCFrame);
}
