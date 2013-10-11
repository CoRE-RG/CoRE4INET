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
package ttethernet.nodes.ethernet.AS6802;

import ttethernet.buffer.base.BGQueueBuffer;
import ttethernet.linklayer.BGTrafficHandle;
import ttethernet.scheduler.ITTEScheduler;
import ttethernet.scheduler.TTEScheduler;
import ttethernet.scheduler.Scheduler;
import ttethernet.configuration.base.IConfigurationManager;
import ttethernet.linklayer.TTEPHYPort;
import ttethernet.synchronisation.base.ISync;
import ttethernet.synchronisation.base.DummySync;
import ttethernet.applications.base.IApplication;
import inet.linklayer.ethernet.EtherLLC;
import inet.applications.ethernet.EtherAppSrv;
import inet.applications.ethernet.EtherAppCli;

//
// Module for a TTEthernet Host.
// Contains a EtherLLC for best-effort traffic, a TTEPHYPort module as physical port,
// sync module (Sync) and a TTEScheduler module.
// The Host is configured by the provided TTEthernet XML network configuration
// (network_configuration parameter) and uses the device_name parameter to find its config.
// The configuration is done by the BufferManager that deletes itself at runtime.
//
// @todo Ports for redundancy!
// @todo Documentation for Applications!
//
// @see EtherLLC, TTEPHYPort, Sync, TTEScheduler, BufferManager
//
// @author Till Steinbach
module TTEEtherHost
{
    parameters:
        @display("bgb=894,314;i=device/device");
        @node;
        @labels(node,ethernet-node);
        int numApps = default(0);
        int numPorts = default(1);
        double hardware_delay @unit(s) = default(0us);
    gates:
        // Physical port of the host
        inout ethg @labels(EtherFrame-conn);

    submodules:
        // Physical port of the host
        phy[numPorts]: TTEPHYPort {
            @display("p=235,255,c,50");
        }
        // LLC for best-effort traffic
        llc: EtherLLC {
            parameters:
                @display("p=141,256");
            gates:
                upperLayerIn[3];
                upperLayerOut[3];
        }

        cli: EtherAppCli {
            parameters:
                registerSAP = true;
                @display("p=60,256,col");
        }
        srv: EtherAppSrv {
            parameters:
                registerSAP = true;
                @display("p=60,169,col");
        }
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <default("BaseConfigurationManager")> like IConfigurationManager {
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
        app[numApps]: <default("TTEAPITestApplication")> like IApplication {
            @display("p=234,37,row,70");
        }
        bgIn: BGQueueBuffer {
            @display("p=141,37");
        }
        bgOut: BGQueueBuffer {
            @display("p=141,99");
        }
        bgTrafficHandle: BGTrafficHandle {
            @display("p=60,99");
        }
    connections:
        phy[0].phys <--> ethg;
        llc.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> llc.lowerLayerIn;

        cli.out --> llc.upperLayerIn[0];
        cli.in <-- llc.upperLayerOut[0];

        srv.out --> llc.upperLayerIn[1];
        srv.in <-- llc.upperLayerOut[1];

        bgTrafficHandle.lowerLayerOut --> llc.upperLayerIn[2];
        bgTrafficHandle.lowerLayerIn <-- llc.upperLayerOut[2];
        bgTrafficHandle.out --> bgIn.in;
        bgOut.out --> bgTrafficHandle.in;
}

