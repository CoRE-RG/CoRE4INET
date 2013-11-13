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

package core4inet.examples.AS6802.small_network;

import core4inet.nodes.ethernet.AS6802.TTEEtherHost;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;
import core4inet.incoming.AS6802.RCIncoming;
import core4inet.buffer.AS6802.RCQueueBuffer;


//
// unit3: configuration in unit3.ini.
//
// - Receives time-triggered messages with VL-ID 100 and rate-constrained messages with VL-ID 101
//
module Node3 extends TTEEtherHost
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
        vl_101_ctc: RCIncoming {
            parameters:
                @display("p=350,160");

        }
        vl_101: RCQueueBuffer {
            parameters:
                @display("p=440,160");
        }
    connections:
        vl_100_ctc.out --> vl_100.in;
        vl_101_ctc.out --> vl_101.in;
}
