package ttethernet.buffer.base;

import inet.linklayer.IOutputQueue;
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
        //End-to-end latency
        @statistic[latency](title="End-to-end latency"; unit=s; record=stats,histogram,vector);

        //Comma seperated list of gates where the frames of the buffer are delivered
        string destination_gates = default("");
    gates:
        //The buffers Input
        input in @loose @labels(EtherFrame);
        //The buffers Output @warning CURRENTLY NOT USED!
        output out @loose @labels(EtherFrame);
}
