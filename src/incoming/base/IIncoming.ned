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
package core4inet.incoming.base;
import inet.linklayer.IOutputQueue;

//
// Interface for modules implementing the conformance checks of incoming traffic.
//
//
// @see Incoming,
//
// @author Till Steinbach
moduleinterface IIncoming extends IOutputQueue
{
    //Incoming is implemented by the Incoming C++ Class
    @class(Incoming);
    @display("i=block/arrival");
    //Signal emitted when frame is received, contains received EtherFrame
    @signal[rxPk](type=EtherFrame);
    //Signal emitted when frame is dropped due to implemented policy, contains dropped EtherFrame
    @signal[droppedPk](type=EtherFrame);
    //Statistic of the amount of packets that were dropped by the incoming module
    @statistic[droppedPk](title="Packets Dropped"; source=droppedPk; record=count; interpolationmode=none);
    //Statistic of the amount of packets that were received by the incoming module
    @statistic[rxPk](title="RX Packets"; source=rxPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
    //Statistic of the end-to-end latency
    @statistic[latency](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram,vector; interpolationmode=none);
}
