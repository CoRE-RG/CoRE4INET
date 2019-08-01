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

package core4inet.applications.trafficsink.IEEE8021Q;

import core4inet.applications.trafficsink.base.BGTrafficSinkApp;

//
// Traffic sink application used for statistics collection of traffic with q-priorities.
//
// @see ~BGTrafficSinkApp
//
// @author Sandra Reider
//
simple IEEE8021QTrafficSinkApp extends BGTrafficSinkApp
{
    parameters:
        @class(IEEE8021QTrafficSinkApp);
        @display("i=block/sink,darkgreen");
        
        //Signal emitted when a frame with corresponding q-priority is received, contains received EtherFrame
        @signal[rxPkQ0](type=inet::EtherFrame);
        @signal[rxPkQ1](type=inet::EtherFrame);
        @signal[rxPkQ2](type=inet::EtherFrame);
        @signal[rxPkQ3](type=inet::EtherFrame);
        @signal[rxPkQ4](type=inet::EtherFrame);
        @signal[rxPkQ5](type=inet::EtherFrame);
        @signal[rxPkQ6](type=inet::EtherFrame);
        @signal[rxPkQ7](type=inet::EtherFrame);
        //Statistic of the amount of packets that were received by the application for each q-priority
        @statistic[rxPkQ0](title="Received Packets"; source=rxPkQ0; record=count; unit=packets; );
        @statistic[rxPkQ1](title="Received Packets"; source=rxPkQ1; record=count; unit=packets; );
        @statistic[rxPkQ2](title="Received Packets"; source=rxPkQ2; record=count; unit=packets; );
        @statistic[rxPkQ3](title="Received Packets"; source=rxPkQ3; record=count; unit=packets; );
        @statistic[rxPkQ4](title="Received Packets"; source=rxPkQ4; record=count; unit=packets; );
        @statistic[rxPkQ5](title="Received Packets"; source=rxPkQ5; record=count; unit=packets; );
        @statistic[rxPkQ6](title="Received Packets"; source=rxPkQ6; record=count; unit=packets; );
        @statistic[rxPkQ7](title="Received Packets"; source=rxPkQ7; record=count; unit=packets; );
        //Statistic of the amount of bytes that were received by the application for each q-priority
        @statistic[rxBytesQ0](title="Received Bytes"; source=rxPkQ0; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none); //possible parameter e.g.: **.floatingintervalvectorrecorder-measure-interval = 20ms for floatingIntervalRecorders
        @statistic[rxBytesQ1](title="Received Bytes"; source=rxPkQ1; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none);
        @statistic[rxBytesQ2](title="Received Bytes"; source=rxPkQ2; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none);
        @statistic[rxBytesQ3](title="Received Bytes"; source=rxPkQ3; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none);
        @statistic[rxBytesQ4](title="Received Bytes"; source=rxPkQ4; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none);
        @statistic[rxBytesQ5](title="Received Bytes"; source=rxPkQ5; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none);
        @statistic[rxBytesQ6](title="Received Bytes"; source=rxPkQ6; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none);
        @statistic[rxBytesQ7](title="Received Bytes"; source=rxPkQ7; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none);
        //End-to-end latency for each q-priority
        @statistic[rxLatencyQ0](title="End-to-end latency"; source="messageAge(rxPkQ0)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyQ1](title="End-to-end latency"; source="messageAge(rxPkQ1)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyQ2](title="End-to-end latency"; source="messageAge(rxPkQ2)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyQ3](title="End-to-end latency"; source="messageAge(rxPkQ3)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyQ4](title="End-to-end latency"; source="messageAge(rxPkQ4)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyQ5](title="End-to-end latency"; source="messageAge(rxPkQ5)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyQ6](title="End-to-end latency"; source="messageAge(rxPkQ6)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyQ7](title="End-to-end latency"; source="messageAge(rxPkQ7)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        //Uses encapsulated packet | Frame when nothing is encapsulated
        @statistic[rxLatencyInnerQ0](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ0))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyInnerQ1](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ1))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyInnerQ2](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ2))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyInnerQ3](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ3))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyInnerQ4](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ4))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyInnerQ5](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ5))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyInnerQ6](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ6))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        @statistic[rxLatencyInnerQ7](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPkQ7))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
}
