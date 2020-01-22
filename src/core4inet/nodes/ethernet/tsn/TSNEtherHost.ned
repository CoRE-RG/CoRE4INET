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

package core4inet.nodes.ethernet.tsn;

import core4inet.applications.base.IApplication;
import core4inet.buffer.base.BGQueueBuffer;
import core4inet.linklayer.port.TSNPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;
import core4inet.linklayer.ethernet.base.BGEtherEncap;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.linklayer.ethernet.avb.SRPEtherEncap;
import core4inet.incoming.IEEE8021Qbv.IEEE8021QbvIncoming;

import inet.common.lifecycle.NodeStatus;
import inet.networklayer.common.InterfaceTable;

//
// Module for a TSN Host.
// Contains a EtherEncap for best-effort traffic and a TSNPHYPort module as physical port.
//
// @see ~NodeStatus, ~IEEE8021QbvPHYPort, ~BGEtherEncap, ~ISync, ~ITTEScheduler, ~IApplication, ~BGQueueBuffer, ~CheckedBuffer, ~InterfaceTable, ~SRPEtherEncap, ~SRPTable, ~SRProtocol
//
// @author Philipp Meyer
//
module TSNEtherHost
{
    parameters:
        @display("bgb=,;i=device/device");
        @networkNode;
        @labels(node,ethernet-node);
        // Number of Applications running on the device
        int numApps = default(0);
        // Optional: Number of Buffers with Incoming Module for TT and RC traffic 
        // (When not manually declared in own deriving .ned file)
        int numBuffer = default(0);
        // Number of Ports of the device
        int numPorts = default(1);
        // Forwardingdelay of the device hardware
        double hardware_delay @unit(s) = default(0us);
        *.interfaceTableModule = default(absPath(".interfaceTable"));

    gates:
        // Physical port of the host
        inout ethg @loose @labels(EtherFrame-conn);

    submodules:
        // Keeps track of the status of network node (up, down, etc.)
        status: NodeStatus {
            @display("p=100,50;is=n");
        }

        // Physical port of the host
        phy[numPorts]: TSNPHYPort {
            @display("p=100,450,c,50");
        }

        // AVB critical traffic control
        avbCTC: IEEE8021QbvIncoming {
            parameters:
                @display("p=500,250");
                hardware_delay = hardware_delay;
        }

        // Encap for best-effort traffic
        encap: SRPEtherEncap {
            parameters:
                @display("p=100,350");
        }

         // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=300,50");
        }

        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=200,50");
        }

        // Applications for the device
        app[numApps]: <> like IApplication {
            @display("p=400,50,row,100");
        }

        // Best-efford buffer for incoming traffic
        bgIn: BGQueueBuffer {
            @display("p=100,150");
        }

        // Best-efford buffer for outgoing traffic
        bgOut: BGQueueBuffer {
            @display("p=200,150");
        }

        // Buffers with Incoming Module for TT and RC traffic (optional)
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=600,150");
        }

        // Holds interface names
        interfaceTable: InterfaceTable {
            @display("p=200,250");
        }

        // Stream Reservation Protocol table
        srpTable: SRPTable {
            @display("p=400,250");
        }

		// Stream Reservation Protocol implementation
        srpProtocol: SRProtocol {
            @display("p=300,250");
        }

    connections allowunconnected:
        phy[0].phys <--> ethg;
        encap.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> encap.lowerLayerIn;

        encap.bgOut --> bgIn.in;
        bgOut.out --> encap.bgIn;

        srpProtocol.out --> encap.srpIn;
        srpProtocol.in <-- encap.srpOut;
}

