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

package core4inet.applications.trafficsink.base;

import core4inet.applications.base.ApplicationBase;

//
// Traffic sink application used for statistics collection.
//
// @see ~ApplicationBase
//
// @author Till Steinbach
//
simple TrafficSinkApp extends ApplicationBase
{
    parameters:
        @class(TrafficSinkApp);
        @display("i=block/sink");
        
        //Signal emitted when a frame is received, contains received EtherFrame
        @signal[rxPk](type=inet::EtherFrame);
        //Statistic of the amount of packets that were received by the application
        @statistic[rxPk](title="Received Packets"; source=rxPk; record=count; unit=packets);
        //Statistic of the amount of bytes that were received by the application
        @statistic[rxBytes](title="Received Bytes"; source=rxPk; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=linear); //possible parameter e.g.: measure_interval=50ms; for floatingIntervalRecorders
        //End-to-end latency
        @statistic[rxLatency](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram?,vector; interpolationmode=linear);
        //Uses encapsulated packet | Frame when nothing is encapsulated
        @statistic[rxLatencyInner](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPk))"; unit=s; record=stats,histogram?,vector; interpolationmode=linear);
}
