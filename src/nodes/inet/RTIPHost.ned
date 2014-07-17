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
import core4inet.synchronisation.base.ISync;
import core4inet.scheduler.ITTEScheduler;
import core4inet.buffer.base.BGQueueBuffer;
import core4inet.applications.base.IApplication;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.buffer.avb.AVBQueueBuffer;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;

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
        @node;
        @labels(node,ethernet-node,wireless-node);
        string routingFile = default("");
        bool IPForward = default(true);
        bool forwardMulticast = default(false);
        int numTcpApps = default(0);  // no of TCP apps. Specify the app types in INI file with tcpApp[0..1].typename="TCPEchoApp" syntax
        bool hasTcp = default(numTcpApps>0);
        string tcpType = default(firstAvailable("TCP", "TCP_lwIP", "TCP_NSC", "TCP_None"));  // tcp implementation (e.g. ~TCP, ~TCP_lwIP, ~TCP_NSC) or ~TCPSpoof
        int numApps = default(0); //default(1) ? ListenerApp
        double hardware_delay @unit(s) = default(0us);
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

        app[numApps]: <> like IApplication {
            @display("p=380,65,row,70");
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

        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=63,315");
        }

        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=63,232");
        }

		// Buffers
        bgIn: BGQueueBuffer {
            @display("p=385,232");
        }

        bgOut: BGQueueBuffer {
            @display("p=307,232");
        }

        avbCTC: AVBIncoming {
            parameters:
                @display("p=463,150");
            gates:
                AVBout[1];
        }

        avbBuffer: AVBQueueBuffer {
            parameters:
                @display("p=463,232");
        }

        // linklayer
        srpTable: SRPTable {
            @display("p=151,150");
        }

        srpProtocol: SRProtocol {
            @display("p=151,232");
        }

        interfaceTable: InterfaceTable {
            parameters:
                @display("p=63,166;is=s");
        }

        phy[1]: TTEAVBEtherNic {

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
        networkLayer.ifOut++ --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> networkLayer.ifIn++;
        bgOut.out --> phy[0].bgIn;
        phy[0].bgOut --> bgIn.in;
        avbBuffer.out --> phy[0].AVBin;
        avbCTC.AVBout[0] --> avbBuffer.in;
        srpProtocol.out --> phy[0].srpIn;
        phy[0].srpOut --> srpProtocol.in;

		// link layer <--> outside
        phy[0].ethg <--> ethg;

}
