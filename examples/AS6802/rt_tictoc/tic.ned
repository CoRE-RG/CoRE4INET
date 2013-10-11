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

package ttethernet.examples.AS6802.rt_tictoc;

import ttethernet.nodes.ethernet.AS6802.TTEEtherHost;
import ttethernet.incoming.AS6802.TTIncoming;
import ttethernet.buffer.AS6802.TTDoubleBuffer;
import ttethernet.incoming.AS6802.RCIncoming;
import ttethernet.buffer.AS6802.RCQueueBuffer;

//
// tic: configuration in tic.ini.
//
// - Sends time-triggered messages at 1ms with VL-ID 100, receives rate-constrained messages with VL-ID 101
//
module Tic extends TTEEtherHost
{
    @display("bgb=503,314");
    submodules:
        vl_100_ctc: TTIncoming {
            parameters:
                @display("p=350,60");

        }
        vl_100: TTDoubleBuffer {
            parameters:
                @display("p=450,60");
        }
        vl_101_ctc: RCIncoming {
            parameters:
                @display("p=350,160");

        }
        vl_101: RCQueueBuffer {
            parameters:
                @display("p=450,160");
        }
    connections:
        vl_100_ctc.out --> vl_100.in;
        vl_101_ctc.out --> vl_101.in;
}
