package core4inet.nodes.ethernet.avb_AS6802;

import core4inet.buffer.avb.AVBQueueBuffer;
import core4inet.configuration.IConfigurationManager;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.linklayer.beHandling.avb.relay.SRPRelay;
import core4inet.linklayer.port.TTEAVBPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;
import inet.base.NotificationBoard;
import inet.linklayer.IMACAddressTable;
import inet.networklayer.common.InterfaceTable;


//
// Module for a TTEAVBEthernet Switch.
// Contains handler for TT, AVB, RC and BE Messages.
//
// @see IMacRelayUnit, TTEAVBPHYPort, Sync, Scheduler
//
// @author Philipp Meyer
module TTEAVBEtherSwitch
{
    //Parameter:
    parameters:
        @node();
        @display("i=block/switch;bgb=1280,768");
        double hardware_delay @unit(s) = default(8us);
        int numBuffer = default(0);
        string configurationManagerType = default("");
    gates:
        // Physical ports of the switch
        inout ethg[] @loose;
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
        interfaceTable: InterfaceTable {
            @display("p=447,313");
        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=552,313");
        }

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

        avbCTC: AVBIncoming {
            parameters:
                @display("p=346,111");
                hardware_delay = hardware_delay;
            gates:
                AVBAout[sizeof(ethg)];
                AVBBout[sizeof(ethg)];
        }

        avbABuffer[sizeof(ethg)]: AVBQueueBuffer {
            parameters:
                srClass = "A";
                @display("p=209,80,c,130");
        }

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
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <configurationManagerType> like IConfigurationManager if configurationManagerType != "" {
            parameters:
                @display("p=1039,999");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=486,50");
        }
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=486,128");
        }
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
            phy[i].upperLayerIn <-- beswitch.ifOut[i];
            phy[i].upperLayerOut --> beswitch.ifIn[i];
        }

        srpProtocol.out --> beswitch.srpIn;
        srpProtocol.in <-- beswitch.srpOut;

}
