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

import inet.linklayer.IOutputQueue;

//
// Interface representing a buffer module.
//
//
// @see Buffer
//
// @author Till Steinbach
moduleinterface IBuffer extends IOutputQueue
{
    parameters:
        @display("i=block/buffer");

         //Statistic of the amount of packets that were received by the buffer
        @signal[rxPk](type=EtherFrame);
        @statistic[rxPk](title="RX Packets"; source=rxPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        //End-to-end latency
        @statistic[latency](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram,vector; interpolationmode=none);

        //Statistic of the amount of packets that were sent by the buffer
        @signal[txPk](type=EtherFrame);
        @statistic[txPk](title="TX Packets"; source=txPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);


        //Comma seperated list of gates where the frames of the buffer are delivered
        string destination_gates;
}

