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

import core4inet.nodes.ethernet.AS6802.TTEEtherSwitch;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;
import core4inet.incoming.AS6802.RCIncoming;
import core4inet.buffer.AS6802.RCQueueBuffer;
import core4inet.incoming.AS6802.PCFIncoming;
//
// switch1: configuration in switch1.ini
// Forwards time-triggered messages with VL-ID 100
//
module Switch1 extends TTEEtherSwitch
{
    @display("bgb=1307,707");
    submodules:


        pcf_out[3]: PCFIncoming {
            parameters:
                @display("p=737,417");
        }


        vl_pcf_out_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=888,335");
        }


        vl_pcf_out_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=737,335");
        }



        vl_pcf_out_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=888,417");
        }

      //a port that is connected to other compression master need a special handle to reduce cycle dependecy   

         //IN FRAMES
        vl_pcf_in_IN4: RCIncoming {
            parameters:
                @display("p=442,345");
        }
        vl_pcf_in_BUFIN4: RCQueueBuffer {
            parameters:
                @display("p=571,345");
        }
        //CS FRAMES
        vl_pcf_in_CS4: RCIncoming {
            parameters:
                @display("p=442,269");
        }
        vl_pcf_in_BUFCS4: RCQueueBuffer {
            parameters:
                @display("p=571,269");
        }
        //CA FRAMES
        vl_pcf_in_CA4: RCIncoming {
            parameters:
                @display("p=442,425");
        }
        vl_pcf_in_BUFCA4: RCQueueBuffer {
            parameters:
                @display("p=571,425");
        }
        vl_pcf_in_BUFCA1: RCQueueBuffer {
            parameters:
                @display("p=571,116");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS1: RCQueueBuffer {
            parameters:
                @display("p=571,189");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFIN1: RCQueueBuffer {
            parameters:
                @display("p=571,52");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA1: RCIncoming {
            parameters:
                @display("p=454,116");
        }
        //CS FRAMES
        vl_pcf_in_CS1: RCIncoming {
            parameters:
                @display("p=454,189");
        }
        //IN FRAMES
        vl_pcf_in_IN1: RCIncoming {
            parameters:
                @display("p=454,52");
        }
        //CS FRAMES
        vl_pcf_in_CS3: RCIncoming {
            parameters:
                @display("p=747,204");
        }
        //CA FRAMES
        vl_pcf_in_CA3: RCIncoming {
            parameters:
                @display("p=747,131");
        }
        //IN FRAMES
        vl_pcf_in_IN3: RCIncoming {
            parameters:
                @display("p=747,61");
        }
        vl_pcf_in_BUFIN3: RCQueueBuffer {
            parameters:
                @display("p=864,61");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        vl_pcf_in_BUFCA3: RCQueueBuffer {
            parameters:
                @display("p=864,131");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS3: RCQueueBuffer {
            parameters:
                @display("p=864,204");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
    connections:


        vl_pcf_in_IN4.out --> vl_pcf_in_BUFIN4.in;
        vl_pcf_in_CS4.out --> vl_pcf_in_BUFCS4.in;
        vl_pcf_in_CA4.out --> vl_pcf_in_BUFCA4.in;

        pcf_out[0].out --> vl_pcf_out_BUFCS.in;
        pcf_out[1].out --> vl_pcf_out_BUFCA.in;
        pcf_out[2].out --> vl_pcf_out_BUFIN.in;


        vl_pcf_in_IN1.out --> vl_pcf_in_BUFIN1.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA1.out --> vl_pcf_in_BUFCA1.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS1.out --> vl_pcf_in_BUFCS1.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_CS3.out --> vl_pcf_in_BUFCS3.in;

        vl_pcf_in_CA3.out --> vl_pcf_in_BUFCA3.in;

        vl_pcf_in_IN3.out --> vl_pcf_in_BUFIN3.in;


}
