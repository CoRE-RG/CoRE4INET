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

package ttethernet.linklayer;


import inet.linklayer.IEtherMAC;
import inet.linklayer.ethernet.EtherMACFullDuplex;
import inet.networklayer.queue.DropTailQueue;
import inet.networklayer.queue.DropTailQoSQueue;

module TTEPHYPort like IPort
{
    parameters:
        @display("bgb=188,180;i=device/port");
    gates:
        input upperLayerIn @loose @labels(EtherFrame);
        output upperLayerOut @loose @labels(EtherFrame);
        inout phys @labels(EtherFrame);
        
        input TTin @directIn @labels(CTFrame);
        input RCin @directIn @labels(CTFrame);

    submodules:
        tteOutput: TTEOutput {
            @display("p=48,45");
        }

        tteInput: TTEInput {

            @display("p=142,45");
        }

        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true;
                queueModule = "tteOutput";
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
