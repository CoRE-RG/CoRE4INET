package ttethernet.linklayer;


import inet.linklayer.IEtherMAC;
import inet.linklayer.ethernet.EtherMACFullDuplex;

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
        // if true, all packets are received, otherwise only the ones with matching destination MAC address (This does not affect CT-Frames)
        bool promiscuous = default(false);
    gates:
        //Input from the upper layer for best-effort Traffic
        input upperLayerIn @loose @labels(EtherFrame);
        //Output to the upper layer for best-effort Traffic
        output upperLayerOut @loose @labels(EtherFrame);
        //Connection to the physical layer
        inout phys @labels(EtherFrame);
        //Input from the upper layer for time-triggered traffic
        input TTin @directIn @labels(TTFrame);
        //Input from the upper layer for rate-constrained traffic
        input RCin @directIn @labels(RCFrame);
        //Input from the upper layer for rate-constrained traffic
        input PCFin @directIn @labels(PCFrame);

    submodules:
        //Module for the organisation of outbound traffic
        tteOutput: TTEOutput {
            @display("p=48,45");
        }
        //Module for the organisation of inbound traffic
        tteInput: TTEInput {
            parameters:
                @display("p=142,45");
                promiscuous = promiscuous;
        }
        //MAC interface
        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true; //MAC must be set promiscuous to allow for CT receiption with all CT-Markers
                queueModule = "tteOutput";//The tteOutput-Module(TTEOutput) is used as external queue for the interface
                @display("p=78,142");
        }
    connections:
        upperLayerIn --> tteOutput.in;
        upperLayerOut <-- tteInput.out;
        tteOutput.out --> mac.upperLayerIn;
        tteInput.in <-- mac.upperLayerOut;
        phys <--> mac.phys;

        TTin --> tteOutput.TTin;
        RCin --> tteOutput.RCin;
        PCFin --> tteOutput.PCFin;
}
