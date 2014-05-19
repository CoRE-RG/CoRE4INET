package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;

module Node_5 extends TTEAVBEtherHost
{
    submodules:
        vl_210_ctc: TTIncoming {
            @display("p=508,37");
        }
        vl_210: TTDoubleBuffer {
            @display("p=604,37");
        }
        vl_220_ctc: TTIncoming {
            @display("p=508,37");
        }
        vl_220: TTDoubleBuffer {
            @display("p=604,37");
        }
    connections:
        vl_210_ctc.out --> vl_210.in;
        vl_220_ctc.out --> vl_220.in;
}