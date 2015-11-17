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

import core4inet.buffer.avb.AVBQueueBuffer;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.linklayer.beHandling.avb.relay.SRPRelay;
import core4inet.linklayer.port.TTEAVBPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;

import inet.linklayer.contract.IMACAddressTable;
import inet.networklayer.common.InterfaceTable;

//
// Module for a TTEAVBEthernet Switch.
// Contains handler for TT, AVB, RC and BE Messages.
//
// @see ~SRPRelay, ~IMACAddressTable, ~InterfaceTable, ~SRPTable, ~TTEAVBPHYPort, ~AVBIncoming, ~AVBQueueBuffer, ~ISync, ~ITTEScheduler, ~CheckedBuffer, ~SRProtocol
//
// @author Philipp Meyer
//
module TTEAVBEtherSwitch
{
    parameters:
        @networkNode();
        @display("i=block/switch;bgb=1280,768");
        
        // Optional: Number of Buffers with Incoming Module for TT and RC traffic 
        // (When not manually declared in own deriving .ned file)
        int numBuffer = default(0);
        // Forwardingdelay of the device hardware
        double hardware_delay @unit(s) = default(8us);
        
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        
    gates:
        // Physical ports of the switch
        inout ethg[] @loose;
        
    types:
        channel ProcessingDelay extends ned.DelayChannel
        {
        }
        
    submodules:
        // Implementation of the best-effort forwarding part
        beswitch: SRPRelay {
            parameters:
                @display("p=141,50");
            gates:
                ifIn[sizeof(ethg)];
                ifOut[sizeof(ethg)];
        }
        
		//The mac table associated with the be switch
        macTable: <default("MACAddressTable")> like IMACAddressTable {
            @display("p=346,313");
        }
        
        // Holds interface names
        interfaceTable: InterfaceTable {
            @display("p=447,313");
        }

        // Stream Reservation Protocol table
        srpTable: SRPTable {
            @display("p=346,238");
        }
        
        // Physical ports of the switch
        phy[sizeof(ethg)]: TTEAVBPHYPort {
            parameters:
                @display("p=90,110,c,130");
                //For the switch it is necessary to have promiscuous mode enabled
                promiscuous = true;
        }

		// AVB critical traffic control
        avbCTC: AVBIncoming {
            parameters:
                @display("p=346,111");
                hardware_delay = hardware_delay;
            gates:
                AVBAout[sizeof(ethg)];
                AVBBout[sizeof(ethg)];
        }

		// AVB class A buffer
        avbABuffer[sizeof(ethg)]: AVBQueueBuffer {
            parameters:
                srClass = "A";
                @display("p=209,80,c,130");
        }

		// AVB class B buffer
        avbBBuffer[sizeof(ethg)]: AVBQueueBuffer {
            parameters:
                srClass = "B";
                @display("p=209,139,c,130");
        }
        
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=416,50");
        }

        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=486,50");
        }
        
        // Buffers with Incoming Module for TT and RC traffic (optional)
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=486,128");
        }
        
        // Stream Reservation Protocol implementation
        srpProtocol: SRProtocol {
            @display("p=346,50");
        }
        
    connections:
        for i=0..sizeof(ethg)-1 {
            avbCTC.AVBAout[i] --> avbABuffer[i].in;
            avbCTC.AVBBout[i] --> avbBBuffer[i].in;
            avbABuffer[i].out --> phy[i].AVBAin;
            avbBBuffer[i].out --> phy[i].AVBBin;

            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- ProcessingDelay{ delay = (hardware_delay/2); } <-- beswitch.ifOut[i];
            phy[i].upperLayerOut --> ProcessingDelay{ delay = (hardware_delay/2); } --> beswitch.ifIn[i];
        }

        srpProtocol.out --> beswitch.srpIn;
        srpProtocol.in <-- beswitch.srpOut;
}
