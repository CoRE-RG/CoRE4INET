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

package core4inet.linklayer.shaper.IEEE8021Qbv.queueing;

//
// Interface to be implemented by IEEE 802.1Qbv queueing modules.
//
// @warning Since this is an abstract module please do not instantiate it!
//
// @see ~IEEE8021QbvQueueing
//
// @author Philipp Meyer
//
moduleinterface IIEEE8021QbvQueueing {
    
    parameters:
        @display("i=block/fork");
        // Number of priorities.
        int numPCP;
        //Untagged VLAN. Outgoing frames with this VLAN get untagged
        int untaggedVID;
        //Interface allows frames with this VLAN to leave the port
        string taggedVIDs;   
        
    gates:
        // Input for incoming inet::EtherFrame messages.
        input in @labels(EtherFrame);
        // Ouput to the corresponding queues.
        output out[numPCP] @labels(EtherFrame);
}