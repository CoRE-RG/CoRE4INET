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
                @display("p=100,50");
            gates:
                ifIn[sizeof(ethg)];
                ifOut[sizeof(ethg)];
        }
		//The mac table associated with the be switch
        macTable: <default("MACAddressTable")> like IMACAddressTable {
            @display("p=170,276");
        }
        interfaceTable: InterfaceTable {
            @display("p=304,276");
        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=376,276");
        }

        srpTable: SRPTable {
            @display("p=235,276");
        }
        // Physical ports of the switch
        phy[sizeof(ethg)]: TTEAVBPHYPort {
            parameters:
                @display("p=50,110,column,50");
                //For the switch it is necessary to have promiscuous mode enabled
                promiscuous = true;
        }

        avbCTC: AVBIncoming {
            parameters:
                @display("p=170,111");
            gates:
               AVBout[sizeof(ethg)];
        }

        avbBuffer[sizeof(ethg)]: AVBQueueBuffer {
            @display("p=100,111,c,70");
        }
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=240,50");
        }
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <configurationManagerType> like IConfigurationManager if configurationManagerType != "" {
            parameters:
                @display("p=999,999");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=310,50");
        }
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=310,130");
        }
        srpProtocol: SRProtocol {
            @display("p=170,50");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
            avbBuffer[i].out --> phy[i].AVBin;
            avbCTC.AVBout[i] --> avbBuffer[i].in;
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- beswitch.ifOut[i];
            phy[i].upperLayerOut --> beswitch.ifIn[i];
        }

        srpProtocol.out --> beswitch.srpIn;
        srpProtocol.in <-- beswitch.srpOut;

}
