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

package ttethernet.examples.small_network_avb;

import ttethernet.nodes.ethernet.TTEAVBEtherHost;
import ttethernet.ctc.TTIncoming;
import ttethernet.buffer.TTDoubleBuffer;
import ttethernet.ctc.RCIncoming;
import ttethernet.buffer.RCQueueBuffer;


//
// unit3: configuration in unit3.ini.
//
// - Receives time-triggered messages with VL-ID 100 and rate-constrained messages with VL-ID 101
//
module Node3 extends TTEAVBEtherHost
{
    @display("bgb=487,314");
    submodules:
        vl_100_ctc: TTIncoming {
            parameters:
                @display("p=350,100");

        }
        vl_100: TTDoubleBuffer {
            parameters:
                @display("p=440,100");
        }
    connections:
        vl_100_ctc.out --> vl_100.in;
}
