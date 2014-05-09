package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;


module Switch_3 extends TTEAVBEtherSwitch
{
    submodules:
        vl_210_ctc: TTIncoming {
            @display("p=539,37");
        }
        vl_210: TTDoubleBuffer {
            @display("p=647,37");
        }
        vl_211_ctc: TTIncoming {
            @display("p=721,37");
        }
        vl_211: TTDoubleBuffer {
            @display("p=829,37");
        }
        vl_220_ctc: TTIncoming {
            @display("p=539,127");
        }
        vl_220: TTDoubleBuffer {
            @display("p=647,127");
        }
        vl_221_ctc: TTIncoming {
            @display("p=721,127");
        }
        vl_221: TTDoubleBuffer {
            @display("p=829,127");
        }
    connections:
        vl_210_ctc.out --> vl_210.in;
        vl_211_ctc.out --> vl_211.in;
        vl_220_ctc.out --> vl_220.in;
        vl_221_ctc.out --> vl_221.in;
}
