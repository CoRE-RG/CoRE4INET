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

package ttethernet.examples.small_network;

import ttethernet.nodes.ethernet.TTEEtherHost;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network small_network
{
    @display("bgb=,,white");
    types:
        //
        // All links are configured with 100MBit per second and variable delay
        //
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            //bit error rate (probability (0.0-1.0) per bit)  
            ber = 0;
            //packet error rate (probability (0.0-1.0) per packet)  
            per = 0;
        }
    submodules:
        unit1: Unit1 {
            @display("p=39,70");
        }

        unit2: Unit2 {
            @display("p=249,30");
        }

        unit3: Unit3 {
            @display("p=249,102");
        }

        switch1: Switch1 {
            parameters:
                @display("p=147,70");
            gates:
                ethg[3];
        }
    connections:
        //
        // The example uses a simple star topology
        //
        unit1.ethg <--> cable {  delay = 200ns; } <--> switch1.ethg[0];
        unit2.ethg <--> cable {  delay = 100ns; } <--> switch1.ethg[1];
        unit3.ethg <--> cable {  delay = 50ns; } <--> switch1.ethg[2];
}
