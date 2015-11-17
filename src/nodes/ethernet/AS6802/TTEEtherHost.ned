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

import core4inet.applications.base.IApplication;
import core4inet.buffer.base.BGQueueBuffer;
import core4inet.linklayer.port.TTEPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;
import core4inet.linklayer.ethernet.base.BGEtherEncap;

import inet.common.lifecycle.NodeStatus;
import inet.networklayer.common.InterfaceTable;

//
// Module for a TTEthernet Host.
// Contains a BGEtherEncap for best-effort traffic, a TTEPHYPort module as physical port,
// sync module (Sync) and a TTEScheduler module.
//
// @see ~NodeStatus, ~TTEPHYPort, ~BGEtherEncap, ~IConfigurationManager, ~ISync, ~ITTEScheduler, ~IApplication, ~BGQueueBuffer, ~CheckedBuffer, ~InterfaceTable
//
// @author Till Steinbach
//
module TTEEtherHost
{
    parameters:
        @display("bgb=894,314;i=device/device");
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
            @display("p=60,37;is=n");
        }
        
        // Physical port of the host
        phy[numPorts]: TTEPHYPort {
            @display("p=235,255,c,50");
        }
        
        // Encap for best-effort traffic
        encap: BGEtherEncap {
            parameters:
                @display("p=141,256");
        }

         // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=141,169");
        }
        
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=235,169");
        }
        
        // Applications for the device
        app[numApps]: < > like IApplication {
            @display("p=234,37,row,70");
        }
        
        // Best-efford buffer for incoming traffic 
        bgIn: BGQueueBuffer {
            @display("p=141,37");
        }
        
        // Best-efford buffer for outgoing traffic 
        bgOut: BGQueueBuffer {
            @display("p=141,99");
        }
        
        // Buffers with Incoming Module for TT and RC traffic (optional)
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=350,100");
        }
        
        // Holds interface names
        interfaceTable: InterfaceTable {
            @display("p=234,100");
        }
        
    connections allowunconnected:
        phy[0].phys <--> ethg;
        encap.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> encap.lowerLayerIn;

        encap.bgOut --> bgIn.in;
        bgOut.out --> encap.bgIn;
}

