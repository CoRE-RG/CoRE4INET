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

package ttethernet.nodes.ethernet;

import ttethernet.buffer.BGQueueBuffer;
import ttethernet.linklayer.BGTrafficHandle;
import ttethernet.scheduler.TTEScheduler;
import ttethernet.configuration.base.IConfigurationManager;
import ttethernet.linklayer.TTEAVBPHYPort;
import ttethernet.synchronisation.base.ISync;
import ttethernet.synchronisation.base.DummySync;
import ttethernet.applications.base.ITTEApplication;
import ttethernet.buffer.AVBQueueBuffer;
import inet.linklayer.ethernet.EtherLLC;
import inet.applications.ethernet.EtherAppSrv;
import inet.applications.ethernet.EtherAppCli;

module TTEAVBEtherHost
{
    parameters:
        @display("bgb=894,314;i=device/device");
        int numApps = default(0); //default(1) ? ListenerApp
        int numPorts = default(1);
        double hardware_delay @unit(s) = default(0us);

    gates:
        inout ethg;

    submodules:
        phy[numPorts]: TTEAVBPHYPort {
            @display("p=235,255,c,50");
        }

        avbBuffer[numPorts]: AVBQueueBuffer {
            parameters:
                @display("p=390,169");
        }

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
        // Scheudler for the device
        tteScheduler: TTEScheduler {
            @display("p=235,169");
        }
        tteApp[numApps]: <default("TTEAPITestApplication")> like ITTEApplication {
            @display("p=235,99");
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
        
        for i=0..numPorts-1 {
            avbBuffer[i].out --> phy[i].AVBin;
        }
}
