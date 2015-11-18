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

package core4inet.examples.AS6802.synchronization.StandardIntegrity_large;

import core4inet.nodes.ethernet.AS6802.TTEEtherHost;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 3ms Cycletime
// - 80ns Tick length
//
network SICM_AS6802_sync
{
    @display("bgb=744,437");
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
            @display("p=68,55");
        }

        unit2: Unit2 {
            @display("p=165,37");
        }

        unit3: Unit3 {
            @display("p=87,168");
        }

        unit4: Unit4 {
            @display("p=356,86");
        }

        unit5: Unit5 {
            @display("p=566,45");
        }

        unit6: Unit6 {
            @display("p=415,30");
        }

        unit7: Unit7 {
            @display("p=656,102");
        }

        unit8: Unit8 {
            @display("p=39,116");
        }

        unit9: Unit9 {
            @display("p=260,30");
        }

        unit10: Unit10 {
            @display("p=68,232");
        }

        unit11: Unit11 {
            @display("p=278,207");
        }

        unit12: Unit12 {
            @display("p=68,392");
        }

        unit13: Unit13 {
            @display("p=126,392");
        }

        unit14: Unit14 {
            @display("p=221,392");
        }


        unit15: Unit15 {
            @display("p=317,379");
        }

        unit16: Unit16 {
            @display("p=391,340");
        }

        unit17: Unit17 {
            @display("p=441,392");
        }

        unit18: Unit18 {
            @display("p=505,392");
        }

        unit19: Unit19 {
            @display("p=588,392");
        }

        unit20: Unit20 {
            @display("p=663,379");
        }

        unit21: Unit21 {
            @display("p=702,320");
        }
        switch1: Switch1 {
            parameters:
                @display("p=260,127");
            gates:
                ethg[12];
        }

        switch2: Switch2 {
            parameters:
                @display("p=474,168");
            gates:
                ethg[11];
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
        unit5.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[5];
        unit6.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[6];
        unit7.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[7];
        unit8.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[8];
        unit9.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[9];
        unit10.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[10];
        unit11.ethg <--> cable {  delay = 240ns; } <--> switch1.ethg[11];

        switch2.ethg[3] <--> cable {  delay = 240ns; } <--> switch1.ethg[4];

        unit12.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[0];
        unit13.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[1];
        unit14.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[2];
        unit15.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[4];
        unit16.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[5];
        unit17.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[6];
        unit18.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[7];
        unit19.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[8];
        unit20.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[9];
        unit21.ethg <--> cable {  delay = 240ns; } <--> switch2.ethg[10];


}
