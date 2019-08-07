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

package core4inet.linklayer.port;

import core4inet.linklayer.inControl.CT_AVB_8021Q_InControl;
import core4inet.linklayer.shaper.TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper;
import core4inet.linklayer.filtering.IFiltering;

import inet.linklayer.ethernet.EtherMACFullDuplex;

//
// The TTEAVBPHYPort is a compund module that contains the input Shaper, input Filtering, output Shaper and MAC (EtherMACFullDuplex)
// It represents a physical port for a real-time Ethernet device (Switch or Host)
//
// @see ~IPort, ~IFiltering, ~NoFiltering, ~EtherMACFullDuplex, ~TTEInput, ~TT_AVBClassA_PCF_RC_BE_Shaper, ~TT_PCF_RC_BE_Shaper, ~PCF_RC_BE_Shaper, ~BE_Shaper
//
// @author Philipp Meyer
//
module TTEAVBFilterPHYPort like IPort
{
    parameters:
        @display("bgb=188,180;i=device/port");

        // if true, all packets are received, otherwise only the ones with matching destination MAC address (This does not affect CT-Frames)
        bool promiscuous = default(false);
        //Module holds Interfacenames
        string interfaceTableModule;
        //Untagged VLAN. Untagged incoming frames get tagged with this VLAN. Outgoing frames with this VLAN get untagged
        int untaggedVID = default(0);
        //Interface allows frames with this VLAN to enter and leave the port
        string taggedVIDs = default("0");

        *.interfaceTableModule = default(absPath(interfaceTableModule));

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
		//Input from the upper layer for audio-video bridging SR-Class A traffic
        input AVBAin @directIn @labels(AVBFrame);
        //Input from the upper layer for audio-video bridging SR-Class B traffic
        input AVBBin @directIn @labels(AVBFrame);

    submodules:
        shaper: TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper {
            @display("p=48,45");
            untaggedVID = untaggedVID;
            taggedVIDs = taggedVIDs;
        }

        inControl: CT_AVB_8021Q_InControl {
            parameters:
                @display("p=142,45");
                promiscuous = promiscuous;
                untaggedVID = untaggedVID;
                taggedVIDs = taggedVIDs;
        }

        filtering: <default("NoFiltering")> like IFiltering {
            @display("p=141.44,90.24");
        }

        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true;
                queueModule = "^.shaper";
                @display("p=87,139");
        }

    connections:
        upperLayerIn --> shaper.in;
        upperLayerOut <-- inControl.out;
        shaper.out --> mac.upperLayerIn;
        inControl.in <-- filtering.out;
        filtering.in <-- mac.upperLayerOut;
        phys <--> mac.phys;

        TTin --> shaper.TTin;
        RCin --> shaper.RCin;
        PCFin --> shaper.PCFin;
        AVBAin --> shaper.AVBAin;
        AVBBin --> shaper.AVBBin;
}
