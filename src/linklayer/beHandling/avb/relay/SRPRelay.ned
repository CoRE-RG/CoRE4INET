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

package core4inet.linklayer.beHandling.avb.relay;

import inet.linklayer.ieee8021d.relay.Ieee8021dRelay;


//
// This module forwards frames (~EtherFrame) based on their destination MAC addresses to appropriate ports.
//
// It can handle: AVBs SRP frames.
// Incoming SRP frames are forwarded as SRP messages through srpOut to the SRProtocol module.
// Outgoing SRP messages coming through srpIn gate are forwarded according to the controlInfo as EtherFrame
//
// @see Ieee8021dRelay, SRProtocol
// 
// @author Till Steinbach
//
simple SRPRelay extends Ieee8021dRelay
{
    parameters:
        @class(SRPRelay);
        @display("i=block/broadcast;bgb=425,114");
    gates:
        //SRP message in from SRP protocol module
        input srpIn @loose;
        //SRP message out to SRP protocol module
        output srpOut @loose;
}
