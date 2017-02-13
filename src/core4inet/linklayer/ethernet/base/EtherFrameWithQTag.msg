//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

cplusplus {{
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Winconsistent-missing-override"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Winconsistent-missing-override"
#endif
}}

class inet::EthernetIIFrame;

namespace CoRE4INET;

//
// Ethernet II headers contain a 16-bit ~EtherType to identify
// the encapsulated protocol and 802.1Q Tag
//
// Header length: src(6)+dest(6)+etherType(2)+802.1QTag(4) = 18 byte
// Total overhead: 18 byte Header + 4 byte CRC = 22 byte
//
// @see ~EthernetIIFrame
//
// @author Philipp Meyer
//
packet EthernetIIFrameWithQTag extends EthernetIIFrame
{
    // Overhead without payload
    byteLength = 22;
    
    // Priority Code Point (PCP): a 3-bit field which refers to the IEEE 802.1p priority. 
    // It indicates the frame priority level.
    // Values are from 0 (best effort) to 7 (highest); 1 represents the lowest priority.
    uint8_t pcp; 
    // Drop Eligible (DE): a 1-bit field. May be used separately 
    // or in conjunction with PCP to indicate frames eligible to be dropped in the presence of congestion.   
    bool de;   
    // VLAN Identifier (VID): a 12-bit field specifying the VLAN to which the frame belongs.
    // The hexadecimal values of 0x000 and 0xFFF are reserved. 
    // All other values may be used as VLAN identifiers, allowing up to 4,094 VLANs.
    // The reserved value 0x000 indicates that the frame does not belong to any VLAN; in this case,
    // the 802.1Q tag specifies only a priority and is referred to as a priority tag. On bridges,
    // VLAN 1 (the default VLAN ID) is often reserved for a management VLAN; this is vendor-specific.     
    uint16_t VID = 0;   
                    
    string displayString = "b=10,10,oval,blue";
}
