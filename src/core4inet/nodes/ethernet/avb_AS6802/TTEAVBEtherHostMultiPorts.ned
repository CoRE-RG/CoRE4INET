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
import core4inet.linklayer.ethernet.avb.SRPEtherEncapAdapter;
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
// @author Philipp Meyer, Michael Malsch
//
module TTEAVBEtherHostMultiPorts
{
    parameters:
        @display("bgb=969.83997,553.3925;i=device/device");
        @networkNode;

        // Number of Applications running on the device
        int numApps = default(0);
        // Optional: Number of Buffers with Incoming Module for TT and RC traffic 
        // (When not manually declared in own deriving .ned file)
        int numBuffer = default(0);
        // Forwardingdelay of the device hardware
        double hardware_delay @unit(s) = default(0us);
        // Promiscuous mode for best-efford traffic handling
        bool be_promiscuous = default(true);
        
        int numPorts = default(1);

        *.interfaceTableModule = default(absPath(".interfaceTable"));

    gates:
        inout ethg[numPorts];

    types:
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
                @display("p=341,193,c,50");
        }

        // AVB class B buffer
        avbBBuffer[numPorts]: AVBQueueBuffer {
            parameters:
                srClass = "B";
                @display("p=419,193,c,50");
        }

		// Stream Reservation Protocol ethernet encapsulation
        encap[numPorts]: SRPEtherEncap {
            parameters:
                @display("p=141,255,c,50");
        }

        adapter: SRPEtherEncapAdapter {
            parameters:
                @display("p=73.73692,173.41832");
            gates:
                encapIn[numPorts];
                encapOut[numPorts];
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
        bgIn[numPorts]: BGQueueBuffer {
            @display("p=60,37,c,50");
        }

		// Best-efford buffer for outgoing traffic
        bgOut[numPorts]: BGQueueBuffer {
            @display("p=109,37,c,50");
        }

		// Stream Reservation Protocol table
        srpTable: SRPTable {
            @display("p=141,99");
        }

		// Stream Reservation Protocol implementation
        // Holds interface names
        interfaceTable: InterfaceTable {
            @display("p=208,99");
        }

        srpProtocol: SRProtocol {
            @display("p=150.76924,173.84616");
        }
    connections allowunconnected:
        for i=0..numPorts-1 {
            phy[i].phys <--> ethg[i];
            encap[i].lowerLayerOut --> phy[i].upperLayerIn;
            phy[i].upperLayerOut --> encap[i].lowerLayerIn;

            encap[i].bgOut --> bgIn[i].in;
            bgOut[i].out --> encap[i].bgIn;

            avbCTC.AVBAout[i] --> avbABuffer[i].in;
            avbCTC.AVBBout[i] --> avbBBuffer[i].in;
            avbABuffer[i].out --> phy[i].AVBAin;
            avbBBuffer[i].out --> phy[i].AVBBin;

            adapter.encapIn[i] <-- encap[i].srpOut;
            adapter.encapOut[i] --> encap[i].srpIn;

        } // new Code

        adapter.srpIn <-- srpProtocol.out;
        adapter.srpOut --> srpProtocol.in;
}
