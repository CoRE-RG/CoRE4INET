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

import core4inet.linklayer.ethernet.base.ICoRE4INETEtherNic;
import core4inet.linklayer.ethernet.avb.SRPEtherEncap;
import core4inet.linklayer.inControl.AVB_8021Q_InControl;
import core4inet.linklayer.shaper.IEEE8021Qbv_Shaper;
import core4inet.linklayer.filtering.IFiltering;
import inet.linklayer.contract.IEtherMAC;



//
// Module for a TSN Ethernet NIC
// Contains handler BG SRP and TSN.
//
// @see SRPEtherEncap, TTEAVBPHYPort, Sync, Scheduler
//
// @author Kai-Uwe von Deylen, Till Steinbach, Timo Haeckel
module TSNEtherNic like ICoRE4INETEtherNic
{
    parameters:
        @display("i=block/ifcard");
        string interfaceTableModule;
        double hardware_delay @unit(s) = default(0us);
        // if true, all packets are received, otherwise only the ones with matching destination MAC address
        bool promiscuous = default(false);
        *.interfaceTableModule = default(absPath(this.interfaceTableModule));
        //Untagged VLAN. Untagged incoming frames get tagged with this VLAN. Outgoing frames with this VLAN get untagged
        int untaggedVID = default(0);
        //Interface allows frames with this VLAN to enter and leave the port
        string taggedVIDs = default("0");
    gates:

        // Connection to the physical ethernet gate
        inout phys;

        // best effort input from upper layer 
        input upperLayerIn;

        // best effort output to upper layer
        output upperLayerOut;
        
        //Direct input from the upper layer
        input upperLayerDirectIn @directIn @labels(EtherFrame);

        // background (BE) traffic input
        input bgIn;

        // background (BE) traffic out
        output bgOut;

        // stream reservation protocol input
        input srpIn;

        // stream reservation protocol output
        output srpOut;

    submodules:

        //Module for the organisation of outbound traffic
        shaper: IEEE8021Qbv_Shaper {
            @display("p=63,120");
            untaggedVID = parent.untaggedVID;
            taggedVIDs = parent.taggedVIDs;
        }

        //Module for the organisation of inbound traffic
        inControl: AVB_8021Q_InControl {
            parameters:
                @display("p=191,120");
                promiscuous = parent.promiscuous;
                untaggedVID = parent.untaggedVID;
                taggedVIDs = parent.taggedVIDs;
        }

        filtering: <default("NoFiltering")> like IFiltering {
            @display("p=191,190");
        }

        mac: <default("EtherMACFullDuplex")> like IEtherMAC {
            parameters:
                promiscuous = true;
                queueModule = "^.shaper.transmissionSelection";
                @display("p=127,264");
        }

        encap: SRPEtherEncap {
            parameters:
                @display("p=127,60");
        }

    connections:

        mac.phys <--> phys;

        mac.upperLayerIn <-- shaper.out;
        inControl.in <-- filtering.out;
        filtering.in <-- mac.upperLayerOut;

        inControl.out --> encap.lowerLayerIn;

        shaper.in <-- encap.lowerLayerOut;
        upperLayerDirectIn --> shaper.inD;

        srpIn --> encap.srpIn;
        srpOut <-- encap.srpOut;

        encap.upperLayerOut --> upperLayerOut;
        upperLayerIn --> encap.upperLayerIn;
        encap.bgOut --> bgOut;
        bgIn --> encap.bgIn;
}
