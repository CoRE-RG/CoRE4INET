package ttethernet.nodes.ethernet;

import ttethernet.scheduler.TTEScheduler;
import ttethernet.configuration.base.IConfigurationManager;
import ttethernet.synchronisation.base.ISync;
import ttethernet.synchronisation.base.DummySync;
import ttethernet.linklayer.TTEAVBPHYPort;
import ttethernet.ctc.AVBIncoming;
import ttethernet.buffer.AVBQueueBuffer;
import inet.linklayer.ethernet.EtherLLC;
import ttethernet.linklayer.SRPTrafficHandle;

import inet.linklayer.IMACRelayUnit;

module TTEAVBEtherSwitch
{
    //Parameter:
    parameters:
        @node();
        @display("i=block/switch;bgb=1280,768");
        double hardware_delay @unit(s) = default(8us);
    gates:
        // Physical ports of the switch
        inout ethg[] @loose;
    submodules:
        // Implementation of the best-effort forwarding part
        beswitch: <default("MACRelayUnitNP")> like IMACRelayUnit {
            parameters:
                @display("p=101,54");
            gates:
                lowerLayerIn[sizeof(ethg)+1];
                lowerLayerOut[sizeof(ethg)+1];
        }

        llc: EtherLLC {
            parameters:
                @display("p=173,54");
            gates:
                upperLayerIn[1];
                upperLayerOut[1];
        }

        srpTrafficHandle: SRPTrafficHandle {
            @display("p=250,54");
        }
        // Physical ports of the switch
        phy[sizeof(ethg)]: TTEAVBPHYPort {
            parameters:
                @display("p=42,126,c,70");
                //For the switch it is necessary to have promiscuous mode enabled
                promiscuous = true;
        }

        avbCTC: AVBIncoming {
            parameters:
                @display("p=328,54");
                NrOfPorts = sizeof(ethg);
        }

        avbBuffer[sizeof(ethg)]: AVBQueueBuffer {
            @display("p=173,126,c,70");
        }
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=422,54");
        }
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <default("BaseConfigurationManager")> like IConfigurationManager {
            parameters:
                @display("p=999,999");
        }
        // Scheudler for the device
        tteScheduler: TTEScheduler {
            parameters:
                @display("p=422,127");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
            avbBuffer[i].out --> phy[i].AVBin;
            avbCTC.AVBout[i] --> avbBuffer[i].in;
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- beswitch.lowerLayerOut[i];
            phy[i].upperLayerOut --> beswitch.lowerLayerIn[i];
        }
        beswitch.lowerLayerOut[sizeof(ethg)] --> llc.lowerLayerIn;
        beswitch.lowerLayerIn[sizeof(ethg)] <-- llc.lowerLayerOut;

        srpTrafficHandle.lowerLayerOut --> llc.upperLayerIn[0];
        srpTrafficHandle.lowerLayerIn <-- llc.upperLayerOut[0];
        avbCTC.SRPout --> srpTrafficHandle.SRPin;
        avbCTC.SRPin <-- srpTrafficHandle.SRPout;
        srpTrafficHandle.out --> srpTrafficHandle.in;
//        
//       	llc.upperLayerOut[0] --> avbCTC.SRPin;
//       	llc.upperLayerIn[0] <-- avbCTC.SRPout;

}
