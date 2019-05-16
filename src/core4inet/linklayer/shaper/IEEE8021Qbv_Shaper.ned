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

package core4inet.linklayer.shaper;

import core4inet.linklayer.shaper.base.IShaper;
import core4inet.linklayer.shaper.IEEE8021Qbv.queueing.IIEEE8021QbvQueueing;
import core4inet.buffer.base.IBuffer;
import core4inet.linklayer.shaper.IEEE8021Qbv.selectionAlgorithm.IIEEE8021QbvSelectionAlgorithm;
import core4inet.linklayer.shaper.IEEE8021Qbv.gate.IIEEE8021QbvGate;
import core4inet.linklayer.shaper.IEEE8021Qbv.selection.IIEEE8021QbvSelection;
import core4inet.linklayer.shaper.IEEE8021Qbv.gate.IIEEE8021QbvGateControlList;

// @see ~IShaper
//
// @author Philipp Meyer

module IEEE8021Qbv_Shaper like IShaper
{
    parameters:
        @display("i=block/classifier");
        //Untagged VLAN. Outgoing frames with this VLAN get untagged
        int untaggedVID = default(0);
        //Interface allows frames with this VLAN to leave the port
        string taggedVIDs = default("0");
        // Number of priorities
        int numPCP = default(8);
        
    gates:
        input in @labels(EtherFrame);
        output out @labels(EtherFrame);
        
    submodules:
        queueing: <default("IEEE8021QbvQueueing")> like IIEEE8021QbvQueueing {
          	parameters:
             	@display("p=75,150");
             	untaggedVID = untaggedVID;
                taggedVIDs = taggedVIDs;   
             	numPCP = numPCP;
        }
        
        queue[numPCP]: <default("IEEE8021QbvQueue")> like IBuffer {
            @display("p=375,150,c,130");
        }
        
        transmissionSelectionAlgorithm[numPCP]: <default("IEEE8021QbvSelectionAlgorithm")> like IIEEE8021QbvSelectionAlgorithm {
            @display("p=675,150,c,130");
        }
        
        transmissionGate[numPCP]: <default("IEEE8021QbvGate")> like IIEEE8021QbvGate {
        	@display("p=975,150,c,130");
        }
        
        transmissionSelection: <default("IEEE8021QbvSelection")> like IIEEE8021QbvSelection {
            parameters:
            	@display("p=1275,150");
            	numPCP = numPCP;
        }
        
//        gateControlList: <default("IEEE8021QbvGateControlList")> like IIEEE8021QbvGateControlList {
//            parameters:
//            	@display("p=975,75");
//            	numGates = numPCP;
//        }
        
    connections:
        in --> queueing.in;
        for i=0..numPCP-1 {
            queueing.out[i] --> queue[i].in;
        }
        transmissionSelection.out --> out;     
}
