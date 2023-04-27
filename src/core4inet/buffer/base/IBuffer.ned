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

import inet.common.queue.IOutputQueue;

//
// Interface representing a buffer module.
//
// Buffers are used in CoRE4INET to hold frames between reception and transmitting. There are various types of buffers
// with different behavior for AS6802, AVB and background traffic.
//
// @see Buffer
//
// @author Till Steinbach
//
moduleinterface IBuffer extends IOutputQueue
{
    parameters:
        @display("i=block/buffer");

        //Signal is emitted when when frame is received. Contains the received frame.
        @signal[rxPk](type=inet::EtherFrame);
        //Signal is emitted when when frame is transmitted. Contains the transmitted frame.
        @signal[txPk](type=inet::EtherFrame);

        //Statistic of the number of packets that were received by the buffer
        @statistic[rxPk](title="Received Packets"; source=rxPk; unit=packets; record=count);
        //Statistic of the number of Bytes that were received by the buffer
        @statistic[rxBytes](title="Received Bytes"; source=rxPk; unit=B; record="sum(packetBytes)?","vector(packetBytes)?","histogram(packetBytes)?"; interpolationmode=none);
        //Statistic of the number of packets that were received by the buffer
        @statistic[txPk](title="Transmitted Packets"; source=txPk; unit=packets; record=count);
        //Statistic of the number of Bytes that were received by the buffer
        @statistic[txBytes](title="Transmitted Bytes"; source=txPk; unit=B; record="sum(packetBytes)","vector(packetBytes)","histogram(packetBytes)?"; interpolationmode=none);
        //End-to-end latency recorded when frame is received. Contains the time from frame creation until received in the Buffer
        @statistic[rxLatency](title="End-to-end latency (received)"; source="messageAge(rxPk)"; unit=s; record=?stats,histogram?,vector?; interpolationmode=none);
        //End-to-end latency recorded when frame is transmitted. Contains the time from frame creation until transmitted from the Buffer
        @statistic[txLatency](title="End-to-end latency (transmitted)"; source="messageAge(txPk)"; unit=s; record=stats?,histogram?,vector?; interpolationmode=none);
        //Maximum packet size in Interval
        @statistic[maxPacketSize](title="Maximum Packet Size in Interval"; source=rxPk; unit=B; record="IntervalMaxVector(packetBytes)?"; interpolationmode=linear);
        //Minimum packet size in Interval
        @statistic[minPacketSize](title="Minimum Packet Size in Interval"; source=rxPk; unit=B; record="IntervalMinVector(packetBytes)?"; interpolationmode=linear);
        //Utilized Bandwidth over Interval
        @statistic[bandwidth](title="Bandwidth used over Interval"; source=rxPk; unit=B; record="IntervalSumVector(packetBytes)?"; interpolationmode=linear);
 
        //Comma seperated list of gates where the frames of the buffer are delivered
        string destination_gates;
}

