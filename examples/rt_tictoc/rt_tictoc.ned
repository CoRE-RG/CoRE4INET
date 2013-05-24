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

package ttethernet.examples.rt_tictoc;

import ttethernet.nodes.ethernet.TTEEtherHost;

//
// Small sample network with two hosts and one switch that shows how to 
// build application models for the simulation. The example uses two different
// applications (TicApp and TocApp) that pass messages to each other
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network rt_tictoc
{
    @display("bgb=,,white");
    types:
        //
        // All links are configured with 100MBit per second and variable delay
        //
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            //bit error rate (probability (0.0-1.0) per bit)  
            ber = 0;
            //packet error rate (probability (0.0-1.0) per packet)  
            per = 0;
        }
    submodules:
        //Device hosting the Tic application
        tic: Tic {
            @display("p=39,70");
        }
		//Device hosting the Toc application
        toc: Toc {
            @display("p=247,70");
        }
		//Switch that forwards Tic and Toc messages
        switch1: Switch1 {
            parameters:
                @display("p=147,70");
            gates:
                ethg[2];
        }
    connections:
        //
        // The example uses a simple star topology
        //
        tic.ethg <--> cable {  delay = 200ns; } <--> switch1.ethg[0];
        toc.ethg <--> cable {  delay = 100ns; } <--> switch1.ethg[1];
}
