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

package core4inet.services.avb.SRP;

//
// This module handles the Stream Reservation Protocol
//
// SRP messages are sent and received through SRPEtherLLC and SRPRelay
//
// @warning This is a simplified implementation of the Stream Reservation Protocol that does not use the original
// message format
//
// @see SRPEtherLLC, SRPRelay
//
// @author Till Steinbach
//
simple SRProtocol
{
    parameters:
        @display("i=block/network2,blue");
        @class(SRProtocol);
        //Amount of total bandwidth that is reservable (0-1) default: 0.75 representing 75% 
        double reservableBandwidth = default(0.75); 
    gates:
        //Gate for incoming SRP messages
        input in @labels(EtherFrame);
        //Gate for outgoing SRP messages
        output out @labels(EtherFrame);
}
