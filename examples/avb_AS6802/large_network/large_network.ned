package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import core4inet.nodes.ethernet.avb_AS6802.CorruptedTTEAVBEtherHost;

network large_network
{
    @display("bgb=685,299;bgi=background/avb_AS6802_large_network,s");
    types:
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 200ns;
        }

    submodules:
        switch_1: Switch_1 {
            @display("p=228,123");
            gates:
                ethg[5];
        }
        switch_2: Switch_2 {
            @display("p=364,123");
            gates:
                ethg[5];
        }
        switch_3: Switch_3 {
            @display("p=497,123");
            gates:
                ethg[4];
        }

        node_1: CorruptedTTEAVBEtherHost {
            @display("p=40,35");
        }
        node_2: TTEAVBEtherHost {
            @display("p=40,108");
        }
        node_3: Node_3 {
            @display("p=40,183");
        }
        node_4: Node_4 {
            @display("p=40,249");
        }
        node_5: Node_5 {
            @display("p=267,249");
        }
        node_6: Node_6 {
            @display("p=364,249");
        }
        node_7: Node_7 {
            @display("p=458,249");
        }
        node_8: TTEAVBEtherHost {
            @display("p=640,35");
        }
        node_9: Node_9 {
            @display("p=640,123");
        }
        node_10: TTEAVBEtherHost {
            @display("p=640,249");
        }

    connections:
        switch_1.ethg[0] <--> cable <--> switch_2.ethg[0];
        switch_2.ethg[1] <--> cable <--> switch_3.ethg[0];

        node_1.ethg <--> cable <--> switch_1.ethg[1];
        node_2.ethg <--> cable <--> switch_1.ethg[2];
        node_3.ethg <--> cable <--> switch_1.ethg[3];
        node_4.ethg <--> cable <--> switch_1.ethg[4];

        node_5.ethg <--> cable <--> switch_2.ethg[2];
        node_6.ethg <--> cable <--> switch_2.ethg[3];
        node_7.ethg <--> cable <--> switch_2.ethg[4];

        node_8.ethg <--> cable <--> switch_3.ethg[1];
        node_9.ethg <--> cable <--> switch_3.ethg[2];
        node_10.ethg <--> cable <--> switch_3.ethg[3];
}
