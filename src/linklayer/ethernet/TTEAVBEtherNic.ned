//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package core4inet.linklayer.ethernet;

import core4inet.linklayer.ethernet.avb.SRPEtherEncap;
import core4inet.linklayer.inControl.CT_AVB_BE_InControl;
import core4inet.linklayer.shaper.TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper;
import inet.linklayer.ethernet.EtherMACFullDuplex;

import inet.linklayer.INic;


//
// Module for a TTE AVB BE Ethernet NIC
// Contains handler for TT, AVB, RC and BE Messages.
//
// @todo Kommentar
//
// @see SRPEtherEncap, TTEAVBPHYPort, Sync, Scheduler
//
// @author Kai-Uwe von Deylen
module TTEAVBEtherNic like INic
{
    parameters:
        @display("i=block/ifcard");
        double hardware_delay @unit(s) = default(0us);
        bool promiscuous = default(true); // TODO: sinnvoller default
    gates:

        // Connection to the physical ethernet gate
        inout ethg;

        // best effort input from upper layer 
        input upperLayerIn;

        // best effort output to upper layer
        output upperLayerOut;
        
        // background (BE) traffic input
        input bgIn;
        
        // background (BE) traffic out
        output bgOut;

        // time-triggered traffic input from upper layer
        input TTin @directIn @labels(TTFrame);

        // rate-constrained traffic input from upper layer
        input RCin @directIn @labels(RCFrame);

		// audio-video bridging class A traffic from upper layer
        input AVBAin @directIn @labels(AVBFrame);

		// audio-video bridging class B traffic from upper layer
        input AVBBin @directIn @labels(AVBFrame);

        // rate-constrained Protocol-Control-Frame traffic from upper layer
        input PCFin @directIn @labels(PCFrame);
        
        // stream reservation protocol input
        input srpIn;
        
        // stream reservation protocol output
        output srpOut;

    submodules:

        shaper: TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper {
            @display("p=88,75");
        }

        inControl: CT_AVB_BE_InControl {
            parameters:
                @display("p=166,144");
                promiscuous = promiscuous;
        }

        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true;
                queueModule = "shaper";
                @display("p=127,227");
        }

        encap: SRPEtherEncap {
            parameters:
                @display("p=166,75");
        }

    connections:

        mac.phys <--> ethg;

        mac.upperLayerIn <-- shaper.out;
        mac.upperLayerOut --> inControl.in;

        inControl.out --> encap.lowerLayerIn;

        shaper.in <-- encap.lowerLayerOut;
        shaper.AVBAin <-- AVBAin;
        shaper.AVBBin <-- AVBBin;
        shaper.PCFin <-- PCFin;
        shaper.RCin <-- RCin;
        shaper.TTin <-- TTin;

        srpIn --> encap.srpIn;
        srpOut <-- encap.srpOut;

        encap.upperLayerOut --> upperLayerOut;
        upperLayerIn --> encap.upperLayerIn;
        encap.bgOut --> bgOut;
        bgIn --> encap.bgIn;
}
