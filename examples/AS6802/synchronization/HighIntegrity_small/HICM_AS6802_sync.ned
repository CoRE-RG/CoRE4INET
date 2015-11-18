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

package core4inet.examples.AS6802.synchronization.HighIntegrity_small;

import core4inet.nodes.ethernet.AS6802.TTEEtherHost;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 1ms Cycletime
// - 80ns Tick length
//
network HICM_AS6802_sync
{
    @display("bgb=431,246");
    types:
        //
        // All links are configured with 100MBit per second and variable delay
        //
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
        }
    submodules:
        unit1: Unit1 {
            @display("p=39,70");
        }

        unit2: Unit2 {
            @display("p=249,30");
        }

        unit3: Unit3 {
            @display("p=327,127");
        }

        unit4: Unit4 {
            @display("p=210,218");
        }



        switch1: Switch1 {
            parameters:
                @display("p=210,127");
            gates:
                ethg[4];
        }
    connections:
        //
        // The example uses a simple star topology
        //
      
        unit1.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[0];
        unit2.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[1];
        unit3.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[2];
        unit4.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[3];

}
