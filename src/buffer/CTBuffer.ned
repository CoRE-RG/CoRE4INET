package ttethernet.buffer;

import inet.linklayer.IOutputQueue;
//
// Abstract base Buffer used for critical traffic Buffers of TTEthernet.
// Since this is an abstract module please do not instantiate it
//
// @warning Currently the out gate is not used. Instead the buffer sends its
// message via sendDirect to all via addDestinationGate() registred gates.
//
// @todo The CTBuffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see Buffer
//
// @author Till Steinbach
simple CTBuffer extends Buffer
{
    parameters:
        @display("i=block/buffer");
        //Statistic of the amount of packets that were sent by the buffer
        @statistic[txPk](title="TX Packets"; record=count,vector);
        //End-to-end latency
        @statistic[latency](title="End-to-end latency"; unit=s; record=stats,histogram,vector);
        //Priority of the buffer (currently only used for rate-constrained traffic)
        int priority=default(-1);
        //Critical traffic ID of the buffer
        int ct_id;
        //Critical traffic marker of the buffer
        int ct_marker;
        //Critical traffic mask of the buffer
        int ct_mask;

}
