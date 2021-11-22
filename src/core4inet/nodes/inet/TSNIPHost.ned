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

import inet.node.inet.INetworkNode;

// from INET::NodeBase
import inet.common.lifecycle.NodeStatus;
import inet.common.packet.PcapRecorder;
import inet.linklayer.contract.IExternalNic;
import inet.linklayer.contract.ITunNic;
import inet.linklayer.contract.IWiredNic;
import inet.linklayer.contract.IWirelessNic;
import inet.linklayer.loopback.LoopbackInterface;
import inet.mobility.contract.IMobility;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.contract.INetworkLayer;
import inet.networklayer.contract.IRoutingTable;
import inet.power.contract.IEnergyGenerator;
import inet.power.contract.IEnergyManagement;
import inet.power.contract.IEnergyStorage;

// from INET::StandardHost
import inet.applications.contract.IPingApp;
import inet.applications.contract.ISCTPApp;
import inet.applications.contract.ITCPApp;
import inet.applications.contract.IUDPApp;
import inet.transportlayer.contract.ISCTP;
import inet.transportlayer.contract.ITCP;
import inet.transportlayer.contract.IUDP;
import inet.applications.contract.ITunApp;

//CoRE4INET
import core4inet.linklayer.ethernet.ICoRE4INETEtherNic;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.linklayer.ethernet.avb.SRPEtherEncapAdapter;
import core4inet.buffer.avb.AVBQueueBuffer;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.applications.base.IApplication;
import core4inet.buffer.base.BGQueueBuffer;
import core4inet.incoming.IEEE8021Qbv.IEEE8021QbvIncoming;

//
// This network host combines the inet framework standard host with the core4inet TSN features.
// It enables all features of an inet::StandardHost, replaces the Ethernet NIC with a TSN NIC,
// and supports CoRE4INET BGApps, IEEE802.1QApps and AVBApps. 
//
// @author Timo Haeckel, for HAW Hamburg
//
module TSNIPHost like INetworkNode
{
    parameters:
        // Annotations 
        @display("i=device/pc2");
        @networkNode;
        @labels(node,ethernet-node,wireless-node);

        // CoRE4INET extensions for TSN
        int numApps = default(0); // CoRE4INET apps
        string etherNicType = default("TSNEtherNic");
        // Forwardingdelay of the device hardware
        double hardware_delay @unit(s) = default(0us);
        *.portModule = default("eth"); // rename port module from default "phy" to "eth"
        *.buffers = default("bgOut[0]"); // rename buffers as we have an array now

        // CoRE4INET extensions for TSN overriding INET::StandardHost

        // CoRE4INET extensions for TSN overriding INET::NodeBase
        string networkLayerType = default("RTNetworkLayer");

        // from INET::Standard Host
        int numTcpApps = default(0);  // no of TCP apps. Specify the app types in INI file with tcpApp[0..1].typename="TCPEchoApp" syntax
        int numUdpApps = default(0);  // no of UDP apps. Specify the app types in INI file with udpApp[0..1].typename="UDPVideoStreamCli" syntax
        int numSctpApps = default(0); // no of SCTP apps. Specify the app types in INI file with sctpApp[0..1].typename="SCTPServer" syntax
        int numPingApps = default(0);  // no of PING apps. Specify the app types in INI file with pingApp[0..1].typename="PingApp" syntax
        bool hasTcp = default(numTcpApps > 0);
        bool hasUdp = default(numUdpApps > 0);
        bool hasSctp = default(numSctpApps > 0);
        bool hasTun = default(numTunInterfaces > 0);
        string tcpType = default(firstAvailableOrEmpty("TCP", "TCP_lwIP", "TCP_NSC"));  // tcp implementation (e.g. ~TCP, ~TCP_lwIP, ~TCP_NSC) or ~TCPSpoof
        string udpType = default(firstAvailableOrEmpty("UDP"));
        string sctpType = default(firstAvailableOrEmpty("SCTP"));
        networkLayer.proxyARP = default(false);

        // from INET::StandardHost overwriding INET::NodeBase
        bool forwarding = default(false);  // disable routing by default        

