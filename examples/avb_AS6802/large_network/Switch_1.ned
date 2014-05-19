package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;

module Switch_1 extends TTEAVBEtherSwitch
{
    submodules:
        vl_212_ctc: TTIncoming {
            @display("p=553,37");
        }
        vl_212: TTDoubleBuffer {
            @display("p=657,37");
        }
        vl_213_ctc: TTIncoming {
            @display("p=744,37");
        }
        vl_213: TTDoubleBuffer {
            @display("p=848,37");
        }
        vl_222_ctc: TTIncoming {
            @display("p=553,127");
        }
        vl_222: TTDoubleBuffer {
            @display("p=657,127");
        }
        vl_223_ctc: TTIncoming {
            @display("p=744,127");
        }
        vl_223: TTDoubleBuffer {
            @display("p=848,127");
        }
    connections:
        vl_212_ctc.out --> vl_212.in;
        vl_213_ctc.out --> vl_213.in;
        vl_222_ctc.out --> vl_222.in;
        vl_223_ctc.out --> vl_223.in;
}
