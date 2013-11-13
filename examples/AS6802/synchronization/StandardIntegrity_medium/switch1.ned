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
                @display("p=1054,390");
        }


        vl_pcf_out_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=1205,308");
        }


        vl_pcf_out_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=1054,308");
        }



        vl_pcf_out_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=1205,390");
        }

      //a port that is connected to other compression master need a special handle to reduce cycle dependecy   

         //IN FRAMES
        vl_pcf_in_IN4: RCIncoming {
            parameters:
                @display("p=512,128");
        }
        vl_pcf_in_BUFIN4: RCQueueBuffer {
            parameters:
                @display("p=629,128");
        }
        //CS FRAMES
        vl_pcf_in_CS4: RCIncoming {
            parameters:
                @display("p=512,52");
        }
        vl_pcf_in_BUFCS4: RCQueueBuffer {
            parameters:
                @display("p=629,52");
        }
        //CA FRAMES
        vl_pcf_in_CA4: RCIncoming {
            parameters:
                @display("p=512,208");
        }
        vl_pcf_in_BUFCA4: RCQueueBuffer {
            parameters:
                @display("p=629,208");
        }
        //for compressed frames stems  from other compression master--------------------
        vl_pcf_in_BUFCAcomp: RCQueueBuffer {
            parameters:
                @display("p=1192,552");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCScomp: RCQueueBuffer {
            parameters:
                @display("p=1192,622");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFINcomp: RCQueueBuffer {
            parameters:
                @display("p=1192,491");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CAcomp: RCIncoming {
            parameters:
                @display("p=1054,568");
        }
        //CS FRAMES
        vl_pcf_in_CScomp: RCIncoming {
            parameters:
                @display("p=1054,642");
        }
        //IN FRAMES
        vl_pcf_in_INcomp: RCIncoming {
            parameters:
                @display("p=1054,498");
        }

      //  --------------------------------

        vl_pcf_in_BUFCA1: RCQueueBuffer {
            parameters:
                @display("p=864,112");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS1: RCQueueBuffer {
            parameters:
                @display("p=864,185");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFIN1: RCQueueBuffer {
            parameters:
                @display("p=864,48");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA1: RCIncoming {
            parameters:
                @display("p=747,112");
        }
        //CS FRAMES
        vl_pcf_in_CS1: RCIncoming {
            parameters:
                @display("p=747,185");
        }
        //IN FRAMES
        vl_pcf_in_IN1: RCIncoming {
            parameters:
                @display("p=747,48");
        }
        vl_pcf_in_BUFCA7: RCQueueBuffer {
            parameters:
                @display("p=864,429");
        }
        vl_pcf_in_BUFCS7: RCQueueBuffer {
            parameters:
                @display("p=864,273");
        }
        vl_pcf_in_BUFIN7: RCQueueBuffer {
            parameters:
                @display("p=864,349");
        }
        //CA FRAMES
        vl_pcf_in_CA7: RCIncoming {
            parameters:
                @display("p=747,429");
        }
        //CS FRAMES
        vl_pcf_in_CS7: RCIncoming {
            parameters:
                @display("p=747,273");
        }
        vl_pcf_in_IN7: RCIncoming {
            parameters:
                @display("p=747,349");
        }
        vl_pcf_in_BUFCA5: RCQueueBuffer {
            parameters:
                @display("p=621,647");
        }
        vl_pcf_in_BUFCS5: RCQueueBuffer {
            parameters:
                @display("p=621,491");
        }
        vl_pcf_in_BUFIN5: RCQueueBuffer {
            parameters:
                @display("p=621,567");
        }
        //CA FRAMES
        vl_pcf_in_CA5: RCIncoming {
            parameters:
                @display("p=504,647");
        }
        //CS FRAMES
        vl_pcf_in_CS5: RCIncoming {
            parameters:
                @display("p=504,491");
        }
        vl_pcf_in_IN5: RCIncoming {
            parameters:
                @display("p=504,567");
        }
        vl_pcf_in_BUFCA6: RCQueueBuffer {
            parameters:
                @display("p=864,645");
        }
        vl_pcf_in_BUFCS6: RCQueueBuffer {
            parameters:
                @display("p=864,492");
        }
        vl_pcf_in_BUFIN6: RCQueueBuffer {
            parameters:
                @display("p=864,567");
        }
        //CA FRAMES
        vl_pcf_in_CA6: RCIncoming {
            parameters:
                @display("p=747,647");
        }
        //CS FRAMES
        vl_pcf_in_CS6: RCIncoming {
            parameters:
                @display("p=747,492");
        }
        vl_pcf_in_IN6: RCIncoming {
            parameters:
                @display("p=747,567");
        }
        //CS FRAMES
        vl_pcf_in_CS3: RCIncoming {
            parameters:
                @display("p=1064,203");
        }
        //CA FRAMES
        vl_pcf_in_CA3: RCIncoming {
            parameters:
                @display("p=1064,130");
        }
        //IN FRAMES
        vl_pcf_in_IN3: RCIncoming {
            parameters:
                @display("p=1064,60");
        }
        vl_pcf_in_BUFIN3: RCQueueBuffer {
            parameters:
                @display("p=1181,60");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        vl_pcf_in_BUFCA3: RCQueueBuffer {
            parameters:
                @display("p=1181,130");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS3: RCQueueBuffer {
            parameters:
                @display("p=1181,203");
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


        vl_pcf_in_INcomp.out --> vl_pcf_in_BUFINcomp.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CAcomp.out --> vl_pcf_in_BUFCAcomp.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CScomp.out --> vl_pcf_in_BUFCScomp.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN1.out --> vl_pcf_in_BUFIN1.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA1.out --> vl_pcf_in_BUFCA1.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS1.out --> vl_pcf_in_BUFCS1.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_CS3.out --> vl_pcf_in_BUFCS3.in;

        vl_pcf_in_CA3.out --> vl_pcf_in_BUFCA3.in;

        vl_pcf_in_IN3.out --> vl_pcf_in_BUFIN3.in;


        vl_pcf_in_CS5.out --> vl_pcf_in_BUFCS5.in;

        vl_pcf_in_CA5.out --> vl_pcf_in_BUFCA5.in;

        vl_pcf_in_IN5.out --> vl_pcf_in_BUFIN5.in;


        vl_pcf_in_CA6.out --> vl_pcf_in_BUFCA6.in;

        vl_pcf_in_CS6.out --> vl_pcf_in_BUFCS6.in;

        vl_pcf_in_IN6.out --> vl_pcf_in_BUFIN6.in;



        vl_pcf_in_CA7.out --> vl_pcf_in_BUFCA7.in;

        vl_pcf_in_CS7.out --> vl_pcf_in_BUFCS7.in;

        vl_pcf_in_IN7.out --> vl_pcf_in_BUFIN7.in;


}
