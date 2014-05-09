package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;

module Node_3 extends TTEAVBEtherHost
{
	submodules:
        vl_212_ctc: TTIncoming {
            @display("p=508,37");
        }
        vl_212: TTDoubleBuffer {
            @display("p=604,37");
        }
        vl_222_ctc: TTIncoming {
            @display("p=508,37");
        }
        vl_222: TTDoubleBuffer {
            @display("p=604,37");
        }
    connections:
        vl_212_ctc.out --> vl_212.in;
        vl_222_ctc.out --> vl_222.in;
}