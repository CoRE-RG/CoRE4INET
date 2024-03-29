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

package core4inet.nodes.ethernet.AS6802;

import core4inet.linklayer.port.TTEPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;

import inet.linklayer.contract.IMACAddressTable;
import inet.linklayer.contract.IMACRelayUnit;
import inet.common.lifecycle.NodeStatus;
import inet.networklayer.common.InterfaceTable;

//
// Module for a TTEthernet Switch with variable number of ports.
// Contains a configurable best-effort implementation (beswitch like IMACRelayUnit),
// TTEPHYPort modules for physical ports, sync module (Sync) and a TTEScheduler module.
//
// @see ~NodeStatus, ~IMACRelayUnit, ~IMACAddressTable, ~InterfaceTable, ~TTEPHYPort, ~ISync, ~ITTEScheduler, ~CheckedBuffer
//
// @author Till Steinbach
//
module TTEEtherSwitch
{
    parameters:
        @display("i=block/switch;bgb=514,312");
        @networkNode;
        @labels(node,ethernet-node);
        
        // Optional: Number of Buffers with Incoming Module for TT and RC traffic 
        // (When not manually declared in own deriving .ned file)
        int numBuffer = default(0);
        // Forwardingdelay of the device hardware
        double hardware_delay @unit(s) = default(8us);
      
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        
    gates:
        // Physical ports of the switch
        inout ethg[] @loose @labels(EtherFrame-conn);
        
    types:
        channel ProcessingDelay extends ned.DelayChannel
        {
        }
        
    submodules:
        // Keeps track of the status of network node (up, down, etc.)
        status: NodeStatus {
            @display("p=47,50;is=n");
        }
        
        // Implementation of the best-effort forwarding part
        beswitch: <default("MACRelayUnit")> like IMACRelayUnit {
            parameters:
                @display("p=100,50");
            gates:
                ifIn[sizeof(parent.ethg)];
                ifOut[sizeof(parent.ethg)];
        }
        
        //The mac table associated with the be switch
        macTable: <default("MACAddressTable")> like IMACAddressTable {
            @display("p=170,50");
        }
        
        // Holds interface names
        interfaceTable: InterfaceTable {
            @display("p=447,313");
        }
        
        // Physical ports of the switch
        phy[sizeof(ethg)]: TTEPHYPort {
            parameters:
                @display("p=50,100,column,50");
                //For the switch it is necessary to have promiscuous mode enabled
                promiscuous = true;
        }
        
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=240,50");
        }

        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=310,50");
        }
        
        // Buffers with Incoming Module for TT and RC traffic (optional)
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=170,130");
        }
        
    connections:
        for i=0..sizeof(ethg)-1 {
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- ProcessingDelay{ delay = (parent.hardware_delay/2); } <-- beswitch.ifOut[i];
            phy[i].upperLayerOut --> ProcessingDelay{ delay = (parent.hardware_delay/2); } --> beswitch.ifIn[i];
        }
}

