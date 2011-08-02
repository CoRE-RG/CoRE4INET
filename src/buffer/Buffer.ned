package ttethernet.buffer;

import inet.networklayer.queue.IOutputQueue;
//
// Abstract base Buffer used for the various Buffers of TTEthernet.
// Since this is an abstract module please do not instantiate it
//
// @warning Currently the out gate is not used. Instead the buffer sends its
// message via sendDirect to all via addDestinationGate() registred gates.
//
// @todo The Buffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see IOutputQueue
//
// @author Till Steinbach
simple Buffer like IOutputQueue
{
    parameters:
        @display("i=block/buffer");
        //Statistic of the amount of packets that were sent by the buffer
        @statistic[txPk](title="TX Packets"; record=count,vector);
        //Priority of the buffer (currently only used for rate-constrained traffic)
        int priority=-1;
        
    gates:
        //The buffers Input
        input in @labels(CTFrame);
        //The buffers Output @warning CURRENTLY NOT USED!
        output out @labels(CTFrame);
}
