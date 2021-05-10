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

package core4inet.nodes.inet;

//INET
import inet.node.inet.StandardHost;
//CoRE4INET
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.incoming.avb.AVBIncoming;
import core4inet.buffer.avb.AVBQueueBuffer;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.applications.base.IApplication;

//
// This network host combines the inet framework standard host with the core4inet TSN features.
// As it extends the @see ~inet::StandardHost it can run any additional inet compatible application.
//
// @author Timo Haeckel, for HAW Hamburg
//
module TSNInetHost extends StandardHost
{
    parameters:
        eth[0].typename = "TSNEtherNic";
        networkLayerType = default("RTNetworkLayer");
    submodules:
        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=655,40");
        }

        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=710,40");
        }

        // Stream Reservation Protocol table
        srpTable: SRPTable {
            @display("p=519,287");
        }

		// Stream Reservation Protocol implementation
        srpProtocol: SRProtocol {
            @display("p=441,287");
        }
        
    connections allowunconnected:
		//this only throws an error in the IDE but works in the current omnet version!
        srpProtocol.out --> eth[0].srpIn;
        srpProtocol.in <-- eth[0].srpOut;

}
