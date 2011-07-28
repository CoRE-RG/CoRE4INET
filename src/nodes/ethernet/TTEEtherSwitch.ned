package ttethernet.nodes.ethernet;

import ttethernet.scheduler.TTEScheduler;
import ttethernet.buffer.BufferManager;
import ttethernet.linklayer.Sync;
import ttethernet.linklayer.TTEPHYPort;

import inet.linklayer.IMACRelayUnit;

module TTEEtherSwitch
{
    parameters:
        @node();
        @display("i=block/switch;bgb=276,302");
        string network_configuration;
        string device_name;

        string beRelayUnitType = default("MACRelayUnitNP"); // type of the MACRelayUnit; currently possible MACRelayUnitNP, MACRelayUnitPP
    gates:
        inout ethg[] @loose;
    submodules:
        beswitch: <beRelayUnitType> like IMACRelayUnit {

            @display("p=135,54");
            gates:
                lowerLayerIn[sizeof(ethg)];
                lowerLayerOut[sizeof(ethg)];
        }
        phy[sizeof(ethg)]: TTEPHYPort {
            parameters:
                @display("p=135,216");
        }
        sync: Sync {
            @display("p=45,217");
        }
        bufferManager: BufferManager {
            @display("p=203,121");
        }
        tteScheduler: TTEScheduler {
            @display("p=45,158");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- beswitch.lowerLayerOut[i];
            phy[i].upperLayerOut --> beswitch.lowerLayerIn[i];

        }
}

