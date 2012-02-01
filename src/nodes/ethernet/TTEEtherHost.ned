package ttethernet.nodes.ethernet;

import ttethernet.buffer.BGQueueBuffer;
import ttethernet.linklayer.BGTrafficHandle;
import ttethernet.applications.TTEAPITestApplication;
import ttethernet.scheduler.TTEScheduler;
import ttethernet.configuration.IConfigurationManager;
import ttethernet.api.TTEthAPI;
import ttethernet.linklayer.TTEPHYPort;
import ttethernet.synchronisation.ISync;
import ttethernet.synchronisation.DummySync;
import ttethernet.applications.ITTEApplication;
import inet.linklayer.ethernet.EtherLLC;
import inet.applications.ethernet.EtherAppSrv;
import inet.applications.ethernet.EtherAppCli;

//
// Module for a TTEthernet Host.
// Contains a EtherLLC for best-effort traffic, a TTEPHYPort module as physical port,
// sync module (Sync) and a TTEScheduler module.
// The Host is configured by the provided TTEthernet XML network configuration
// (network_configuration parameter) and uses the device_name parameter to find its config.
// The configuration is done by the BufferManager that deletes itself at runtime.
//
// @todo Ports for redundancy!
// @todo Documentation for Applications!
//
// @see EtherLLC, TTEPHYPort, Sync, TTEScheduler, BufferManager
//
// @author Till Steinbach
module TTEEtherHost
{
    parameters:
        @display("bgb=894,314;i=device/device");
        int numApps = default(0);
        int numPorts = default(1);
        double hardware_delay @unit(s) = default(0us);
    gates:
        // Physical port of the host
        inout ethg;

    submodules:
        // Physical port of the host
        phy[numPorts]: TTEPHYPort {
            @display("p=235,255,c,50");
        }
        // LLC for best-effort traffic
        llc: EtherLLC {
            parameters:
                @display("p=141,256");
            gates:
                upperLayerIn[3];
                upperLayerOut[3];
        }

        cli: EtherAppCli {
            parameters:
                registerSAP = true;
                @display("p=60,256,col");
        }
        srv: EtherAppSrv {
            parameters:
                registerSAP = true;
                @display("p=60,169,col");
        }
        // Buffer manager that creates the buffers according to the configuration
        configurationManager: <default("BaseConfigurationManager")> like IConfigurationManager {
            @display("p=999,999");
        }
         // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            @display("p=141,169");
        }
        // Scheudler for the device
        tteScheduler: TTEScheduler {
            @display("p=235,169");
        }
        tteApp[numApps]: <default("TTEAPITestApplication")> like ITTEApplication {
            @display("p=235,99");
        }
        bgIn: BGQueueBuffer {
            @display("p=141,37");
        }
        bgOut: BGQueueBuffer {
            @display("p=141,99");
        }
        bgTrafficHandle: BGTrafficHandle {
            @display("p=60,99");
        }
    connections:
        phy[0].phys <--> ethg;
        llc.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> llc.lowerLayerIn;

        cli.out --> llc.upperLayerIn[0];
        cli.in <-- llc.upperLayerOut[0];

        srv.out --> llc.upperLayerIn[1];
        srv.in <-- llc.upperLayerOut[1];

        bgTrafficHandle.lowerLayerOut --> llc.upperLayerIn[2];
        bgTrafficHandle.lowerLayerIn <-- llc.upperLayerOut[2];
        bgTrafficHandle.out --> bgIn.in;
        bgOut.out --> bgTrafficHandle.in;
}

