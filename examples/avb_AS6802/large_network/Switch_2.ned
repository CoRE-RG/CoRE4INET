package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;

module Switch_2 extends TTEAVBEtherSwitch
{
    submodules:
        vl_210_ctc: TTIncoming {
            @display("p=508,37");
        }
        vl_210: TTDoubleBuffer {
            @display("p=604,37");
        }
        vl_211_ctc: TTIncoming {
            @display("p=683,302");
        }
        vl_211: TTDoubleBuffer {
            @display("p=772,302");
        }
        vl_212_ctc: TTIncoming {
            @display("p=508,302");
        }
        vl_212: TTDoubleBuffer {
            @display("p=604,302");
        }
        vl_213_ctc: TTIncoming {
            @display("p=683,212");
        }
        vl_213: TTDoubleBuffer {
            @display("p=772,212");
        }
        vl_220_ctc: TTIncoming {
            @display("p=508,212");
        }
        vl_220: TTDoubleBuffer {
            @display("p=604,212");
        }
        vl_221_ctc: TTIncoming {
            @display("p=683,37");
        }
        vl_221: TTDoubleBuffer {
            @display("p=772,37");
        }
        vl_222_ctc: TTIncoming {
            @display("p=508,127");
        }
        vl_222: TTDoubleBuffer {
            @display("p=604,127");
        }
        vl_223_ctc: TTIncoming {
            @display("p=683,127");
        }
        vl_223: TTDoubleBuffer {
            @display("p=772,127");
        }
    connections:
        vl_210_ctc.out --> vl_210.in;
        vl_211_ctc.out --> vl_211.in;
        vl_212_ctc.out --> vl_212.in;
        vl_213_ctc.out --> vl_213.in;
        vl_220_ctc.out --> vl_220.in;
        vl_221_ctc.out --> vl_221.in;
        vl_222_ctc.out --> vl_222.in;
        vl_223_ctc.out --> vl_223.in;
}
