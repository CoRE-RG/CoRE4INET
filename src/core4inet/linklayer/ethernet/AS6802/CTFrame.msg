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

import inet.linklayer.ethernet.EtherFrame;

cplusplus {{ 
#if defined(__clang__)
#  pragma clang diagnostic ignored "-Winconsistent-missing-override"
#elif defined(__GNUC__) && __GNUC__ >= 5
#  pragma GCC diagnostic ignored "-Wsuggest-override"
#endif
}}

namespace CoRE4INET;

//
// Represents a critical traffic frame
//
// CTFrames are displayed as small black rectangles in the GUI
//
// @see ~EthernetIIFrame, ~EtherFrame
//
// @author Till Steinbach
//
packet CTFrame extends inet::EthernetIIFrame
{
    @customize(true);    
    
	// Set EthernetHeader Bytelength
	byteLength = 18;	
	etherType = 0x891d;
	
    // Critical traffic ID (from MAC) (for TT and RC messages). 
    abstract uint16_t ctID;  
    // Critical traffic marker (from MAC) (for TT and RC messages). 
    abstract uint32_t ctMarker;
    
    string displayString="b=15,15,rect,black,kind,5";
}