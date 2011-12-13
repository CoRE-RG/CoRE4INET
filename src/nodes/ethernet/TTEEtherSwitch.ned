package ttethernet.nodes.ethernet;

import ttethernet.scheduler.TTEScheduler;
import ttethernet.configuration.IConfigurationManager;
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
        @display("i=block/switch;bgb=1219,312");
        // type of the best-effort MACRelayUnit; currently possible MACRelayUnitNP, MACRelayUnitPP
        string beRelayUnitType = default("MACRelayUnitNP");
        // type of the configurationManager this package contains a dummy ConfigurationManager (BaseConfigurationManager) that can be extended
        string configurationManager = default("BaseConfigurationManager");
    gates:
        // Physical ports of the switch
        inout ethg[] @loose;
    submodules:
        // Implementation of the best-effort forwarding part
        beswitch: <beRelayUnitType> like IMACRelayUnit {
            parameters:
                @display("p=141,242");
            gates:
                lowerLayerIn[sizeof(ethg)];
                lowerLayerOut[sizeof(ethg)];
        }
        // Physical ports of the switch
        phy[sizeof(ethg)]: TTEPHYPort {
            parameters:
                @display("p=235,278,r,50");
        }
        // Sync module for synchronisation of the scheduler
        sync: Sync {
            parameters:
                @display("p=141,169");
        }
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <configurationManager> like IConfigurationManager {
            parameters:
                @display("p=999,999");
        }
        // Scheudler for the device
        tteScheduler: TTEScheduler {
            parameters:
                @display("p=235,169");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- beswitch.lowerLayerOut[i];
            phy[i].upperLayerOut --> beswitch.lowerLayerIn[i];
        }
}

