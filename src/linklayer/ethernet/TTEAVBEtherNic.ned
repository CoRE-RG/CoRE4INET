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

package core4inet.linklayer.ethernet;

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

import inet.linklayer.INic;


//
// Module for a TTE AVB BE Ethernet NIC
// Contains handler for TT, AVB, RC and BE Messages.
//
// @see SRPEtherEncap, TTEAVBPHYPort, Sync, Scheduler
//
// @author Kai-Uwe von Deylen
module TTEAVBEtherNic like INic
{
    parameters:
        @display("bgb=577,314;i=block/ifcard");
        int numApps = default(0); //default(1) ? ListenerApp
        int numBuffer = default(0);
        int numPorts = default(1);
        double hardware_delay @unit(s) = default(0us);
        string configurationManagerType = default("");
    gates:
        inout ethg;
        input upperLayerIn;
        output upperLayerOut;

    submodules:
        phy[numPorts]: TTEAVBPHYPort {
            @display("p=254,235,c,50");
            promiscuous = true;
        }

        avbCTC: AVBIncoming {
            parameters:
                @display("p=487,236");
            gates:
                AVBout[numPorts];
        }

        avbBuffer[numPorts]: AVBQueueBuffer {
            parameters:
                @display("p=355,236");
        }

        encap: SRPEtherEncap {
            parameters:
                @display("p=254,118");
        }

        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <configurationManagerType> like IConfigurationManager if configurationManagerType != "" {
            @display("p=87,265");
        }
         // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=87,118");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=87,194");
        }

        app[numApps]: <> like IApplication {
            @display("p=355,40,row,70");
        }

        bgIn: BGQueueBuffer {
            @display("p=355,118");
        }

        bgOut: BGQueueBuffer {
            @display("p=355,177");
        }

        srpTable: SRPTable {
            @display("p=87,42");
        }

        srpProtocol: SRProtocol {
            @display("p=161,118");
        }

    connections allowunconnected:
        phy[0].phys <--> ethg;
        encap.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> encap.lowerLayerIn;

        encap.bgOut --> bgIn.in;
        bgOut.out --> encap.bgIn;

        avbCTC.AVBout[0] --> avbBuffer[0].in;
        avbBuffer[0].out --> phy[0].AVBin;

        srpProtocol.out --> encap.srpIn;
        srpProtocol.in <-- encap.srpOut;

        encap.upperLayerOut --> upperLayerOut;
        upperLayerIn --> encap.upperLayerIn;
}
