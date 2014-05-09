package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;

module Node_6 extends TTEAVBEtherHost
{
    submodules:
        vl_211_ctc: TTIncoming {
            @display("p=508,37");
        }
        vl_211: TTDoubleBuffer {
            @display("p=604,37");
        }
        vl_221_ctc: TTIncoming {
            @display("p=508,37");
        }
        vl_221: TTDoubleBuffer {
            @display("p=604,37");
        }
    connections:
        vl_211_ctc.out --> vl_211.in;
        vl_221_ctc.out --> vl_221.in;
}