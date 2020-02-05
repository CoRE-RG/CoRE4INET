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

package core4inet.applications.trafficsource.IEEE8021Q;

import core4inet.applications.trafficsource.base.BGTrafficSourceApp;

//
// Traffic source application used for IEEE 802.1Q traffic.
//
// @see ~BGTrafficSourceApp, ~TTTrafficSourceApp, ~RCTrafficSourceApp
//
// @author Till Steinbach, Philipp Meyer
//
simple IEEE8021QTrafficSourceApp extends BGTrafficSourceApp
{
    parameters:
        @class(IEEE8021QTrafficSourceApp);
        @display("i=block/source,blue");
        
        // IEEE 802.1q priority (0=None, 1=Lowest, 7=Highest)
    	int priority = default(0);
    	// VLAN ID (0=untagged, 4094=Highest)
    	int vid = default(0);
    	// Number of priorities.
        int numPCP = default(8);
    	
    	//Signal emitted when a frame with corresponding q-priority is send for each q-priority
        @signal[txQPcp*Pk](type=inet::EtherFrame);
        //Statistic of the amount of packets that were send by the application for each q-priority
        @statisticTemplate[txQPcpPk](title="Send Packets"; record=count; unit=packets);
        //Statistic of the amount of bytes that were send by the application
        @statisticTemplate[txQPcpBytes](title="Send Bytes"; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none); //possible parameter e.g.: **.floatingintervalvectorrecorder-measure-interval = 20ms for floatingIntervalRecorders
}
