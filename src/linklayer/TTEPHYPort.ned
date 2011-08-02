package ttethernet.linklayer;


import inet.linklayer.IEtherMAC;
import inet.linklayer.ethernet.EtherMACFullDuplex;
import inet.networklayer.queue.DropTailQueue;
import inet.networklayer.queue.DropTailQoSQueue;

// The TTEPHYPort is a compund module that contains the TTEOutput, TTEInput and MAC (EtherMACFullDuplex)
// It represents a physical port for a TTEthernet device (Switch or Host)
//
// @see IPort, TTEOutput, TTEInput, EtherMACFullDuplex
//
// @author Till Steinbach
module TTEPHYPort like IPort
{
    parameters:
        @display("bgb=188,180;i=device/port");
    gates:
        //Input from the upper layer for best-effort Traffic
        input upperLayerIn @loose @labels(EtherFrame);
        //Output to the upper layer for best-effort Traffic
        output upperLayerOut @loose @labels(EtherFrame);
        //Connection to the physical layer
        inout phys @labels(EtherFrame);
        //Input from the upper layer for time-triggered traffic
        input TTin @directIn @labels(CTFrame);
        //Input from the upper layer for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);

    submodules:
        //Module for the organisation of outbound traffic
        tteOutput: TTEOutput {
            @display("p=48,45");
        }
        //Module for the organisation of inbound traffic
        tteInput: TTEInput {

            @display("p=142,45");
        }
        //MAC interface
        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true; //MAC must be set promiscuous to allow for CT receiption
                queueModule = "tteOutput";//The tteOutput-Module(TTEOutput) is used as external queue for the interface
                @display("p=87,139");
        }
    connections:
        upperLayerIn --> tteOutput.in;
        upperLayerOut <-- tteInput.out;
        tteOutput.out --> mac.upperLayerIn;
        tteInput.in <-- mac.upperLayerOut;
        phys <--> mac.phys;
        
        TTin --> tteOutput.TTin;
        RCin --> tteOutput.RCin;
}
