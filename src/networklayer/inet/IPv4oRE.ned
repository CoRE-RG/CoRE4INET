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

package core4inet.networklayer.inet;

import inet.networklayer.ipv4.IPv4;

//
// Module for sending IP traffic over RTEthernet.
// Which packets are send over TT, RC or AVB and which are sent as BE is defined via the "filters" parameter
//
// @author Kai-Uwe von Deylen
simple IPv4oRE extends IPv4 {
    
    parameters:
        @class("TT_RC_AVB_IPv4");
        //
        // this parameter defines which traffic is sent via TT, RC or AVB
        // The config consists of "filter" elements and "subscribe" elements
        //
	    // Each filter consists of several attributes.
	    // Each attribute either is used to define the pattern to check if outgoing packets are matching them or is used to define how to send the matching packets:
	    // The pattern attributes are always the same, no matter what kind of outgoing packet should be sent.
	    // The other attributes, which are defining how to send the packet, vary, depending on which kind of packet should be sent (i.e. TT or RC or AVB)
	    // 
	    // Pattern attributes:
	    // - srcAddress       (optional)
        // - srcPrefixLength  (optional)
        // - destAddress      (optional)
        // - destPrefixLength (optional)
        // - protocol         (optional)
        // - tos              (optional)
        // - tosMask          (optional)
        // - srcPort          (optional)
        // - srcPortMin       (optional)
        // - srcPortMax       (optional)
        // - destPort         (optional)
        // - destPortMin      (optional)
        // - destPortMax      (optional)
        // 
        // Destination Type (value of the "destType" attribute, which defines the Layer2)
        // - destType="DestinationType_TT"
        // - destType="DestinationType_RC"
        // - destType="DestinationType_AVB"
        // 
        // TT send attributes:
        // - destModule (mandatory)
        // - ctId       (mandatory)
        // - actionTime (mandatory)
        // - period     (optional, defaults to "period[0]")
        // - oscillator (optional, defaults to "oscillator")
        // 
        // RC send attributes:
        // - destModules (mandatory)
        // - ctId        (mandatory)
        // 
        // AVB send attributes:
        // - destModule      (mandatory)
        // - destMAC         (mandatory)
        // - streamId        (mandatory)
        // - trafficClass    (optional, defaults to "A")
        // - frameSize       (mandatory)
        // - intervallFrames (mandatory)
        // - vlanId          (mandatory)
        //  
	    // 	Each subscribe element has one single "streamId" attribute which defines the stream Id to subscribe to.
	    // 
        xml filters = default(xmldoc("filters.xml"));
        //Interval in which an avb subscription is updated
        double avbUpdateInterval @unit("s") = default(6s);
        //Interval in which an avb subscription is reregistered after a timeout
        double avbRetryInterval @unit("s") = default(1s);
    gates:
        input AVBin;
        input RCIn;
        input TTIn;
        input schedulerIn;
}
