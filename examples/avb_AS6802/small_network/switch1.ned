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

package core4inet.examples.avb_AS6802.small_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;

//
// switch1: configuration in switch1.ini
// Forwards time-triggered messages with VL-ID 100
//
module Switch1 extends TTEAVBEtherSwitch
{
    @display("bgb=990,547");
    submodules:
        vl_100_ctc: TTIncoming {
            parameters:
                @display("p=534,111");
        }
        vl_100: TTDoubleBuffer {
            parameters:
                @display("p=604,111");
        }
    connections:
        vl_100_ctc.out --> vl_100.in;
}
