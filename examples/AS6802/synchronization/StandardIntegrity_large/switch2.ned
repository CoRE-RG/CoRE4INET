
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
    @display("bgb=1301,796");
    submodules:

        pcf_out[3]: PCFIncoming {

            @display("p=1120,631;is=s");
        }

        //}
        vl_pcf_out_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=1245,733;is=s");
        }

        //}
        vl_pcf_out_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=1245,631;is=s");
        }


        //}
        vl_pcf_out_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=1120,733;is=s");
        }

         //a port that is connected to other compression master need a special handle to reduce cycle dependecy   

         //IN FRAMES
        vl_pcf_in_IN3: RCIncoming {
            parameters:
                @display("p=616,483;is=s");
        }
        vl_pcf_in_BUFIN3: RCQueueBuffer {
            parameters:
                @display("p=758,483;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS3: RCIncoming {
            parameters:
                @display("p=616,446;is=s");
        }
        vl_pcf_in_BUFCS3: RCQueueBuffer {
            parameters:
                @display("p=758,446;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA3: RCIncoming {
            parameters:
                @display("p=616,520;is=s");
        }
        vl_pcf_in_BUFCA3: RCQueueBuffer {
            parameters:
                @display("p=758,520;is=s");
        }

        vl_pcf_in_BUFCA1: RCQueueBuffer {
            parameters:
                @display("p=487,523;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        vl_pcf_in_BUFCS1: RCQueueBuffer {
            parameters:
                @display("p=487,485;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        vl_pcf_in_BUFIN1: RCQueueBuffer {
            parameters:
                @display("p=487,440;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        //CA FRAMES
        vl_pcf_in_CA1: RCIncoming {
            parameters:
                @display("p=345,523;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS1: RCIncoming {
            parameters:
                @display("p=345,485;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN1: RCIncoming {
            parameters:
                @display("p=345,440;is=s");
        }
        //IN FRAMES
        vl_pcf_in_INcomp: RCIncoming {
            parameters:
                @display("p=1130,485;is=s");
        }
        vl_pcf_in_BUFINcomp: RCQueueBuffer {
            parameters:
                @display("p=1245,469;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        //CS FRAMES
        vl_pcf_in_CScomp: RCIncoming {
            parameters:
                @display("p=1130,525;is=s");
        }
        vl_pcf_in_BUFCScomp: RCQueueBuffer {
            parameters:
                @display("p=1245,508;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CA FRAMES
        vl_pcf_in_CAcomp: RCIncoming {
            parameters:
                @display("p=1130,573;is=s");
        }
        vl_pcf_in_BUFCAcomp: RCQueueBuffer {
            parameters:
                @display("p=1245,563;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //CS FRAMES
        vl_pcf_in_CS4: RCIncoming {
            parameters:
                @display("p=345,568;is=s");
        }
        vl_pcf_in_BUFCS4: RCQueueBuffer {
            parameters:
                @display("p=487,568;is=s");
        }
        vl_pcf_in_IN4: RCIncoming {
            parameters:
                @display("p=345,604;is=s");
        }
        vl_pcf_in_BUFIN4: RCQueueBuffer {
            parameters:
                @display("p=487,604;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA4: RCIncoming {
            parameters:
                @display("p=345,638;is=s");
        }
        vl_pcf_in_BUFCA4: RCQueueBuffer {
            parameters:
                @display("p=487,638;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS5: RCIncoming {
            parameters:
                @display("p=616,569;is=s");
        }
        vl_pcf_in_BUFCS5: RCQueueBuffer {
            parameters:
                @display("p=758,569;is=s");
        }
        vl_pcf_in_IN5: RCIncoming {
            parameters:
                @display("p=616,605;is=s");
        }
        vl_pcf_in_BUFIN5: RCQueueBuffer {
            parameters:
                @display("p=758,605;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA5: RCIncoming {
            parameters:
                @display("p=616,639;is=s");
        }
        vl_pcf_in_BUFCA5: RCQueueBuffer {
            parameters:
                @display("p=758,639;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS6: RCIncoming {
            parameters:
                @display("p=345,686;is=s");
        }
        vl_pcf_in_BUFCS6: RCQueueBuffer {
            parameters:
                @display("p=487,686;is=s");
        }
        vl_pcf_in_IN6: RCIncoming {
            parameters:
                @display("p=345,724;is=s");
        }
        vl_pcf_in_BUFIN6: RCQueueBuffer {
            parameters:
                @display("p=487,724;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA6: RCIncoming {
            parameters:
                @display("p=345,761;is=s");
        }
        vl_pcf_in_BUFCA6: RCQueueBuffer {
            parameters:
                @display("p=487,761;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS7: RCIncoming {
            parameters:
                @display("p=616,686;is=s");
        }
        vl_pcf_in_BUFCS7: RCQueueBuffer {
            parameters:
                @display("p=758,686;is=s");
        }
        vl_pcf_in_IN7: RCIncoming {
            parameters:
                @display("p=616,724;is=s");
        }
        vl_pcf_in_BUFIN7: RCQueueBuffer {
            parameters:
                @display("p=758,724;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA7: RCIncoming {
            parameters:
                @display("p=616,762;is=s");
        }
        vl_pcf_in_BUFCA7: RCQueueBuffer {
            parameters:
                @display("p=758,762;is=s");
        }


        //IN FRAMES
        vl_pcf_in_IN21: RCIncoming {
            parameters:
                @display("p=345,317;is=s");
        }
        vl_pcf_in_BUFIN21: RCQueueBuffer {
            parameters:
                @display("p=487,317;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS21: RCQueueBuffer {
            parameters:
                @display("p=487,362;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS21: RCIncoming {
            parameters:
                @display("p=345,362;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA21: RCIncoming {
            parameters:
                @display("p=345,400;is=s");
        }
        vl_pcf_in_BUFCA21: RCQueueBuffer {
            parameters:
                @display("p=487,400;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //IN FRAMES
        vl_pcf_in_IN8: RCIncoming {
            parameters:
                @display("p=345,182;is=s");
        }
        vl_pcf_in_BUFIN8: RCQueueBuffer {
            parameters:
                @display("p=487,182;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS8: RCQueueBuffer {
            parameters:
                @display("p=487,227;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS8: RCIncoming {
            parameters:
                @display("p=345,227;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA8: RCIncoming {
            parameters:
                @display("p=345,265;is=s");
        }
        vl_pcf_in_BUFCA8: RCQueueBuffer {
            parameters:
                @display("p=487,265;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //IN FRAMES
        vl_pcf_in_IN9: RCIncoming {
            parameters:
                @display("p=616,317;is=s");
        }
        vl_pcf_in_BUFIN9: RCQueueBuffer {
            parameters:
                @display("p=765,317;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS9: RCQueueBuffer {
            parameters:
                @display("p=758,362;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS9: RCIncoming {
            parameters:
                @display("p=616,362;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA9: RCIncoming {
            parameters:
                @display("p=616,400;is=s");
        }
        vl_pcf_in_BUFCA9: RCQueueBuffer {
            parameters:
                @display("p=758,400;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //IN FRAMES
        vl_pcf_in_IN10: RCIncoming {
            parameters:
                @display("p=616,185;is=s");
        }
        vl_pcf_in_BUFIN10: RCQueueBuffer {
            parameters:
                @display("p=765,185;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS10: RCQueueBuffer {
            parameters:
                @display("p=758,230;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS10: RCIncoming {
            parameters:
                @display("p=616,230;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA10: RCIncoming {
            parameters:
                @display("p=616,268;is=s");
        }
        vl_pcf_in_BUFCA10: RCQueueBuffer {
            parameters:
                @display("p=758,268;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //CA FRAMES
        vl_pcf_in_CA11: RCIncoming {
            parameters:
                @display("p=345,138;is=s");
        }
        vl_pcf_in_BUFCA11: RCQueueBuffer {
            parameters:
                @display("p=487,138;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        vl_pcf_in_BUFCS11: RCQueueBuffer {
            parameters:
                @display("p=487,100;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        vl_pcf_in_BUFIN11: RCQueueBuffer {
            parameters:
                @display("p=487,55;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        //IN FRAMES
        vl_pcf_in_IN11: RCIncoming {
            parameters:
                @display("p=345,55;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS11: RCIncoming {
            parameters:
                @display("p=345,100;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN12: RCIncoming {
            parameters:
                @display("p=609,55;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS12: RCIncoming {
            parameters:
                @display("p=609,100;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA12: RCIncoming {
            parameters:
                @display("p=609,138;is=s");
        }
        vl_pcf_in_BUFCA12: RCQueueBuffer {
            parameters:
                @display("p=751,138;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        vl_pcf_in_BUFCS12: RCQueueBuffer {
            parameters:
                @display("p=751,100;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        vl_pcf_in_BUFIN12: RCQueueBuffer {
            parameters:
                @display("p=758,55;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        //IN FRAMES
        vl_pcf_in_IN13: RCIncoming {
            parameters:
                @display("p=851,40;is=s");
        }
        vl_pcf_in_BUFIN13: RCQueueBuffer {
            parameters:
                @display("p=1000,40;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS13: RCQueueBuffer {
            parameters:
                @display("p=993,85;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS13: RCIncoming {
            parameters:
                @display("p=851,85;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA13: RCIncoming {
            parameters:
                @display("p=851,123;is=s");
        }
        vl_pcf_in_BUFCA13: RCQueueBuffer {
            parameters:
                @display("p=993,123;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //IN FRAMES
        vl_pcf_in_IN14: RCIncoming {
            parameters:
                @display("p=857,169;is=s");
        }
        vl_pcf_in_BUFIN14: RCQueueBuffer {
            parameters:
                @display("p=1006,169;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS14: RCQueueBuffer {
            parameters:
                @display("p=999,214;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        vl_pcf_in_BUFCA14: RCQueueBuffer {
            parameters:
                @display("p=999,252;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //CA FRAMES
        vl_pcf_in_CA14: RCIncoming {
            parameters:
                @display("p=857,252;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS14: RCIncoming {
            parameters:
                @display("p=857,214;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN15: RCIncoming {
            parameters:
                @display("p=857,307;is=s");
        }
        vl_pcf_in_BUFIN15: RCQueueBuffer {
            parameters:
                @display("p=1006,307;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS15: RCQueueBuffer {
            parameters:
                @display("p=999,352;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS15: RCIncoming {
            parameters:
                @display("p=857,352;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA15: RCIncoming {
            parameters:
                @display("p=857,390;is=s");
        }
        vl_pcf_in_BUFCA15: RCQueueBuffer {
            parameters:
                @display("p=999,390;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //IN FRAMES
        vl_pcf_in_IN16: RCIncoming {
            parameters:
                @display("p=857,446;is=s");
        }
        vl_pcf_in_BUFIN16: RCQueueBuffer {
            parameters:
                @display("p=1006,446;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS16: RCQueueBuffer {
            parameters:
                @display("p=999,491;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS16: RCIncoming {
            parameters:
                @display("p=857,491;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA16: RCIncoming {
            parameters:
                @display("p=857,529;is=s");
        }
        vl_pcf_in_BUFCA16: RCQueueBuffer {
            parameters:
                @display("p=999,529;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        //IN FRAMES
        vl_pcf_in_IN17: RCIncoming {
            parameters:
                @display("p=857,573;is=s");
        }
        vl_pcf_in_BUFIN17: RCQueueBuffer {
            parameters:
                @display("p=1006,573;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        //CS FRAMES
        vl_pcf_in_CS17: RCIncoming {
            parameters:
                @display("p=857,618;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA17: RCIncoming {
            parameters:
                @display("p=857,656;is=s");
        }
        vl_pcf_in_BUFCA17: RCQueueBuffer {
            parameters:
                @display("p=999,656;is=s");
        }
       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
        vl_pcf_in_BUFCS17: RCQueueBuffer {
            parameters:
                @display("p=999,618;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //IN FRAMES
        vl_pcf_in_IN18: RCIncoming {
            parameters:
                @display("p=864,701;is=s");
        }
        vl_pcf_in_BUFIN18: RCQueueBuffer {
            parameters:
                @display("p=1013,701;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS18: RCQueueBuffer {
            parameters:
                @display("p=1006,746;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS18: RCIncoming {
            parameters:
                @display("p=864,746;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA18: RCIncoming {
            parameters:
                @display("p=864,784;is=s");
        }
        vl_pcf_in_BUFCA18: RCQueueBuffer {
            parameters:
                @display("p=1006,784;is=s");
        }

         //IN FRAMES
        vl_pcf_in_IN19: RCIncoming {
            parameters:
                @display("p=1107,200;is=s");
        }
        vl_pcf_in_BUFIN19: RCQueueBuffer {
            parameters:
                @display("p=1256,200;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS19: RCQueueBuffer {
            parameters:
                @display("p=1249,245;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS19: RCIncoming {
            parameters:
                @display("p=1107,245;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA19: RCIncoming {
            parameters:
                @display("p=1107,283;is=s");
        }
        vl_pcf_in_BUFCA19: RCQueueBuffer {
            parameters:
                @display("p=1249,283;is=s");
        }

          //IN FRAMES
        vl_pcf_in_IN20: RCIncoming {
            parameters:
                @display("p=1096,55;is=s");
        }
        vl_pcf_in_BUFIN20: RCQueueBuffer {
            parameters:
                @display("p=1245,55;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=583,137");
        vl_pcf_in_BUFCS20: RCQueueBuffer {
            parameters:
                @display("p=1238,100;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=583,60");
        //CS FRAMES
        vl_pcf_in_CS20: RCIncoming {
            parameters:
                @display("p=1096,100;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA20: RCIncoming {
            parameters:
                @display("p=1096,138;is=s");
        }
        vl_pcf_in_BUFCA20: RCQueueBuffer {
            parameters:
                @display("p=1238,138;is=s");
        }

       // vl_pcf_out_CA: RCIncoming {
         //   parameters:
           //     @display("p=583,217");
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
        vl_pcf_in_CS21.out --> vl_pcf_in_BUFCS21.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN21.out --> vl_pcf_in_BUFIN21.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA21.out --> vl_pcf_in_BUFCA21.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS8.out --> vl_pcf_in_BUFCS8.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN8.out --> vl_pcf_in_BUFIN8.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA8.out --> vl_pcf_in_BUFCA8.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS9.out --> vl_pcf_in_BUFCS9.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN9.out --> vl_pcf_in_BUFIN9.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA9.out --> vl_pcf_in_BUFCA9.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS10.out --> vl_pcf_in_BUFCS10.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN10.out --> vl_pcf_in_BUFIN10.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA10.out --> vl_pcf_in_BUFCA10.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS11.out --> vl_pcf_in_BUFCS11.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN11.out --> vl_pcf_in_BUFIN11.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA11.out --> vl_pcf_in_BUFCA11.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS12.out --> vl_pcf_in_BUFCS12.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN12.out --> vl_pcf_in_BUFIN12.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA12.out --> vl_pcf_in_BUFCA12.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS13.out --> vl_pcf_in_BUFCS13.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN13.out --> vl_pcf_in_BUFIN13.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA13.out --> vl_pcf_in_BUFCA13.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS14.out --> vl_pcf_in_BUFCS14.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN14.out --> vl_pcf_in_BUFIN14.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA14.out --> vl_pcf_in_BUFCA14.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS15.out --> vl_pcf_in_BUFCS15.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN15.out --> vl_pcf_in_BUFIN15.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA15.out --> vl_pcf_in_BUFCA15.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS16.out --> vl_pcf_in_BUFCS16.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN16.out --> vl_pcf_in_BUFIN16.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA16.out --> vl_pcf_in_BUFCA16.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS17.out --> vl_pcf_in_BUFCS17.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN17.out --> vl_pcf_in_BUFIN17.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA17.out --> vl_pcf_in_BUFCA17.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS18.out --> vl_pcf_in_BUFCS18.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN18.out --> vl_pcf_in_BUFIN18.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA18.out --> vl_pcf_in_BUFCA18.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS19.out --> vl_pcf_in_BUFCS19.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN19.out --> vl_pcf_in_BUFIN19.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA19.out --> vl_pcf_in_BUFCA19.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;

        vl_pcf_in_CS20.out --> vl_pcf_in_BUFCS20.in;
        //vl_pcf_out_CS.out --> vl_pcf_out_BUFCS.in;

        vl_pcf_in_IN20.out --> vl_pcf_in_BUFIN20.in;
        //vl_pcf_out_IN.out --> vl_pcf_out_BUFIN.in;

        vl_pcf_in_CA20.out --> vl_pcf_in_BUFCA20.in;
        //vl_pcf_out_CA.out --> vl_pcf_out_BUFCA.in;


}
