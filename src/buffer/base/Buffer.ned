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
package core4inet.buffer.base;

//
// Abstract base Buffer used for the various Buffers of (real-time) Ethernet.
// Since this is an abstract module please do not instantiate it
//
// @warning Currently the out gate is not used. Instead the buffer sends its
// message via sendDirect to all via addDestinationGate() registred gates.
//
// @todo The Buffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see IBuffer
//
// @author Till Steinbach
simple Buffer like IBuffer
{
    parameters:
        @display("i=block/buffer");

         //Statistic of the amount of packets that were received by the buffer
        @signal[rxPk](type=EtherFrame);
        @statistic[rxPk](title="RX Packets"; source=rxPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        //End-to-end latency
//        @statistic[latency](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram,vector; interpolationmode=none);

        //Statistic of the amount of packets that were sent by the buffer
        @signal[txPk](type=EtherFrame);
        @statistic[txPk](title="TX Packets"; source=txPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
		
		//Statistic of the End-to-end latency for each packet that is received by the buffer
		@statistic[latencyReceive](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram,vector; interpolationmode=none);
        
        //Statistic of the End-to-end latency for each packet when it lefts the buffer
        @statistic[latencyTransmit](title="End-to-end latency"; source="messageAge(txPk)"; unit=s; record=stats,histogram,vector; interpolationmode=none);
        
        //Statistic for the variance of the end-to-end latency for received and transmitted packets
        @statistic[jitterReceive](title="Jitter for received Packets"; source="SubtractActualFromLast(messageAge(rxPk))"; unit=s; record=count,min,max,vector; interpolationmode=none);
        @statistic[jitterTransmit](title="Jitter for transmitted Packets"; source="SubtractActualFromLast(messageAge(txPk))"; unit=s; record=count,min,max,vector; interpolationmode=none);
        
        //Statistics the size of packets that were received for each interval
        @statistic[bandwidthInterval](title="Bandwidth for each Interval"; source=rxPk; record=count, "IntervalCountVector(packetBytes)?", "IntervalSumVector(packetBytes)?", "IntervalAvgVector(packetBytes)?", "IntervalMinVector(packetBytes)?", "IntervalMaxVector(packetBytes)?", "IntervalVarianceVector(packetBytes)?"; interpolationmode=none);
        
        //Records the capacity for each packet that is received by the buffer. The Capacity is the relation between payload and packetsize
        @statistic[capacityInterval](title="Capacity for each Interval"; source=rxPk; record=count,"IntervalCapacityRecorder(packetBytes(innerMessage))?","IntervalCountVector(packetBytes(innerMessage))?","IntervalSumVector(packetBytes(innerMessage))?","IntervalAvgVector(packetBytes(innerMessage))?","IntervalMinVector(packetBytes(innerMessage))?","IntervalMaxVector(packetBytes(innerMessage))?","IntervalVarianceVector(packetBytes(innerMessage))?"; interpolationmode=none);
        
        //Floating Statistics for bandwidth and capacity(Slower)
        @statistic[bandwidthIntervalFloating](title="Fbaloating Bandwidth for each Interval"; source=rxPk; record=count,"sum(packetBytes)?","vector(packetBytes)?","floatingIntervalCountVector(packetBytes)?","floatingIntervalSumVector(packetBytes)?","floatingIntervalAvgVector(packetBytes)?"; interpolationmode=sample-hold);
        @statistic[capacityIntervalFloating](title="Floating Capacity for each Interval"; source=rxPk; record=count,"floatingIntervalCapacityRecorder(innerMessagePacketBytes)?","sum(innerMessagePacketBytes)?","vector(innerMessagePacketBytes)?","floatingIntervalCountVector(innerMessagePacketBytes)?","floatingIntervalSumVector(innerMessagePacketBytes)?","floatingIntervalAvgVector(innerMessagePacketBytes)?"; interpolationmode=sample-hold);
        

        //Comma seperated list of gates where the frames of the buffer are delivered
        string destination_gates = default("");
        
        int maxMessageSize @unit(B) = default(1518B);
    gates:
        //The buffers Input
        input in @loose @labels(EtherFrame);
        //The buffers Output @warning CURRENTLY NOT USED!
        output out @loose @labels(EtherFrame);
}
