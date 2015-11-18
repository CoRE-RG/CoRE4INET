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

package core4inet.examples.AS6802.synchronization.StandardIntegrity_large;

import core4inet.nodes.ethernet.AS6802.TTEEtherHost;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;
import core4inet.incoming.AS6802.RCIncoming;
import core4inet.buffer.AS6802.RCQueueBuffer;


//
// unit1: configuration in unit1.ini.
//
// - Sends time-triggered messages at 1ms with VL-ID 100
//
module Unit3 extends TTEEtherHost
{
    @display("bgb=922,500");
    submodules:

        //IN FRAMES
        vl_pcf_in_IN: RCIncoming {
            parameters:
                @display("p=349,60");
        }
        vl_pcf_in_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=472,60");
        }
        vl_pcf_out_IN: RCIncoming {
            parameters:
                @display("p=608,271");
        }
        vl_pcf_out_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=731,271");
        }

        //CS FRAMES
        vl_pcf_in_CS: RCIncoming {
            parameters:
                @display("p=349,130");
        }
        vl_pcf_in_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=472,130");
        }
        vl_pcf_out_CS: RCIncoming {
            parameters:
                @display("p=608,193");
        }
        vl_pcf_out_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=731,193");
        }


        //CA FRAMES
        vl_pcf_in_CA: RCIncoming {
            parameters:
                @display("p=349,199");
        }
        vl_pcf_in_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=472,199");
        }
        vl_pcf_out_CA: RCIncoming {
            parameters:
                @display("p=608,346");
        }
        vl_pcf_out_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=731,346");
        }
        //CA FRAMES
        vl_pcf_in_CA1: RCIncoming {
            parameters:
                @display("p=349,415");
        }
        //CS FRAMES
        vl_pcf_in_CS1: RCIncoming {
            parameters:
                @display("p=349,346");
        }
        //IN FRAMES
        vl_pcf_in_IN1: RCIncoming {
            parameters:
                @display("p=349,276");
        }
        vl_pcf_in_BUFIN1: RCQueueBuffer {
            parameters:
                @display("p=472,276");
        }
        vl_pcf_in_BUFCS1: RCQueueBuffer {
            parameters:
                @display("p=472,346");
        }
        vl_pcf_in_BUFCA1: RCQueueBuffer {
            parameters:
                @display("p=472,415");
        }
    connections:


        vl_pcf_in_IN.out --> vl_pcf_in_BUFIN.in;
        vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CS.out --> vl_pcf_in_BUFCS.in;
        vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_CA.out --> vl_pcf_in_BUFCA.in;
        vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;
        vl_pcf_in_IN1.out --> vl_pcf_in_BUFIN1.in;
        vl_pcf_in_CS1.out --> vl_pcf_in_BUFCS1.in;
        vl_pcf_in_CA1.out --> vl_pcf_in_BUFCA1.in;
}
