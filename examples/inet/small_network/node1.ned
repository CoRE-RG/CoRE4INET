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

package core4inet.examples.inet.small_network;


import core4inet.nodes.inet.RTIPHost;
import core4inet.buffer.AS6802.RCQueueBuffer;
import core4inet.incoming.AS6802.RCIncoming;
import core4inet.buffer.AS6802.TTQueueBuffer;
import core4inet.incoming.AS6802.TTIncoming;

module Node1 extends RTIPHost
{
    submodules:
        vl_100_ctc: RCIncoming {
            parameters:
                @display("p=342,81");

        }
        vl_100: RCQueueBuffer {
            parameters:
                @display("p=420,81");
        }
        vl_101_ctc: TTIncoming {
            @display("p=342,34");
        }
        vl_101: TTQueueBuffer {

            @display("p=420,34");
        }
    connections:
        vl_100_ctc.out --> vl_100.in;
        vl_101_ctc.out --> vl_101.in;
}
