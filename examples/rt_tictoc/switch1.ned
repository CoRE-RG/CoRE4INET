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

import ttethernet.nodes.ethernet.AS6802.TTEEtherSwitch;
import ttethernet.incoming.AS6802.TTIncoming;
import ttethernet.buffer.AS6802.TTDoubleBuffer;
import ttethernet.incoming.AS6802.RCIncoming;
import ttethernet.buffer.AS6802.RCQueueBuffer;

//
// switch1: configuration in switch1.ini
// Forwards time-triggered messages with VL-ID 100 and rc messages with VL-ID 101
//
module Switch1 extends TTEEtherSwitch
{
    @display("bgb=500,312");
    submodules:
        vl_100_ctc: TTIncoming {
            parameters:
                @display("p=349,60");
        }
        vl_100: TTDoubleBuffer {
            parameters:
                @display("p=439,61");
        }
        vl_101_ctc: RCIncoming {
            parameters:
                @display("p=349,140");
        }
        vl_101: RCQueueBuffer {
            parameters:
                @display("p=439,141");
        }
    connections:
        vl_100_ctc.out --> vl_100.in;
        vl_101_ctc.out --> vl_101.in;
}
