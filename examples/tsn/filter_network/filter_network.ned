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

package core4inet.examples.tsn.filter_network;

import inet.node.ethernet.Eth100M;

//
// TODO
//
network filter_network
{
    parameters:
        @display("bgb=,,white");
    submodules:
        node1: Node1 {
            @display("p=39,70");
        }

        node2: Node2 {
            @display("p=260,70");
        }

        switch1: Switch1 {
            parameters:
                @display("p=147,70");
            gates:
                ethg[2];
        }
    connections:
        node1.ethg <--> Eth100M <--> switch1.ethg[0];
        node2.ethg <--> Eth100M <--> switch1.ethg[1];
}
