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

package core4inet.nodes.inet;

import core4inet.linklayer.ethernet.TTEAVBEtherNic;

import inet.base.NotificationBoard;
import inet.linklayer.loopback.LoopbackInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.nodes.inet.NetworkLayer;
import inet.applications.ITCPApp;
import inet.transport.ITCP;


//
// Contains the common lower layers (linklayer and networklayer)
// of Router, StandardHost, WirelessHost etc.
//
// NOTE:
//    - IPForward is turned on by default.
//    - use this model only as a base type. In simulations use ~Router,
//      ~StandardHost, ~WirelessHost and ~AdhocHost
//
module RTIPHost
{
    parameters:
        @display("bgb=,448");
        @node;
        @labels(node,ethernet-node,wireless-node);
        string routingFile = default("");
        bool IPForward = default(true);
        bool forwardMulticast = default(false);
        int numTcpApps = default(0);  // no of TCP apps. Specify the app types in INI file with tcpApp[0..1].typename="TCPEchoApp" syntax
        bool hasTcp = default(numTcpApps>0);
        string tcpType = default(firstAvailable("TCP", "TCP_lwIP", "TCP_NSC", "TCP_None"));  // tcp implementation (e.g. ~TCP, ~TCP_lwIP, ~TCP_NSC) or ~TCPSpoof
    gates:
        inout ethg @labels(EtherFrame-conn);
    submodules:

        notificationBoard: NotificationBoard {
            parameters:
                @display("p=63,34;is=s");
        }

        // application Layer
        tcpApp[numTcpApps]: <> like ITCPApp {
            parameters:
                @display("p=229,65,row,60");
        }

        // transport Layer
        tcp: <tcpType> like ITCP if hasTcp {
            parameters:
                @display("p=229,150");
        }

        // network layer
        networkLayer: NetworkLayer {
            parameters:
                @display("p=229,232;q=queue");
        }

        routingTable: RoutingTable {
            parameters:
                @display("p=63,104;is=s");
                IPForward = IPForward;
                forwardMulticast = forwardMulticast;
                routingFile = routingFile;
        }

        // linklayer
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=63,166;is=s");
        }

        tteavbEtherNic: TTEAVBEtherNic {

            @display("p=229,315");
        }
    connections allowunconnected:

        // application Layer <--> transport Layer
        for i=0..numTcpApps-1 {
            tcpApp[i].tcpOut --> tcp.appIn++;
            tcpApp[i].tcpIn <-- tcp.appOut++;
        }

		// transport Layer <--> network Layer
        tcp.ipOut --> networkLayer.transportIn++ if hasTcp;
        tcp.ipIn <-- networkLayer.transportOut++ if hasTcp;

        // network Layer <--> link Layer
        networkLayer.ifOut++ --> tteavbEtherNic.upperLayerIn;
        tteavbEtherNic.upperLayerOut --> networkLayer.ifIn++;

		// link layer <--> outside
        tteavbEtherNic.ethg <--> ethg;

}
