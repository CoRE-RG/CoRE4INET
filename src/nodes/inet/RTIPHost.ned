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
import core4inet.nodes.inet.RTNetworkLayer;

import inet.base.NotificationBoard;
import inet.linklayer.loopback.LoopbackInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.nodes.inet.NetworkLayer;
import inet.applications.IPingApp;
import inet.applications.ISCTPApp;
import inet.applications.ITCPApp;
import inet.applications.IUDPApp;
import inet.transport.ISCTP;
import inet.transport.ITCP;
import inet.transport.IUDP;


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
        int numUdpApps = default(0);  // no of UDP apps. Specify the app types in INI file with udpApp[0..1].typename="UDPVideoStreamCli" syntax
        int numSctpApps = default(0); // no of SCTP apps. Specify the app types in INI file with sctpApp[0..1].typename="SCTPServer" syntax
        int numPingApps = default(0);  // no of PING apps. Specify the app types in INI file with pingApp[0..1].typename="PingApp" syntax
        bool hasTcp = default(numTcpApps>0);
        bool hasUdp = default(numUdpApps>0);
        bool hasSctp = default(numSctpApps>0);
        string tcpType = default(firstAvailable("TCP", "TCP_lwIP", "TCP_NSC", "TCP_None"));  // tcp implementation (e.g. ~TCP, ~TCP_lwIP, ~TCP_NSC) or ~TCPSpoof
        string udpType = default(firstAvailable("UDP","UDP_None"));
        string sctpType = default(firstAvailable("SCTP","SCTP_None"));
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
                @display("p=498,65,row,60");
        }

        app[numApps]: <> like IApplication {
            @display("p=849,232,row,70");
        }

        udpApp[numUdpApps]: <> like IUDPApp {
            parameters:
                @display("p=615,65,row,60");
        }

        sctpApp[numSctpApps]: <> like ISCTPApp {
            parameters:
                @display("p=732,65,row,60");
        }

        pingApp[numPingApps]: <default("PingApp")> like IPingApp {
            parameters:
                @display("p=849,141,row,60");
        }

        // transport Layer
        tcp: <tcpType> like ITCP if hasTcp {
            parameters:
                @display("p=498,150");
        }

        udp: <udpType> like IUDP if hasUdp {
            parameters:
                @display("p=615,150");
        }

        sctp: <sctpType> like ISCTP if hasSctp {
            @display("p=732,141");
        }

        // network layer
        networkLayer: RTNetworkLayer {
            parameters:
                @display("p=498,232;q=queue");
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
        avbCTC: AVBIncoming {
            parameters:
                @display("p=186,150");
            gates:
                AVBAout[1];
                AVBBout[1];
        }

        avbABuffer: AVBQueueBuffer {
            parameters:
                srClass = "A";
                @display("p=201,232");
        }

        avbBBuffer: AVBQueueBuffer {
            parameters:
                srClass = "B";
                @display("p=135,232");
        }

        // linklayer
        srpTable: SRPTable {
            @display("p=420,150");
        }

        srpProtocol: SRProtocol {
            @display("p=420,232");
        }

        interfaceTable: InterfaceTable {
            parameters:
                @display("p=63,166;is=s");
        }

        phy[1]: TTEAVBEtherNic {

            @display("p=498,315");
        }
    connections allowunconnected:

        // application Layer <--> transport Layer
        for i=0..numTcpApps-1 {
            tcpApp[i].tcpOut --> tcp.appIn++;
            tcpApp[i].tcpIn <-- tcp.appOut++;
        }

        for i=0..numUdpApps-1 {
            udpApp[i].udpOut --> udp.appIn++;
            udpApp[i].udpIn <-- udp.appOut++;
        }

        udp.ipOut --> networkLayer.transportIn++ if hasUdp;
        udp.ipIn <-- networkLayer.transportOut++ if hasUdp;

        for i=0..numSctpApps-1 {
            sctpApp[i].sctpOut --> sctp.from_appl++;
            sctp.to_appl++ --> sctpApp[i].sctpIn;
        }
        sctp.to_ip --> networkLayer.transportIn++ if hasSctp;
        networkLayer.transportOut++ --> sctp.from_ip if hasSctp;

        for i=0..numPingApps-1 {
            networkLayer.pingOut++ --> pingApp[i].pingIn;
            networkLayer.pingIn++ <-- pingApp[i].pingOut;
        }

		// transport Layer <--> network Layer
        tcp.ipOut --> networkLayer.transportIn++ if hasTcp;
        tcp.ipIn <-- networkLayer.transportOut++ if hasTcp;

        // network Layer <--> link Layer
        networkLayer.ifOut++ --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> networkLayer.ifIn++;
        avbABuffer.out --> phy[0].AVBAin;
        avbBBuffer.out --> phy[0].AVBBin;
        avbCTC.AVBAout[0] --> avbABuffer.in;
        avbCTC.AVBBout[0] --> avbBBuffer.in;
        srpProtocol.out --> phy[0].srpIn;
        phy[0].srpOut --> srpProtocol.in;

		// link layer <--> outside
        phy[0].ethg <--> ethg;

}
