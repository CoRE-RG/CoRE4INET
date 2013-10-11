//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
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
