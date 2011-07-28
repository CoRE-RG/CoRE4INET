//
// Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//



package ttethernet.nodes.ethernet;

import ttethernet.scheduler.TTEScheduler;
import ttethernet.buffer.BufferManager;
import ttethernet.api.TTEthAPI;
import ttethernet.linklayer.TTEPHYPort;
import ttethernet.linklayer.Sync;
import ttethernet.applications.ITTEApplication;
import inet.linklayer.ethernet.EtherLLC;
import inet.applications.ethernet.EtherAppSrv;
import inet.applications.ethernet.EtherAppCli;
//
// Example host model with one Ethernet port and several traffic generators
// to create traffic in the test network.
//
module TTEEtherHost
{
    parameters:
        @display("bgb=596,314;i=device/device");
        string network_configuration;
        string device_name;
    gates:
        inout ethg;

    submodules:
        phy[1]: TTEPHYPort {
            @display("p=132,239");
        }

        llc: EtherLLC {
            parameters:
                @display("p=132,127");
            gates:
                upperLayerIn[2];
                upperLayerOut[2];
        }
        cli: EtherAppCli {
            parameters:
                registerSAP = true;
                @display("p=45,55,col");
        }
        srv: EtherAppSrv {
            parameters:
                registerSAP = true;
                @display("p=235,55,col");
        }
        bufferManager: BufferManager {
            @display("p=216,203");
        }
        sync: Sync {
            @display("p=52,240");
        }
        tteScheduler: TTEScheduler {
            @display("p=52,180");
        }
    connections:
        phy[0].phys <--> ethg;
        llc.lowerLayerOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> llc.lowerLayerIn;

        cli.out --> llc.upperLayerIn[0];
        cli.in <-- llc.upperLayerOut[0];

        srv.out --> llc.upperLayerIn[1];
        srv.in <-- llc.upperLayerOut[1];
}

