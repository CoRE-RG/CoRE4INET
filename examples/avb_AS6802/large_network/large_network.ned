package core4inet.examples.avb_AS6802.large_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;

network large_network
{
    @display("bgb=909,415;bgl=5");
    types:
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 200ns;
        }

    submodules:
        switch_1: Switch_1 {
            @display("p=231,197");
            gates:
                ethg[5];
        }
        switch_2: Switch_2 {
            @display("p=367,197");
            gates:
                ethg[5];
        }
        switch_3: Switch_3 {
            @display("p=500,197");
            gates:
                ethg[4];
        }

        node_1: TTEAVBEtherHost {
            @display("p=43,109");
        }
        node_2: TTEAVBEtherHost {
            @display("p=43,182");
        }
        node_3: Node_3 {
            @display("p=43,257");
        }
        node_4: Node_4 {
            @display("p=43,323");
        }
        node_5: Node_5 {
            @display("p=270,323");
        }
        node_6: Node_6 {
            @display("p=367,323");
        }
        node_7: Node_7 {
            @display("p=461,323");
        }
        node_8: TTEAVBEtherHost {
            @display("p=643,109");
        }
        node_9: Node_9 {
            @display("p=643,197");
        }
        node_10: TTEAVBEtherHost {
            @display("p=643,323");
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
