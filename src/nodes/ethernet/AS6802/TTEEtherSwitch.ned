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
package ttethernet.nodes.ethernet.AS6802;

import ttethernet.scheduler.ITTEScheduler;
import ttethernet.scheduler.TTEScheduler;
import ttethernet.configuration.base.IConfigurationManager;
import ttethernet.synchronisation.base.ISync;
import ttethernet.synchronisation.base.DummySync;
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
        @display("i=block/switch;bgb=514,312");
        @node;
        @labels(node,ethernet-node);
        double hardware_delay @unit(s) = default(8us);
    gates:
        // Physical ports of the switch
        inout ethg[] @loose @labels(EtherFrame-conn);
    submodules:
        // Implementation of the best-effort forwarding part
        beswitch: <default("MACRelayUnitNP")> like IMACRelayUnit {
            parameters:
                @display("p=100,50");
            gates:
                ifIn[sizeof(ethg)];
                ifOut[sizeof(ethg)];
        }
        // Physical ports of the switch
        phy[sizeof(ethg)]: TTEPHYPort {
            parameters:
                @display("p=50,100,column,50");
                //For the switch it is necessary to have promiscuous mode enabled
                promiscuous = true;
        }
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=170,50");
        }
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <default("BaseConfigurationManager")> like IConfigurationManager {
            parameters:
                @display("p=999,999");
        }
        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=240,50");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- beswitch.ifOut[i];
            phy[i].upperLayerOut --> beswitch.ifIn[i];
        }
}

