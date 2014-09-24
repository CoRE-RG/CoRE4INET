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

package core4inet.examples.inet.small_network;

import core4inet.nodes.inet.RTIPHost;
import core4inet.examples.inet.small_network.Node1;
import core4inet.examples.inet.small_network.Node3;

import inet.nodes.ethernet.Eth100M;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network small_network
{
    @display("bgb=,,white");
    submodules:
        node1: Node1 {
            @display("p=39,70");
        }

        node2: RTIPHost {
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

        configurator: IPv4NetworkConfigurator {
            @display("p=89,22");
        }
    connections:
        //
        // The example uses a simple star topology
        //
        node1.ethg <--> Eth100M {  length = 20m; } <--> switch1.ethg[0];
        node2.ethg <--> Eth100M {  length = 10m; } <--> switch1.ethg[1];
        node3.ethg <--> Eth100M {  length = 5m; } <--> switch1.ethg[2];
}
