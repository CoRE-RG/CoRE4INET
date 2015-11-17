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

import core4inet.linklayer.inControl.IEEE8021Q.IEEE8021Q_InControl;
import core4inet.linklayer.shaper.IEEE8021Q_Shaper;

import inet.linklayer.ethernet.EtherMACFullDuplex;

//
// The IEEE8021QPHYPort is a compund module that contains the input Shaper, output Shaper and MAC (EtherMACFullDuplex)
// It represents a physical port for a IEEE 802.1Q Ethernet device (Switch or Host)
//
// @see ~EtherMACFullDuplex, ~IEEE8021Q_Shaper, ~BE_Shaper, ~BE_InControl
//
// @author Philipp Meyer
//
module IEEE8021QPHYPort
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
        //Input from the upper layer for best-effort Traffic
        input upperLayerIn @loose @labels(EtherFrame);
        //Output to the upper layer for best-effort Traffic
        output upperLayerOut @loose @labels(EtherFrame);
        //Connection to the physical layer
        inout phys @labels(EtherFrame);

    submodules:
        //Module for the organisation of outbound traffic
        shaper: IEEE8021Q_Shaper {
            @display("p=48,45");
            untaggedVID = untaggedVID;
            taggedVIDs = taggedVIDs;
        }
        
        //Module for the organisation of inbound traffic
        inControl: IEEE8021Q_InControl {
            parameters:
                @display("p=142,45");
                promiscuous = promiscuous;
                untaggedVID = untaggedVID;
            	taggedVIDs = taggedVIDs;
        }
        
        //MAC interface
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
        inControl.in <-- mac.upperLayerOut;
        phys <--> mac.phys;
}
