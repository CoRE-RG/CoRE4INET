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

package core4inet.applications.trafficsink.AS6802;

import core4inet.applications.base.ApplicationBase;

//
// Traffic sink application used for statistics collection of multiple different virtual links.
//
// @see ApplicationBase
//
// @author Till Steinbach
simple MultiCTTrafficSinkApp extends ApplicationBase
{
    parameters:
        @class(MultiTrafficSinkApp);
        @display("i=block/sink");
        //Signal emitted when a frame is received, contains received EtherFrame
        @signal[rxPk:*](type=EtherFrame);
        //Statistic of the amount of packets that were received by the application
        @statisticTemplate[rxPk](title="RX Packets"; record=count,"sum(packetBytes)","vector(packetBytes)","floatingIntervalCountVector(packetBytes)?","floatingIntervalSumVector(packetBytes)?","floatingIntervalAvgVector(packetBytes)?"; interpolationmode=linear); //possible parameter e.g.: measure_interval=50ms; for floatingIntervalRecorders
        //End-to-end latency
        //Uses encapsulated packet or frame when nothing is encapsulated
        //@statistic[latency](title="End-to-end latency"; unit=s; record=stats,histogram,vector);
        @statisticTemplate[latency](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram,vector; interpolationmode=linear);
        @statistic[innerLatency](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPk))"; unit=s; record=stats,histogram,vector; interpolationmode=linear);
}
