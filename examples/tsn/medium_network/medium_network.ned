package core4inet.examples.tsn.medium_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import inet.node.ethernet.EtherLink;

network medium_network
{
parameters:
     @display("bgb=,,white");
     double measure_interval @unit(s) = default(1s);

types: 
 channel ETH_100MBIT extends EtherLink
  {
	datarate = 100000000bps;
	length = 0.0m;
	ber = 0.0;
	per = 0.0;
  }

submodules:
  node1: node1 {
    parameters: 
      @display("p=43,55");
}

  node2: node2 {
    parameters: 
      @display("p=43,111");
}

  node3: node3 {
    parameters: 
      @display("p=43,168");
}

  node4: node4 {
    parameters: 
      @display("p=43,226");
}

  node5: node5 {
    parameters: 
      @display("p=247,136");
}

  switch1: switch1 {
    parameters: 
      @display("p=147,136");
    gates:
      ethg[5];
  }

connections:
  node1.ethg <--> ETH_100MBIT <--> switch1.ethg[0];
  node2.ethg <--> ETH_100MBIT <--> switch1.ethg[1];
  node3.ethg <--> ETH_100MBIT <--> switch1.ethg[2];
  node4.ethg <--> ETH_100MBIT <--> switch1.ethg[3];
  node5.ethg <--> ETH_100MBIT <--> switch1.ethg[4];

}