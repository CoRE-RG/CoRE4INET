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
//
// TODO auto-generated type
//
module TTEAVBPHYPort like IPort
{
    parameters:
        @display("bgb=326,188;i=device/port");
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

        input AVBin @directIn @labels(AVBFrame);

    //input SRP?
    submodules:
        tteavbOutput: TTEAVBOutput {
            @diplay("p=48,45");
            @display("p=222,142");
        }

        tteavbInput: TTEAVBInput {
            parameters:
                @display("p=142,45");
                promiscuous = promiscuous;
        }

        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true;
                queueModule = "tteavbOutput";
                @display("p=78,142");
        }
    connections:
        upperLayerIn --> tteavbOutput.in;
        upperLayerOut <-- tteavbInput.out;
        tteavbOutput.out --> mac.upperLayerIn;
        tteavbInput.in <-- mac.upperLayerOut;
        phys <--> mac.phys;

        TTin --> tteavbOutput.TTin;
        RCin --> tteavbOutput.RCin;
        PCFin --> tteavbOutput.PCFin;
        AVBin --> tteavbOutput.AVBin;
}
