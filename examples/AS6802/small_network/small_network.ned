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

package core4inet.examples.AS6802.small_network;

import inet.nodes.ethernet.Eth100M;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network small_network
{
    parameters:
        @display("bgb=,,white");
        double measure_interval @unit(s) = default(1s);
    submodules:
        node1: Node1 {
            @display("p=39,70");
        }

        node2: Node2 {
            @display("p=249,30");
        }

        node3: Node3 {
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
        node1.ethg <--> Eth100M {  length = 20m; } <--> switch1.ethg[0];
        node2.ethg <--> Eth100M {  length = 10m; } <--> switch1.ethg[1];
        node3.ethg <--> Eth100M {  length = 5m; } <--> switch1.ethg[2];
}
