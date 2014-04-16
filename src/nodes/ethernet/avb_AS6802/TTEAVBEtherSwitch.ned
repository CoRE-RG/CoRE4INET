package core4inet.nodes.ethernet.avb_AS6802;

import core4inet.scheduler.Scheduler;
import core4inet.scheduler.ITTEScheduler;
import core4inet.configuration.IConfigurationManager;
import core4inet.synchronisation.base.ISync;
import core4inet.synchronisation.base.DummySync;
import core4inet.linklayer.port.TTEAVBPHYPort;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.buffer.avb.AVBQueueBuffer;
import inet.linklayer.ethernet.EtherLLC;
import core4inet.linklayer.beHandling.avb.SRPTrafficHandle;
import core4inet.utilities.modules.CheckedBuffer;

import inet.linklayer.IMACRelayUnit;
import inet.linklayer.IMACAddressTable;

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
        beswitch: <default("MACRelayUnit")> like IMACRelayUnit {
            parameters:
                @display("p=100,50");
            gates:
                ifIn[sizeof(ethg)+1];
                ifOut[sizeof(ethg)+1];
        }
		//The mac table associated with the be switch
        macTable: <default("MACAddressTable")> like IMACAddressTable {
            @display("p=170,50");
        }
        llc: EtherLLC {
            parameters:
                @display("p=170,110");
            gates:
                upperLayerIn[1];
                upperLayerOut[1];
        }

        srpTrafficHandle: SRPTrafficHandle {
            @display("p=170,170");
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
                @display("p=170,240");
                NrOfPorts = sizeof(ethg);
        }

        avbBuffer[sizeof(ethg)]: AVBQueueBuffer {
            @display("p=100,240,c,70");
        }
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=240,50");
        }
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <configurationManagerType> like IConfigurationManager if configurationManagerType != ""{
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
    connections:
        for i=0..sizeof(ethg)-1 {
            avbBuffer[i].out --> phy[i].AVBin;
            avbCTC.AVBout[i] --> avbBuffer[i].in;
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- beswitch.ifOut[i];
            phy[i].upperLayerOut --> beswitch.ifIn[i];
        }
        beswitch.ifOut[sizeof(ethg)] --> llc.lowerLayerIn;
        beswitch.ifIn[sizeof(ethg)] <-- llc.lowerLayerOut;

        srpTrafficHandle.lowerLayerOut --> llc.upperLayerIn[0];
        srpTrafficHandle.lowerLayerIn <-- llc.upperLayerOut[0];
        avbCTC.SRPout --> srpTrafficHandle.SRPin;
        avbCTC.SRPin <-- srpTrafficHandle.SRPout;
        srpTrafficHandle.out --> srpTrafficHandle.in;
//        
//       	llc.upperLayerOut[0] --> avbCTC.SRPin;
//       	llc.upperLayerIn[0] <-- avbCTC.SRPout;

}
