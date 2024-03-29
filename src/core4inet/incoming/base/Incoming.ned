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

//
// Abstract module for the conformance checks of incoming traffic.
//
// @warning Since this is an abstract module do not instantiate it! Use RCIncoming or
// TTIncoming instead!
//
// @todo Since this is an abstract module it might be better to make an interface 
//
// @see ~IIncoming, ~RCIncoming, ~TTIncoming,
//
// @author Till Steinbach
//
simple Incoming like IIncoming
{
    parameters:
    //Incoming is implemented by the Incoming C++ Class
    @class(AbstractSimpleModule);
    @display("i=block/arrival");
    
    //Signal emitted when frame is received, contains received EtherFrame
    @signal[rxPk](type=inet::EtherFrame);
    //Signal emitted when frame is dropped due to implemented policy, contains dropped EtherFrame
    @signal[droppedPk](type=inet::EtherFrame);
    //Statistic of the number of packets that were received by the incoming module
    @statistic[droppedPk](title="Dropped Packets"; source=droppedPk; record=count);
    //Statistic of the number of bytes that were dropped by the incoming module
    @statistic[droppedBytes](title="Dropped Bytes"; source=droppedPk; unit=B; record="sum(packetBytes)?","vector(packetBytes)?"; interpolationmode=none);
    //Statistic of the number of packets that were received by the incoming module
    @statistic[rxPk](title="Received Packets"; source=rxPk; record=count);
    //Statistic of the number of bytes that were recveived by the incoming module
    @statistic[rxBytes](title="Received Bytes"; source=rxPk; unit=B; record="sum(packetBytes)?","vector(packetBytes)?"; interpolationmode=none);
    //Statistic of the end-to-end latency
    @statistic[latency](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
    
	//Hardware delay between incoming and outgoing buffer
	double hardware_delay @unit(s) = default(0s);

    gates:
        //input of the ctc
        input in @directIn @labels(EtherFrame);
        //output of the ctc
        output out @loose @labels(EtherFrame-conn);
}
