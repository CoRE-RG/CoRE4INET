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

package core4inet.examples.AS6802.synchronization.StandardIntegrity_medium;

import core4inet.nodes.ethernet.AS6802.TTEEtherHost;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 3ms Cycletime
// - 80ns Tick length
//
network SICM_AS6802_sync
{
    @display("bgb=627,246");
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
            @display("p=87,168");
        }

        unit4: Unit4 {
            @display("p=210,218");
        }

        unit5: Unit5 {
            @display("p=566,45");
        }

        unit6: Unit6 {
            @display("p=415,30");
        }

        unit7: Unit7 {
            @display("p=515,193");
        }


        switch1: Switch1 {
            parameters:
                @display("p=210,127");
            gates:
                ethg[5];
        }

        switch2: Switch2 {
            parameters:
                @display("p=430,127");
            gates:
                ethg[4];
        }

    connections:
        //
        // The example uses a simple star topology
        //
        //unit1.ethg <--> cable {  delay = 200ns; } <--> switch1.ethg[0];
        //unit2.ethg <--> cable {  delay = 100ns; } <--> switch1.ethg[1];
        //unit3.ethg <--> cable {  delay = 50ns; } <--> switch1.ethg[2];
        //unit4.ethg <--> cable {  delay = 150ns; } <--> switch1.ethg[3];
        unit1.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[0];
        unit2.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[1];
        unit3.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[2];
        unit4.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[3];

        switch2.ethg[3] <--> cable {  delay = 240ns; } <--> switch1.ethg[4];

        unit5.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[0];
        unit6.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[1];
        unit7.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[2];

}