        // from INET::NodeBase
        bool hasStatus = default(false);
        int numExtInterfaces = default(0);
        int numRadios = default(0);               // the number of radios in the router. by default no wireless
        int numPcapRecorders = default(0); // no of PcapRecorders.
        int numTunInterfaces = default(0);
        string osgModel = default(""); // 3D model for OSG visualization, no 3D model by default
        string osgModelColor = default(""); // tint color, no colorization by default
        string mobilityType = default(numRadios > 0 ? "StationaryMobility" : "");
        //        string networkLayerType = default("IPv4NetworkLayer");
        string routingTableType = default("IPv4RoutingTable");
        //        bool forwarding = default(true);
        bool multicastForwarding = default(false);
        string energyStorageType = default("");
        string energyManagementType = default("");
        string energyGeneratorType = default("");
        routingTable.forwarding = forwarding;
        routingTable.multicastForwarding = multicastForwarding;   // for IPv4, IPv6, Generic
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        *.routingTableModule = default(routingTableType != "" ? absPath(".routingTable") : "");
        *.energySourceModule = default(energyStorageType != "" ? absPath(".energyStorage") : "");
        *.mobilityModule = default(mobilityType != "" ? absPath(".mobility") : "");

    gates:
         // from INET::NodeBase
        input radioIn[numRadios] @directIn;
        inout pppg[] @labels(PPPFrame-conn);
        inout ethg[] @labels(EtherFrame-conn);

