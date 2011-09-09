package ttethernet.nodes.ethernet;

import ttethernet.buffer.BGQueueBuffer;
import ttethernet.linklayer.BGTrafficHandle;
import ttethernet.applications.TTEAPITestApplication;
import ttethernet.scheduler.TTEScheduler;
import ttethernet.buffer.BufferManager;
import ttethernet.api.TTEthAPI;
import ttethernet.linklayer.TTEPHYPort;
import ttethernet.synchronisation.Sync;
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
        @display("bgb=596,314;i=device/device");
        // Network configuration file
        string network_configuration;
        // Name of the device in the network configuration
        string device_name;
        //Application running on the Host
        string appType = default("TTEAPITestApplication");
    gates:
        // Physical port of the host
        inout ethg;

    submodules:
        // Physical port of the host
        phy[1]: TTEPHYPort {
            @display("p=132,239");
        }
        // LLC for best-effort traffic
        llc: EtherLLC {
            parameters:
                @display("p=132,127");
            gates:
                upperLayerIn[3];
                upperLayerOut[3];
        }

        cli: EtherAppCli {
            parameters:
                registerSAP = true;
                @display("p=45,55,col");
        }
        srv: EtherAppSrv {
            parameters:
                registerSAP = true;
                @display("p=132,55,col");
        }
        // Buffer manager that creates the buffers according to the configuration
        bufferManager: BufferManager {
            @display("p=216,203");
        }
         // Sync module for synchronisation of the scheduler
        sync: Sync {
            @display("p=52,240");
        }
        // Scheudler for the device
        tteScheduler: TTEScheduler {
            @display("p=52,180");
        }
        tteApp: <appType> like ITTEApplication {
            @display("p=434,55");
        }
        bgIn: BGQueueBuffer {
            @display("p=291,55");
        }
        bgOut: BGQueueBuffer {
            @display("p=291,119");
        }
        bgTrafficHandle: BGTrafficHandle {
            @display("p=216,94");
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

