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

package core4inet.examples.AS6802.synchronization.StandardIntegrity_medium;

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
module Unit5 extends TTEEtherHost
{
    @display("bgb=986,555");
    submodules:

        //IN FRAMES
        vl_pcf_in_IN: RCIncoming {
            parameters:
                @display("p=419,64");
        }
        vl_pcf_in_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=542,64");
        }
        vl_pcf_out_IN: RCIncoming {
            parameters:
                @display("p=746,134");
        }
        vl_pcf_out_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=869,134");
        }

        //CS FRAMES
        vl_pcf_in_CS: RCIncoming {
            parameters:
                @display("p=419,134");
        }
        vl_pcf_in_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=542,134");
        }
        vl_pcf_out_CS: RCIncoming {
            parameters:
                @display("p=746,57");
        }
        vl_pcf_out_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=858,60");
        }


        //CA FRAMES
        vl_pcf_in_CA: RCIncoming {
            parameters:
                @display("p=419,203");
        }
        vl_pcf_in_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=542,203");
        }
        vl_pcf_out_CA: RCIncoming {
            parameters:
                @display("p=746,208");
        }
        vl_pcf_out_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=869,208");
        }
        //IN FRAMES
        vl_pcf_in_IN1: RCIncoming {
            parameters:
                @display("p=425,307");
        }
        vl_pcf_in_BUFIN1: RCQueueBuffer {
            parameters:
                @display("p=548,307");
        }
        vl_pcf_in_BUFCS1: RCQueueBuffer {
            parameters:
                @display("p=548,377");
        }
        //CS FRAMES
        vl_pcf_in_CS1: RCIncoming {
            parameters:
                @display("p=425,377");
        }
        //CA FRAMES
        vl_pcf_in_CA1: RCIncoming {
            parameters:
                @display("p=425,446");
        }
        vl_pcf_in_BUFCA1: RCQueueBuffer {
            parameters:
                @display("p=548,446");
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
