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
import core4inet.configuration.IConfigurationManager;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.linklayer.ethernet.avb.SRPEtherEncap;
import core4inet.linklayer.port.TTEAVBPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.synchronisation.base.ISync;


//
// Module for a TTEAVBEthernet Host.
// Contains handler for TT, AVB, RC and BE Messages.
//
// @see SRPEtherEncap, TTEAVBPHYPort, Sync, Scheduler
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
        string configurationManagerType = default("");
        bool be_promiscuous = default(true);
    gates:
        inout ethg;

    submodules:
        phy[numPorts]: TTEAVBPHYPort {
            @display("p=380,255,c,50");
            promiscuous = be_promiscuous;
        }

        avbCTC: AVBIncoming {
            parameters:
                @display("p=380,118");
                hardware_delay = hardware_delay;
            gates:
                AVBAout[numPorts];
                AVBBout[numPorts];
        }

        avbABuffer[numPorts]: AVBQueueBuffer {
            parameters:
                srClass = "A";
                @display("p=341,193");
        }

        avbBBuffer[numPorts]: AVBQueueBuffer {
            parameters:
                srClass = "B";
                @display("p=419,193");
        }

        encap: SRPEtherEncap {
            parameters:
                @display("p=141,255");
        }

        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <configurationManagerType> like IConfigurationManager if configurationManagerType != "" {
            @display("p=999,999");
        }
         // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=208,169");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=274,169");
        }

        app[numApps]: <> like IApplication {
            @display("p=380,37,row,70");
        }

        bgIn: BGQueueBuffer {
            @display("p=60,37");
        }

        bgOut: BGQueueBuffer {
            @display("p=109,37");
        }

        srpTable: SRPTable {
            @display("p=141,99");
        }

        srpProtocol: SRProtocol {
            @display("p=141,169");
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
