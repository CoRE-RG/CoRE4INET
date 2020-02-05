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
        // number of priorities
        int numPCP = default(8);
        
        //Signal emitted when a frame with corresponding q-priority is received, contains received EtherFrame
        @signal[rxQPcp*Pk](type=inet::EtherFrame);
        //Statistic of the amount of packets that were received by the application for each q-priority
        @statisticTemplate[rxQPcpPk](title="Received Packets"; record=count; unit=packets);
        //Statistic of the amount of bytes that were received by the application for each q-priority
        @statisticTemplate[rxQPcpBytes](title="Received Bytes"; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none); //possible parameter e.g.: **.floatingintervalvectorrecorder-measure-interval = 20ms for floatingIntervalRecorders
        //End-to-end latency for each q-priority
        @statisticTemplate[rxQPcpLatency](title="End-to-end latency"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        //Uses encapsulated packet | Frame when nothing is encapsulated
        @statisticTemplate[rxQPcpLatencyInner](title="End-to-end latency inner"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
}
