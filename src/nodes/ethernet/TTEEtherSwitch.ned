package ttethernet.nodes.ethernet;

import ttethernet.scheduler.TTEScheduler;
import ttethernet.buffer.BufferManager;
import ttethernet.synchronisation.Sync;
import ttethernet.linklayer.TTEPHYPort;

import inet.linklayer.IMACRelayUnit;

//
// Module for a TTEthernet Switch with variable number of ports.
// Contains a configurable best-effort implementation (beRelayUnitType like IMACRelayUnit),
// TTEPHYPort modules for physical ports, sync module (Sync) and a TTEScheduler module.
// The switch is configured by the provided TTEthernet XML network configuration
// (network_configuration parameter) and uses the device_name parameter to find its config.
// The configuration is done by the BufferManager that deletes itself at runtime.
//
// @see IMacRelayUnit, TTEPHYPort, Sync, TTEScheduler, BufferManager
//
// @author Till Steinbach
module TTEEtherSwitch
{
    parameters:
        @node();
        @display("i=block/switch;bgb=666,302");
        // Network configuration file
        string network_configuration;
        // Name of the device in the network configuration
        string device_name;
        // type of the best-effort MACRelayUnit; currently possible MACRelayUnitNP, MACRelayUnitPP
        string beRelayUnitType = default("MACRelayUnitNP"); 
    gates:
        // Physical ports of the switch
        inout ethg[] @loose;
    submodules:
        // Implementation of the best-effort forwarding part
        beswitch: <beRelayUnitType> like IMACRelayUnit {
            parameters:
                @display("p=135,54");
            gates:
                lowerLayerIn[sizeof(ethg)];
                lowerLayerOut[sizeof(ethg)];
        }
        // Physical ports of the switch
        phy[sizeof(ethg)]: TTEPHYPort {
            parameters:
                @display("p=135,216");
        }
        // Sync module for synchronisation of the scheduler
        sync: Sync {
            parameters:
                @display("p=45,217");
        }
        // Buffer manager that creates the buffers according to the configuration
        bufferManager: BufferManager {
            parameters:
                @display("p=203,121");
        }
        // Scheudler for the device
        tteScheduler: TTEScheduler {
            parameters:
                @display("p=45,158");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
                phy[i].phys <--> ethg[i];
                phy[i].upperLayerIn <-- beswitch.lowerLayerOut[i];
                phy[i].upperLayerOut --> beswitch.lowerLayerIn[i];
        }
}

