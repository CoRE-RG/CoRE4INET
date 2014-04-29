
package core4inet.linklayer.ethernet.avb;

import inet.linklayer.ethernet.EtherLLC;

simple SRPEtherLLC extends EtherLLC
{
    parameters:
        @class(SRPEtherLLC);
        @display("i=block/fork");
    gates:
        input srpIn;
        output srpOut;
}

