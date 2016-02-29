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

package core4inet.nodes.ethernet.avb_AS6802;

import core4inet.applications.base.IApplication;
import core4inet.buffer.avb.AVBQueueBuffer;
import core4inet.buffer.base.BGQueueBuffer;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.linklayer.ethernet.avb.SRPEtherEncap;
import core4inet.linklayer.port.TTEAVBPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.synchronisation.base.ISync;

import inet.networklayer.common.InterfaceTable;

//
// Module for a TTEAVBEthernet Host.
// Contains handler for TT, AVB, RC and BE Messages.
//
// @see ~TTEAVBPHYPort, ~AVBIncoming, ~AVBQueueBuffer, ~SRPEtherEncap, ~ISync, ~ITTEScheduler, ~IApplication, ~BGQueueBuffer, ~SRPTable, ~SRProtocol, ~InterfaceTable
//
// @author Philipp Meyer
//
module TTEAVBEtherHost
{
    parameters:
        @display("bgb=894,314;i=device/device");
        @networkNode;
        
        // Number of Applications running on the device
        int numApps = default(0);
        // Optional: Number of Buffers with Incoming Module for TT and RC traffic 
        // (When not manually declared in own deriving .ned file)
        int numBuffer = default(0);
        // Number of Ports of the device
        int numPorts = default(1);
        // Forwardingdelay of the device hardware
        double hardware_delay @unit(s) = default(0us);
        // Promiscuous mode for best-efford traffic handling
        bool be_promiscuous = default(true);
        
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        
    gates:
        inout ethg;

    submodules:
        // Physical port of the host
        phy[numPorts]: TTEAVBPHYPort {
            @display("p=380,255,c,50");
            promiscuous = be_promiscuous;
        }

		// AVB critical traffic control
        avbCTC: AVBIncoming {
            parameters:
                @display("p=380,118");
                hardware_delay = hardware_delay;
            gates:
                AVBAout[numPorts];
                AVBBout[numPorts];
        }

		// AVB class A buffer
        avbABuffer[numPorts]: AVBQueueBuffer {
            parameters:
                srClass = "A";
                @display("p=341,193");
        }

        // AVB class B buffer
        avbBBuffer[numPorts]: AVBQueueBuffer {
            parameters:
                srClass = "B";
                @display("p=419,193");
        }

		// Stream Reservation Protocol ethernet encapsulation
        encap: SRPEtherEncap {
            parameters:
                @display("p=141,255");
        }

        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=208,169");
        }
        
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=274,169");
        }

		// Applications for the device
        app[numApps]: <> like IApplication {
            @display("p=380,37,row,70");
        }

		// Best-efford buffer for incoming traffic 
        bgIn: BGQueueBuffer {
            @display("p=60,37");
        }
        
		// Best-efford buffer for outgoing traffic
        bgOut: BGQueueBuffer {
            @display("p=109,37");
        }
		
		// Stream Reservation Protocol table
        srpTable: SRPTable {
            @display("p=141,99");
        }

		// Stream Reservation Protocol implementation
        srpProtocol: SRProtocol {
            @display("p=141,169");
        }
        
        // Holds interface names
        interfaceTable: InterfaceTable {
            @display("p=208,99");
        }
        
    connections allowunconnected:
        phy[0].phys <--> ethg;
        encap.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> encap.lowerLayerIn;

        encap.bgOut --> bgIn.in;
        bgOut.out --> encap.bgIn;

        avbCTC.AVBAout[0] --> avbABuffer[0].in;
        avbCTC.AVBBout[0] --> avbBBuffer[0].in;
        avbABuffer[0].out --> phy[0].AVBAin;
        avbBBuffer[0].out --> phy[0].AVBBin;

        srpProtocol.out --> encap.srpIn;
        srpProtocol.in <-- encap.srpOut;
}