    submodules:
        // CoRE4INET extensions for TSN
        // CoRE4INET app support (currently only 802.1Q, BG, and AVB Apps!)
        app[numApps]: <> like IApplication {
            @display("p=635,287,row,60");
        }
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=655,40");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=710,40");
        }
        // CORE4INET BGApps
        bgOut[sizeof(ethg)]: BGQueueBuffer {
            @display("p=216,287,c,50");
        }
        // Best-efford buffer for incoming traffic
        bgIn[sizeof(ethg)]: BGQueueBuffer {
            @display("p=149,287,c,50");
        }
        // AVB critical traffic control
        avbCTC: IEEE8021QbvIncoming {
            parameters:
                @display("p=558,287");
                hardware_delay = hardware_delay;
        }
        // Stream Reservation Protocol table
        srpTable: SRPTable {
            @display("p=480,287");
        }
		// Stream Reservation Protocol implementation
        srpProtocol: SRProtocol {
            parameters:
                @display("p=407,287");
        }
        // Adapter to support multiple Ethernet ports in one host with SRP
        srpAdapter: SRPEtherEncapAdapter {
            parameters:
                @display("p=407,342");
            gates:
                encapIn[sizeof(ethg)];
                encapOut[sizeof(ethg)];
        }
        // use the CoRE4INET specific EtherNic for srp and bg gates
        eth[sizeof(ethg)]: <etherNicType> like ICoRE4INETEtherNic {
            parameters:
                @display("p=368,406,row,60;q=txQueue");
        }

        // from INET::StandardHost
        tunApp[numTunInterfaces]: <> like ITunApp {
            parameters:
                @display("p=280,40");
        }
        tcpApp[numTcpApps]: <> like ITCPApp {
            parameters:
                @display("p=147,54,row,60");
        }
        tcp: <tcpType> like ITCP if hasTcp {
            parameters:
                @display("p=147,141");
        }
        udpApp[numUdpApps]: <> like IUDPApp {
            parameters:
                @display("p=329,54,row,60");
        }
        udp: <udpType> like IUDP if hasUdp {
            parameters:
                @display("p=329,141");
        }
        sctpApp[numSctpApps]: <> like ISCTPApp {
            parameters:
                @display("p=527,54,row,60");
        }
        sctp: <sctpType> like ISCTP if hasSctp {
            @display("p=527,141");
        }
        pingApp[numPingApps]: <default("PingApp")> like IPingApp {
            parameters:
                @display("p=635,141,row,60");
        }

         // from INET::NodeBase
        status: NodeStatus if hasStatus {
            @display("p=50,50");
        }
        energyStorage: <energyStorageType> like IEnergyStorage if energyStorageType != "" {
            parameters:
                @display("p=50,100;i=block/plug;is=s");
        }
        energyManagement: <energyManagementType> like IEnergyManagement if energyManagementType != "" {
            parameters:
                @display("p=50,125;i=block/plug;is=s");
        }
        energyGenerator: <energyGeneratorType> like IEnergyGenerator if energyGeneratorType != "" {
            parameters:
                @display("p=50,150;i=block/plug;is=s");
        }
        // optional mobility module. Required only if wireless cards are present
        mobility: <mobilityType> like IMobility if mobilityType != "" {
            parameters:
                @display("p=53,200");
        }
        // network layer
        networkLayer: <networkLayerType> like INetworkLayer {
            parameters:
                @display("p=329,287;q=queue");
        }
        // routing table
        routingTable: <routingTableType> like IRoutingTable if routingTableType != "" {
            parameters:
                @display("p=53,250;is=s");
        }
        // linklayer
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=53,300;is=s");
        }
        pcapRecorder[numPcapRecorders]: PcapRecorder {
            @display("p=53,350,r,10");
        }
        lo0: LoopbackInterface {
            @display("p=78,406");
        }
        wlan[numRadios]: <default("Ieee80211Nic")> like IWirelessNic {
            parameters:
                @display("p=216,406,row,60;q=queue");
        }
        //        eth[sizeof(ethg)]: <default("EthernetInterface")> like IWiredNic {
        //            parameters:
        //                @display("p=368,406,row,60;q=txQueue");
        //        }
        ppp[sizeof(pppg)]: <default("PPPInterface")> like IWiredNic {
            parameters:
                @display("p=558,406,row,60;q=txQueue");
        }
        ext[numExtInterfaces]: <default("ExtInterface")> like IExternalNic {
            parameters:
                @display("p=149,406,row,10;q=txQueue;i=block/ifcard");
        }
        tun[numTunInterfaces]: <default("TunInterface")> like ITunNic {
            parameters:
                @display("p=213,406,row,10;q=txQueue;i=block/ifcard");
        }

    connections allowunconnected:
        // CoRE4INET extensions for TSN
        for i=0..sizeof(ethg)-1 {
            ethg[i] <--> { @display("m=s"); } <--> eth[i].phys;
            eth[i].upperLayerOut --> networkLayer.ifIn++;
            eth[i].upperLayerIn <-- networkLayer.ifOut++;

            bgOut[i].out --> eth[i].bgIn;
            eth[i].bgOut --> bgIn[i].in;

            srpAdapter.encapIn[i] <-- eth[i].srpOut;
            srpAdapter.encapOut[i] --> eth[i].srpIn;
        }
        srpAdapter.srpIn <-- srpProtocol.out;
        srpAdapter.srpOut --> srpProtocol.in;

        // from INET::StandardHost
        for i=0..numTcpApps-1 {
            tcpApp[i].tcpOut --> tcp.appIn++;
            tcpApp[i].tcpIn <-- tcp.appOut++;
        }

        tcp.ipOut --> networkLayer.transportIn++ if hasTcp;
        tcp.ipIn <-- networkLayer.transportOut++ if hasTcp;

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

        for i=0..numTunInterfaces-1 {
            tunApp[i].tunOut --> tun[i].appIn if hasTun;
            tunApp[i].tunIn <-- tun[i].appOut if hasTun;
        }

        // from INET::NodeBase
        // connections to network outside
        networkLayer.ifOut++ --> lo0.upperLayerIn;
        lo0.upperLayerOut --> networkLayer.ifIn++;

        for i=0..sizeof(radioIn)-1 {
            radioIn[i] --> { @display("m=s"); } --> wlan[i].radioIn;
            wlan[i].upperLayerOut --> networkLayer.ifIn++;
            wlan[i].upperLayerIn <-- networkLayer.ifOut++;
        }

        for i=0..sizeof(pppg)-1 {
            pppg[i] <--> { @display("m=s"); } <--> ppp[i].phys;
            ppp[i].upperLayerOut --> networkLayer.ifIn++;
            ppp[i].upperLayerIn <-- networkLayer.ifOut++;
        }

        for i=0..numExtInterfaces-1 {
            ext[i].upperLayerOut --> networkLayer.ifIn++;
            ext[i].upperLayerIn <-- networkLayer.ifOut++;
        }

        for i=0..numTunInterfaces-1 {
            tun[i].upperLayerOut --> networkLayer.ifIn++;
            tun[i].upperLayerIn <-- networkLayer.ifOut++;
        }
}
