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

package core4inet.examples.AS6802.synchronization.HighIntegrity_small;

import core4inet.nodes.ethernet.AS6802.TTEEtherHost;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;
import core4inet.incoming.AS6802.RCIncoming;
import core4inet.buffer.AS6802.RCQueueBuffer;

//
// unit2: configuration in unit2.ini.
//
// - Receives time-triggered messages with VL-ID 100
//
module Unit2 extends TTEEtherHost
{
    @display("bgb=969,490");
    submodules:

        //IN FRAMES
        vl_pcf_in_IN: RCIncoming {
            parameters:
                @display("p=427,117");
        }
        vl_pcf_in_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=550,117");
        }
        //CS FRAMES
        vl_pcf_in_CS: RCIncoming {
            parameters:
                @display("p=427,256");
        }
        vl_pcf_in_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=550,256");
        }
        //CA FRAMES
        vl_pcf_in_CA: RCIncoming {
            parameters:
                @display("p=427,186");
        }
        vl_pcf_in_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=550,186");
        }
    connections:


        vl_pcf_in_IN.out --> vl_pcf_in_BUFIN.in;
        vl_pcf_in_CS.out --> vl_pcf_in_BUFCS.in;
        vl_pcf_in_CA.out --> vl_pcf_in_BUFCA.in;
}
