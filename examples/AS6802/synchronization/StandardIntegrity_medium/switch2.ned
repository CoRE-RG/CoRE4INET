
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
module Switch2 extends TTEEtherSwitch
{
    @display("bgb=1249,688");
    submodules:

        pcf_out[3]: PCFIncoming {

            @display("p=1013,396");
        }

        //}
        vl_pcf_out_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=1138,498");
        }

        //}
        vl_pcf_out_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=1138,396");
        }


        //}
        vl_pcf_out_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=1013,498");
        }

         //a port that is connected to other compression master need a special handle to reduce cycle dependecy   

         //IN FRAMES
        vl_pcf_in_IN3: RCIncoming {
            parameters:
                @display("p=716,138");
        }
        vl_pcf_in_BUFIN3: RCQueueBuffer {
            parameters:
                @display("p=858,138");
        }
        //CS FRAMES
        vl_pcf_in_CS3: RCIncoming {
            parameters:
                @display("p=716,76");
        }
        vl_pcf_in_BUFCS3: RCQueueBuffer {
            parameters:
                @display("p=858,76");
        }
        //CA FRAMES
        vl_pcf_in_CA3: RCIncoming {
            parameters:
                @display("p=716,206");
        }
        vl_pcf_in_BUFCA3: RCQueueBuffer {
            parameters:
                @display("p=858,206");
        }
        vl_pcf_in_BUFCA1: RCQueueBuffer {
            parameters:
                @display("p=587,209");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        vl_pcf_in_BUFCS1: RCQueueBuffer {
            parameters:
                @display("p=587,140");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        vl_pcf_in_BUFIN1: RCQueueBuffer {
            parameters:
                @display("p=594,70");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        //CA FRAMES
        vl_pcf_in_CA1: RCIncoming {
            parameters:
                @display("p=445,209");
        }
        //CS FRAMES
        vl_pcf_in_CS1: RCIncoming {
            parameters:
                @display("p=445,140");
        }
        //IN FRAMES
        vl_pcf_in_IN1: RCIncoming {
            parameters:
                @display("p=445,70");
        }
        //IN FRAMES
        vl_pcf_in_INcomp: RCIncoming {
            parameters:
                @display("p=984,70");
        }
        vl_pcf_in_BUFINcomp: RCQueueBuffer {
            parameters:
                @display("p=1099,54");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        //CS FRAMES
        vl_pcf_in_CScomp: RCIncoming {
            parameters:
                @display("p=984,140");
        }
        vl_pcf_in_BUFCScomp: RCQueueBuffer {
            parameters:
                @display("p=1099,123");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CA FRAMES
        vl_pcf_in_CAcomp: RCIncoming {
            parameters:
                @display("p=984,215");
        }
        vl_pcf_in_BUFCAcomp: RCQueueBuffer {
            parameters:
                @display("p=1099,205");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //CS FRAMES
        vl_pcf_in_CS4: RCIncoming {
            parameters:
                @display("p=445,291");
        }
        vl_pcf_in_BUFCS4: RCQueueBuffer {
            parameters:
                @display("p=587,291");
        }
        vl_pcf_in_IN4: RCIncoming {
            parameters:
                @display("p=445,353");
        }
        vl_pcf_in_BUFIN4: RCQueueBuffer {
            parameters:
                @display("p=587,353");
        }
        //CA FRAMES
        vl_pcf_in_CA4: RCIncoming {
            parameters:
                @display("p=445,421");
        }
        vl_pcf_in_BUFCA4: RCQueueBuffer {
            parameters:
                @display("p=587,421");
        }
        //CS FRAMES
        vl_pcf_in_CS5: RCIncoming {
            parameters:
                @display("p=716,292");
        }
        vl_pcf_in_BUFCS5: RCQueueBuffer {
            parameters:
                @display("p=858,292");
        }
        vl_pcf_in_IN5: RCIncoming {
            parameters:
                @display("p=716,354");
        }
        vl_pcf_in_BUFIN5: RCQueueBuffer {
            parameters:
                @display("p=858,354");
        }
        //CA FRAMES
        vl_pcf_in_CA5: RCIncoming {
            parameters:
                @display("p=716,422");
        }
        vl_pcf_in_BUFCA5: RCQueueBuffer {
            parameters:
                @display("p=858,422");
        }
        //CS FRAMES
        vl_pcf_in_CS6: RCIncoming {
            parameters:
                @display("p=445,498");
        }
        vl_pcf_in_BUFCS6: RCQueueBuffer {
            parameters:
                @display("p=587,498");
        }
        vl_pcf_in_IN6: RCIncoming {
            parameters:
                @display("p=445,560");
        }
        vl_pcf_in_BUFIN6: RCQueueBuffer {
            parameters:
                @display("p=587,560");
        }
        //CA FRAMES
        vl_pcf_in_CA6: RCIncoming {
            parameters:
                @display("p=445,628");
        }
        vl_pcf_in_BUFCA6: RCQueueBuffer {
            parameters:
                @display("p=587,628");
        }
        //CS FRAMES
        vl_pcf_in_CS7: RCIncoming {
            parameters:
                @display("p=716,499");
        }
        vl_pcf_in_BUFCS7: RCQueueBuffer {
            parameters:
                @display("p=858,499");
        }
        vl_pcf_in_IN7: RCIncoming {
            parameters:
                @display("p=716,561");
        }
        vl_pcf_in_BUFIN7: RCQueueBuffer {
            parameters:
                @display("p=858,561");
        }
        //CA FRAMES
        vl_pcf_in_CA7: RCIncoming {
            parameters:
                @display("p=716,629");
        }
        vl_pcf_in_BUFCA7: RCQueueBuffer {
            parameters:
                @display("p=858,629");
        }
    connections:


        vl_pcf_in_IN3.out --> vl_pcf_in_BUFIN3.in;
        vl_pcf_in_CS3.out --> vl_pcf_in_BUFCS3.in;
        vl_pcf_in_CA3.out --> vl_pcf_in_BUFCA3.in;
        pcf_out[0].out --> vl_pcf_out_BUFCS.in;
        pcf_out[1].out --> vl_pcf_out_BUFCA.in;
        pcf_out[2].out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CS1.out --> vl_pcf_in_BUFCS1.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN1.out --> vl_pcf_in_BUFIN1.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA1.out --> vl_pcf_in_BUFCA1.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CScomp.out --> vl_pcf_in_BUFCScomp.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_INcomp.out --> vl_pcf_in_BUFINcomp.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CAcomp.out --> vl_pcf_in_BUFCAcomp.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_IN4.out --> vl_pcf_in_BUFIN4.in;
        vl_pcf_in_CS4.out --> vl_pcf_in_BUFCS4.in;
        vl_pcf_in_CA4.out --> vl_pcf_in_BUFCA4.in;
        vl_pcf_in_IN5.out --> vl_pcf_in_BUFIN5.in;
        vl_pcf_in_CS5.out --> vl_pcf_in_BUFCS5.in;
        vl_pcf_in_CA5.out --> vl_pcf_in_BUFCA5.in;
        vl_pcf_in_IN6.out --> vl_pcf_in_BUFIN6.in;
        vl_pcf_in_CS6.out --> vl_pcf_in_BUFCS6.in;
        vl_pcf_in_CA6.out --> vl_pcf_in_BUFCA6.in;
        vl_pcf_in_IN7.out --> vl_pcf_in_BUFIN7.in;
        vl_pcf_in_CS7.out --> vl_pcf_in_BUFCS7.in;
        vl_pcf_in_CA7.out --> vl_pcf_in_BUFCA7.in;
}
