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

import core4inet.buffer.base.BGQueueBuffer;
import core4inet.linklayer.SRPTrafficHandle;
import core4inet.scheduler.ITTEScheduler;
import core4inet.configuration.base.IConfigurationManager;
import core4inet.linklayer.TTEAVBPHYPort;
import core4inet.synchronisation.base.ISync;
import core4inet.synchronisation.base.DummySync;
import core4inet.applications.base.IApplication;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.buffer.avb.AVBQueueBuffer;
import inet.linklayer.ethernet.EtherLLC;
import inet.applications.ethernet.EtherAppSrv;
import inet.applications.ethernet.EtherAppCli;

//
// Module for a TTEAVBEthernet Host.
// Contains handler for TT, AVB, RC and BE Messages.
//
// @see EtherLLC, TTEAVBPHYPort, Sync, Scheduler
//
// @author Philipp Meyer
module TTEAVBEtherHost
{
    parameters:
        @display("bgb=894,314;i=device/device");
        @node;
        int numApps = default(0); //default(1) ? ListenerApp
        int numBuffer = default(0);
        int numPorts = default(1);
        double hardware_delay @unit(s) = default(0us);

    gates:
        inout ethg;

    submodules:
        phy[numPorts]: TTEAVBPHYPort {
            @display("p=380,255,c,50");
            promiscuous = true;
        }

        avbCTC: AVBIncoming {
            parameters:
                @display("p=380,115");
                NrOfPorts = numPorts;
        }

        avbBuffer[numPorts]: AVBQueueBuffer {
            parameters:
                @display("p=380,193");
        }

        llc: EtherLLC {
            parameters:
                @display("p=141,255");
            gates:
                upperLayerIn[3];
                upperLayerOut[3];
        }

        cli: EtherAppCli {
            parameters:
                registerSAP = true;
                @display("p=60,255,col");
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
            @display("p=186,169");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=274,169");
        }

        app[numApps]: <default("TTEAPITestApplication")> like IApplication {
            @display("p=380,37");
        }

        bgIn: BGQueueBuffer {
            @display("p=60,37");
        }

        bgOut: BGQueueBuffer {
            @display("p=109,37");
        }

        srpIn: BGQueueBuffer {
            @display("p=235,37");
        }

        srpOut: BGQueueBuffer {
            @display("p=235,99");
        }

        srpTrafficHandle: SRPTrafficHandle {
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

        srpTrafficHandle.lowerLayerOut --> llc.upperLayerIn[2];
        srpTrafficHandle.lowerLayerIn <-- llc.upperLayerOut[2];
        srpTrafficHandle.out --> bgIn.in;
        bgOut.out --> srpTrafficHandle.in;
        srpTrafficHandle.SRPout --> srpIn.in;
        srpTrafficHandle.SRPin <-- srpOut.out;

        avbCTC.SRPout --> avbCTC.SRPin;
        avbCTC.AVBout[0] --> avbBuffer[0].in;
        avbBuffer[0].out --> phy[0].AVBin;
}
