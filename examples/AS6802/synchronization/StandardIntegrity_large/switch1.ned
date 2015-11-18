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
module Switch1 extends TTEEtherSwitch
{
    @display("bgb=1360,797");
    submodules:


        pcf_out[3]: PCFIncoming {
            parameters:
                @display("p=1118,561;is=s");
        }

        //}
        vl_pcf_out_BUFIN: RCQueueBuffer {
            parameters:
                @display("p=1269,479;is=s");
        }

        //}
        vl_pcf_out_BUFCS: RCQueueBuffer {
            parameters:
                @display("p=1118,479;is=s");
        }


        //}
        vl_pcf_out_BUFCA: RCQueueBuffer {
            parameters:
                @display("p=1269,561;is=s");
        }

      //a port that is connected to other compression master need a special handle to reduce cycle dependecy   

         //IN FRAMES
        vl_pcf_in_IN4: RCIncoming {
            parameters:
                @display("p=362,585;is=s");
        }
        vl_pcf_in_BUFIN4: RCQueueBuffer {
            parameters:
                @display("p=491,585;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS4: RCIncoming {
            parameters:
                @display("p=356,542;is=s");
        }
        vl_pcf_in_BUFCS4: RCQueueBuffer {
            parameters:
                @display("p=485,542;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA4: RCIncoming {
            parameters:
                @display("p=362,623;is=s");
        }
        vl_pcf_in_BUFCA4: RCQueueBuffer {
            parameters:
                @display("p=491,623;is=s");
        }
        //for compressed frames stems  from other compression master--------------------
        vl_pcf_in_BUFCAcomp: RCQueueBuffer {
            parameters:
                @display("p=1256,652;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCScomp: RCQueueBuffer {
            parameters:
                @display("p=1256,699;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFINcomp: RCQueueBuffer {
            parameters:
                @display("p=1256,600;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CAcomp: RCIncoming {
            parameters:
                @display("p=1118,668;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CScomp: RCIncoming {
            parameters:
                @display("p=1118,719;is=s");
        }
        //IN FRAMES
        vl_pcf_in_INcomp: RCIncoming {
            parameters:
                @display("p=1118,607;is=s");
        }

      //  --------------------------------

        vl_pcf_in_BUFCA1: RCQueueBuffer {
            parameters:
                @display("p=485,456;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS1: RCQueueBuffer {
            parameters:
                @display("p=485,495;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFIN1: RCQueueBuffer {
            parameters:
                @display("p=485,418;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA1: RCIncoming {
            parameters:
                @display("p=368,456;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS1: RCIncoming {
            parameters:
                @display("p=368,495;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN1: RCIncoming {
            parameters:
                @display("p=368,418;is=s");
        }
        vl_pcf_in_BUFCA7: RCQueueBuffer {
            parameters:
                @display("p=724,618;is=s");
        }
        vl_pcf_in_BUFCS7: RCQueueBuffer {
            parameters:
                @display("p=718,537;is=s");
        }
        vl_pcf_in_BUFIN7: RCQueueBuffer {
            parameters:
                @display("p=724,580;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA7: RCIncoming {
            parameters:
                @display("p=607,618;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS7: RCIncoming {
            parameters:
                @display("p=601,537;is=s");
        }
        vl_pcf_in_IN7: RCIncoming {
            parameters:
                @display("p=607,580;is=s");
        }
        vl_pcf_in_BUFCA5: RCQueueBuffer {
            parameters:
                @display("p=485,753;is=s");
        }
        vl_pcf_in_BUFCS5: RCQueueBuffer {
            parameters:
                @display("p=485,669;is=s");
        }
        vl_pcf_in_BUFIN5: RCQueueBuffer {
            parameters:
                @display("p=485,709;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA5: RCIncoming {
            parameters:
                @display("p=368,753;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS5: RCIncoming {
            parameters:
                @display("p=368,669;is=s");
        }
        vl_pcf_in_IN5: RCIncoming {
            parameters:
                @display("p=368,709;is=s");
        }
        vl_pcf_in_BUFCA6: RCQueueBuffer {
            parameters:
                @display("p=730,746;is=s");
        }
        vl_pcf_in_BUFCS6: RCQueueBuffer {
            parameters:
                @display("p=730,663;is=s");
        }
        vl_pcf_in_BUFIN6: RCQueueBuffer {
            parameters:
                @display("p=730,702;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA6: RCIncoming {
            parameters:
                @display("p=601,746;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS6: RCIncoming {
            parameters:
                @display("p=601,663;is=s");
        }
        vl_pcf_in_IN6: RCIncoming {
            parameters:
                @display("p=601,702;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS3: RCIncoming {
            parameters:
                @display("p=601,501;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA3: RCIncoming {
            parameters:
                @display("p=601,462;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN3: RCIncoming {
            parameters:
                @display("p=601,418;is=s");
        }
        vl_pcf_in_BUFIN3: RCQueueBuffer {
            parameters:
                @display("p=718,418;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        vl_pcf_in_BUFCA3: RCQueueBuffer {
            parameters:
                @display("p=718,462;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS3: RCQueueBuffer {
            parameters:
                @display("p=718,501;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFCA21: RCQueueBuffer {
            parameters:
                @display("p=1194,119;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS21: RCQueueBuffer {
            parameters:
                @display("p=1194,192;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFIN21: RCQueueBuffer {
            parameters:
                @display("p=1194,49;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA21: RCIncoming {
            parameters:
                @display("p=1077,119;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS21: RCIncoming {
            parameters:
                @display("p=1077,192;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN21: RCIncoming {
            parameters:
                @display("p=1077,49;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN8: RCIncoming {
            parameters:
                @display("p=839,425;is=s");
        }
        vl_pcf_in_BUFIN8: RCQueueBuffer {
            parameters:
                @display("p=956,425;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA8: RCIncoming {
            parameters:
                @display("p=839,467;is=s");
        }
        vl_pcf_in_BUFCA8: RCQueueBuffer {
            parameters:
                @display("p=956,467;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CS FRAMES
        vl_pcf_in_CS8: RCIncoming {
            parameters:
                @display("p=839,501;is=s");
        }
        vl_pcf_in_BUFCS8: RCQueueBuffer {
            parameters:
                @display("p=956,501;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        //IN FRAMES
        vl_pcf_in_IN9: RCIncoming {
            parameters:
                @display("p=839,549;is=s");
        }
        vl_pcf_in_BUFIN9: RCQueueBuffer {
            parameters:
                @display("p=956,549;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA9: RCIncoming {
            parameters:
                @display("p=839,588;is=s");
        }
        vl_pcf_in_BUFCA9: RCQueueBuffer {
            parameters:
                @display("p=956,588;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CS FRAMES
        vl_pcf_in_CS9: RCIncoming {
            parameters:
                @display("p=839,628;is=s");
        }
        vl_pcf_in_BUFCS9: RCQueueBuffer {
            parameters:
                @display("p=956,628;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        //IN FRAMES
        vl_pcf_in_IN10: RCIncoming {
            parameters:
                @display("p=839,679;is=s");
        }
        vl_pcf_in_BUFIN10: RCQueueBuffer {
            parameters:
                @display("p=956,679;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA10: RCIncoming {
            parameters:
                @display("p=839,728;is=s");
        }
        vl_pcf_in_BUFCA10: RCQueueBuffer {
            parameters:
                @display("p=956,728;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CS FRAMES
        vl_pcf_in_CS10: RCIncoming {
            parameters:
                @display("p=839,766;is=s");
        }
        vl_pcf_in_BUFCS10: RCQueueBuffer {
            parameters:
                @display("p=956,766;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        //IN FRAMES
        vl_pcf_in_IN11: RCIncoming {
            parameters:
                @display("p=362,284;is=s");
        }
        vl_pcf_in_BUFIN11: RCQueueBuffer {
            parameters:
                @display("p=479,284;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        vl_pcf_in_BUFCA11: RCQueueBuffer {
            parameters:
                @display("p=479,333;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CA FRAMES
        vl_pcf_in_CA11: RCIncoming {
            parameters:
                @display("p=362,333;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS11: RCIncoming {
            parameters:
                @display("p=362,371;is=s");
        }
        vl_pcf_in_BUFCS11: RCQueueBuffer {
            parameters:
                @display("p=479,371;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        //CS FRAMES
        vl_pcf_in_CS12: RCIncoming {
            parameters:
                @display("p=362,242;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA12: RCIncoming {
            parameters:
                @display("p=362,204;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN12: RCIncoming {
            parameters:
                @display("p=362,155;is=s");
        }
        vl_pcf_in_BUFIN12: RCQueueBuffer {
            parameters:
                @display("p=479,155;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        vl_pcf_in_BUFCA12: RCQueueBuffer {
            parameters:
                @display("p=479,204;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS12: RCQueueBuffer {
            parameters:
                @display("p=479,242;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        //IN FRAMES
        vl_pcf_in_IN13: RCIncoming {
            parameters:
                @display("p=362,29;is=s");
        }
        vl_pcf_in_BUFIN13: RCQueueBuffer {
            parameters:
                @display("p=479,29;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA13: RCIncoming {
            parameters:
                @display("p=362,78;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS13: RCIncoming {
            parameters:
                @display("p=362,116;is=s");
        }
        vl_pcf_in_BUFCS13: RCQueueBuffer {
            parameters:
                @display("p=479,116;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFCA13: RCQueueBuffer {
            parameters:
                @display("p=479,78;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //IN FRAMES
        vl_pcf_in_IN14: RCIncoming {
            parameters:
                @display("p=557,29;is=s");
        }
        vl_pcf_in_BUFIN14: RCQueueBuffer {
            parameters:
                @display("p=674,29;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA14: RCIncoming {
            parameters:
                @display("p=557,78;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS14: RCIncoming {
            parameters:
                @display("p=557,116;is=s");
        }
        vl_pcf_in_BUFCS14: RCQueueBuffer {
            parameters:
                @display("p=674,116;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFCA14: RCQueueBuffer {
            parameters:
                @display("p=674,78;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //IN FRAMES
        vl_pcf_in_IN15: RCIncoming {
            parameters:
                @display("p=563,178;is=s");
        }
        vl_pcf_in_BUFIN15: RCQueueBuffer {
            parameters:
                @display("p=680,178;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA15: RCIncoming {
            parameters:
                @display("p=563,227;is=s");
        }
        vl_pcf_in_BUFCA15: RCQueueBuffer {
            parameters:
                @display("p=680,227;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CS FRAMES
        vl_pcf_in_CS15: RCIncoming {
            parameters:
                @display("p=563,265;is=s");
        }
        vl_pcf_in_BUFCS15: RCQueueBuffer {
            parameters:
                @display("p=680,265;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFIN16: RCQueueBuffer {
            parameters:
                @display("p=697,299;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //IN FRAMES
        vl_pcf_in_IN16: RCIncoming {
            parameters:
                @display("p=580,299;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA16: RCIncoming {
            parameters:
                @display("p=580,348;is=s");
        }
        vl_pcf_in_BUFCA16: RCQueueBuffer {
            parameters:
                @display("p=697,348;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFCS16: RCQueueBuffer {
            parameters:
                @display("p=697,386;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        //CS FRAMES
        vl_pcf_in_CS16: RCIncoming {
            parameters:
                @display("p=580,386;is=s");
        }
        //IN FRAMES
        vl_pcf_in_IN17: RCIncoming {
            parameters:
                @display("p=774,34;is=s");
        }
        //CA FRAMES
        vl_pcf_in_CA17: RCIncoming {
            parameters:
                @display("p=774,83;is=s");
        }
        //CS FRAMES
        vl_pcf_in_CS17: RCIncoming {
            parameters:
                @display("p=774,121;is=s");
        }
        vl_pcf_in_BUFCS17: RCQueueBuffer {
            parameters:
                @display("p=891,121;is=s");
        }
        //vl_pcf_out_CS: RCIncoming {
          //  parameters:
            //    @display("p=589,122");
        vl_pcf_in_BUFCA17: RCQueueBuffer {
            parameters:
                @display("p=891,83;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        vl_pcf_in_BUFIN17: RCQueueBuffer {
            parameters:
                @display("p=891,34;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");

        //IN FRAMES
        vl_pcf_in_IN18: RCIncoming {
            parameters:
                @display("p=780,178;is=s");
        }
        vl_pcf_in_BUFIN18: RCQueueBuffer {
            parameters:
                @display("p=897,178;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA18: RCIncoming {
            parameters:
                @display("p=780,227;is=s");
        }
        vl_pcf_in_BUFCA18: RCQueueBuffer {
            parameters:
                @display("p=897,227;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CS FRAMES
        vl_pcf_in_CS18: RCIncoming {
            parameters:
                @display("p=780,265;is=s");
        }
        vl_pcf_in_BUFCS18: RCQueueBuffer {
            parameters:
                @display("p=897,265;is=s");
        }


         //IN FRAMES
        vl_pcf_in_IN19: RCIncoming {
            parameters:
                @display("p=1077,261;is=s");
        }
        vl_pcf_in_BUFIN19: RCQueueBuffer {
            parameters:
                @display("p=1194,261;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA19: RCIncoming {
            parameters:
                @display("p=1077,310;is=s");
        }
        vl_pcf_in_BUFCA19: RCQueueBuffer {
            parameters:
                @display("p=1194,310;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CS FRAMES
        vl_pcf_in_CS19: RCIncoming {
            parameters:
                @display("p=1077,348;is=s");
        }
        vl_pcf_in_BUFCS19: RCQueueBuffer {
            parameters:
                @display("p=1194,348;is=s");
        }


         //IN FRAMES
        vl_pcf_in_IN20: RCIncoming {
            parameters:
                @display("p=797,307;is=s");
        }
        vl_pcf_in_BUFIN20: RCQueueBuffer {
            parameters:
                @display("p=914,307;is=s");
        }
        //vl_pcf_out_IN: RCIncoming {
          //  parameters:
            //    @display("p=349,122");
        //CA FRAMES
        vl_pcf_in_CA20: RCIncoming {
            parameters:
                @display("p=797,356;is=s");
        }
        vl_pcf_in_BUFCA20: RCQueueBuffer {
            parameters:
                @display("p=914,356;is=s");
        }
        //vl_pcf_out_CA: RCIncoming {
          //  parameters:
            //    @display("p=349,271");
        //CS FRAMES
        vl_pcf_in_CS20: RCIncoming {
            parameters:
                @display("p=797,394;is=s");
        }
        vl_pcf_in_BUFCS20: RCQueueBuffer {
            parameters:
                @display("p=914,394;is=s");
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


        vl_pcf_in_CA21.out --> vl_pcf_in_BUFCA21.in;

        vl_pcf_in_CS21.out --> vl_pcf_in_BUFCS21.in;

        vl_pcf_in_IN21.out --> vl_pcf_in_BUFIN21.in;


        vl_pcf_in_CS8.out --> vl_pcf_in_BUFCS8.in;

        vl_pcf_in_CA8.out --> vl_pcf_in_BUFCA8.in;

        vl_pcf_in_IN8.out --> vl_pcf_in_BUFIN8.in;


        vl_pcf_in_CS9.out --> vl_pcf_in_BUFCS9.in;

        vl_pcf_in_CA9.out --> vl_pcf_in_BUFCA9.in;

        vl_pcf_in_IN9.out --> vl_pcf_in_BUFIN9.in;


        vl_pcf_in_CS10.out --> vl_pcf_in_BUFCS10.in;

        vl_pcf_in_CA10.out --> vl_pcf_in_BUFCA10.in;

        vl_pcf_in_IN10.out --> vl_pcf_in_BUFIN10.in;


        vl_pcf_in_CS11.out --> vl_pcf_in_BUFCS11.in;

        vl_pcf_in_CA11.out --> vl_pcf_in_BUFCA11.in;

        vl_pcf_in_IN11.out --> vl_pcf_in_BUFIN11.in;


        vl_pcf_in_CS12.out --> vl_pcf_in_BUFCS12.in;

        vl_pcf_in_CA12.out --> vl_pcf_in_BUFCA12.in;

        vl_pcf_in_IN12.out --> vl_pcf_in_BUFIN12.in;


        vl_pcf_in_CS13.out --> vl_pcf_in_BUFCS13.in;

        vl_pcf_in_CA13.out --> vl_pcf_in_BUFCA13.in;

        vl_pcf_in_IN13.out --> vl_pcf_in_BUFIN13.in;


        vl_pcf_in_CS14.out --> vl_pcf_in_BUFCS14.in;

        vl_pcf_in_CA14.out --> vl_pcf_in_BUFCA14.in;

        vl_pcf_in_IN14.out --> vl_pcf_in_BUFIN14.in;


        vl_pcf_in_CS15.out --> vl_pcf_in_BUFCS15.in;

        vl_pcf_in_CA15.out --> vl_pcf_in_BUFCA15.in;

        vl_pcf_in_IN15.out --> vl_pcf_in_BUFIN15.in;


        vl_pcf_in_CS16.out --> vl_pcf_in_BUFCS16.in;

        vl_pcf_in_CA16.out --> vl_pcf_in_BUFCA16.in;

        vl_pcf_in_IN16.out --> vl_pcf_in_BUFIN16.in;


        vl_pcf_in_CS17.out --> vl_pcf_in_BUFCS17.in;

        vl_pcf_in_CA17.out --> vl_pcf_in_BUFCA17.in;

        vl_pcf_in_IN17.out --> vl_pcf_in_BUFIN17.in;


        vl_pcf_in_CS18.out --> vl_pcf_in_BUFCS18.in;

        vl_pcf_in_CA18.out --> vl_pcf_in_BUFCA18.in;

        vl_pcf_in_IN18.out --> vl_pcf_in_BUFIN18.in;

        vl_pcf_in_CS19.out --> vl_pcf_in_BUFCS19.in;

        vl_pcf_in_CA19.out --> vl_pcf_in_BUFCA19.in;

        vl_pcf_in_IN19.out --> vl_pcf_in_BUFIN19.in;


        vl_pcf_in_CS20.out --> vl_pcf_in_BUFCS20.in;

        vl_pcf_in_CA20.out --> vl_pcf_in_BUFCA20.in;

        vl_pcf_in_IN20.out --> vl_pcf_in_BUFIN20.in;


}
