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

import core4inet.linklayer.inControl.AVB_8021Q_InControl;
import core4inet.linklayer.shaper.IEEE8021Qbv_Shaper;
import core4inet.linklayer.filtering.IFiltering;
import core4inet.linklayer.manipulation.IManipulator;

import inet.linklayer.ethernet.EtherMACFullDuplex;

//
// The IEEE8021QbvPHYPort is a compund module that contains the input Shaper, output Shaper and MAC (EtherMACFullDuplex)
// It represents a physical port for a IEEE 802.1Q Ethernet device (Switch or Host) with Qbv shaping
//
// @see ~EtherMACFullDuplex, ~IEEE8021Qbv_Shaper, ~BE_Shaper, ~BE_InControl
//
// @author Philipp Meyer
//
module CorruptedTSNPHYPort
{
    parameters:
        @display("bgb=188,180;i=device/port");

        // if true, all packets are received, otherwise only the ones with matching destination MAC address
        bool promiscuous = default(false);
        //Static propagation delay for the port
        double static_tx_delay @unit(s) = default(0ns);
        //Module holds Interfacenames
        string interfaceTableModule;
        //Untagged VLAN. Untagged incoming frames get tagged with this VLAN. Outgoing frames with this VLAN get untagged
        int untaggedVID = default(0);
        //Interface allows frames with this VLAN to enter and leave the port
        string taggedVIDs = default("0");

        *.interfaceTableModule = default(absPath(interfaceTableModule));

    gates:
        //Input from the upper layer
        input upperLayerIn @loose @labels(EtherFrame);
        //Output to the upper layer
        output upperLayerOut @loose @labels(EtherFrame);
        //Direct input from the upper layer
        input upperLayerDirectIn @directIn @labels(EtherFrame);
        //Connection to the physical layer
        inout phys @labels(EtherFrame);

    submodules:
        //Module for the organisation of outbound traffic
        shaper: IEEE8021Qbv_Shaper {
            @display("p=48,45");
            untaggedVID = untaggedVID;
            taggedVIDs = taggedVIDs;
        }

        //Module for the organisation of inbound traffic
        inControl: AVB_8021Q_InControl {
            parameters:
                @display("p=142,45");
                promiscuous = promiscuous;
                untaggedVID = untaggedVID;
                taggedVIDs = taggedVIDs;
        }

        filtering: <default("NoFiltering")> like IFiltering {
            @display("p=141.44,90.24");
        }

        outputManipulator: <default("NoManipulation")> like IManipulator {
            parameters:
                @display("p=48,90.24");
        }

        //MAC interface
        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true;
                queueModule = "^.shaper.transmissionSelection";
                @display("p=87,139");
        }

    connections:
        upperLayerIn --> shaper.in;
        upperLayerDirectIn --> shaper.inD;
        upperLayerOut <-- inControl.out;
        shaper.out --> outputManipulator.in;
        outputManipulator.out --> mac.upperLayerIn;
        inControl.in <-- filtering.out;
        filtering.in <-- mac.upperLayerOut;
        phys <--> mac.phys;
}
