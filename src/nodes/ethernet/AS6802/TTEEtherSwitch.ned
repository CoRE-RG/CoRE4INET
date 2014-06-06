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
package core4inet.nodes.ethernet.AS6802;

import core4inet.configuration.IConfigurationManager;
import core4inet.linklayer.port.TTEPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;
import inet.linklayer.IMACAddressTable;
import inet.linklayer.IMACRelayUnit;
import inet.status.NodeStatus;

//
// Module for a TTEthernet Switch with variable number of ports.
// Contains a configurable best-effort implementation (beRelayUnitType like IMACRelayUnit),
// TTEPHYPort modules for physical ports, sync module (Sync) and a TTEScheduler module.
// The switch is configured by the provided TTEthernet XML network configuration
// (network_configuration parameter) and uses the device_name parameter to find its config.
// The configuration is done by the BufferManager that deletes itself at runtime.
//
// @see IMacRelayUnit, TTEPHYPort, Sync, Scheduler, BufferManager
//
// @author Till Steinbach
module TTEEtherSwitch
{
    parameters:
        @display("i=block/switch;bgb=514,312");
        @node;
        @labels(node,ethernet-node);
        double hardware_delay @unit(s) = default(8us);
        int numBuffer = default(0);
        string configurationManagerType = default("");
    gates:
        // Physical ports of the switch
        inout ethg[] @loose @labels(EtherFrame-conn);
    submodules:
        status: NodeStatus {
            @display("p=47,50;is=n");
        }
        // Implementation of the best-effort forwarding part
        beswitch: <default("MACRelayUnit")> like IMACRelayUnit {
            parameters:
                @display("p=100,50");
            gates:
                ifIn[sizeof(ethg)];
                ifOut[sizeof(ethg)];
        }
        //The mac table associated with the be switch
        macTable: <default("MACAddressTable")> like IMACAddressTable {
            @display("p=170,50");
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
            @display("p=170,130");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- beswitch.ifOut[i];
            phy[i].upperLayerOut --> beswitch.ifIn[i];
        }
}

