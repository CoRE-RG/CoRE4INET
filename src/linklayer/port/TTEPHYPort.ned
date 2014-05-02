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

import core4inet.linklayer.inControl.CT_BE_InControl;
import core4inet.linklayer.shaper.TT_PCF_RC_BE_Shaper;
import inet.linklayer.ethernet.EtherMACFullDuplex;


// The TTEPHYPort is a compund module that contains the input Shaper, output Shaper and MAC (EtherMACFullDuplex)
// It represents a physical port for a real-time Ethernet device (Switch or Host)
//
// @see IPort, EtherMACFullDuplex, TTEInput, TT_PCF_RC_BE_Shaper, PCF_RC_BE_Shaper, BE_Shaper
//
// @author Till Steinbach
module TTEPHYPort like IPort
{
    parameters:
        @display("bgb=188,180;i=device/port");
        // if true, all packets are received, otherwise only the ones with matching destination MAC address (This does not affect CT-Frames)
        bool promiscuous = default(false);
        //Static propagation delay for the port
        double static_tx_delay @unit(s) = default(0ns);
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
        shaper: TT_PCF_RC_BE_Shaper {
            @display("p=48,45");
        }
        //Module for the organisation of inbound traffic
        inControl: CT_BE_InControl {
            parameters:
                @display("p=142,45");
                promiscuous = promiscuous;
        }
        //MAC interface
        mac: EtherMACFullDuplex {
            parameters:
                promiscuous = true; //MAC must be set promiscuous to allow for CT receiption with all CT-Markers
                queueModule = "shaper";//The tteOutput-Module(TTEOutput) is used as external queue for the interface
                @display("p=87,139");
        }
    connections:
        upperLayerIn --> shaper.in;
        upperLayerOut <-- inControl.out;
        shaper.out --> mac.upperLayerIn;
        inControl.in <-- mac.upperLayerOut;
        phys <--> mac.phys;


        TTin --> shaper.TTin;
        RCin --> shaper.RCin;
        PCFin --> shaper.PCFin;
}
