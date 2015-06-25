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
package core4inet.nodes.ethernet.IEEE8021Q;

import core4inet.applications.base.IApplication;
import core4inet.buffer.base.BGQueueBuffer;
import core4inet.configuration.IConfigurationManager;
import core4inet.linklayer.port.IEEE8021QPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;
import core4inet.linklayer.ethernet.base.BGEtherEncap;
import inet.status.NodeStatus;


//
// Module for a IEEE 802.1Q Host.
// Contains a EtherEncap for best-effort traffic and a IEEE8021QPHYPort module as physical port.
//
// @todo Ports for redundancy!
// @todo Documentation for Applications!
//
// @see EtherEncap, IEEE8021QPHYPort, Sync, Scheduler, BufferManager
//
// @author Till Steinbach
// @author Philipp Meyer
//
module IEEE8021QEtherHost
{
    parameters:
        @display("bgb=894,314;i=device/device");
        @node;
        @labels(node,ethernet-node);
        int numApps = default(0);
        int numBuffer = default(0);
        int numPorts = default(1);
        double hardware_delay @unit(s) = default(0us);
        string configurationManagerType = default("");
    gates:
        // Physical port of the host
        inout ethg @loose @labels(EtherFrame-conn);

    submodules:
        status: NodeStatus {
            @display("p=60,37;is=n");
        }
        // Physical port of the host
        phy[numPorts]: IEEE8021QPHYPort {
            @display("p=235,255,c,50");
        }
        // Encap for best-effort traffic
        encap: BGEtherEncap {
            parameters:
                @display("p=141,256");
        }

        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <configurationManagerType> like IConfigurationManager if configurationManagerType != "" {
            @display("p=999,999");
        }
         // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=141,169");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=235,169");
        }
        app[numApps]: < > like IApplication {
            @display("p=234,37,row,70");
        }
        bgIn: BGQueueBuffer {
            @display("p=141,37");
        }
        bgOut: BGQueueBuffer {
            @display("p=141,99");
        }
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=350,100");
        }
    connections allowunconnected:
        phy[0].phys <--> ethg;
        encap.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> encap.lowerLayerIn;

        encap.bgOut --> bgIn.in;
        bgOut.out --> encap.bgIn;
}

