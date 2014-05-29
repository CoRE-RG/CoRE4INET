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
cplusplus {{
    //Auto-generated Messages
    #include "EtherFrameWithQTag_m.h"
}}

namespace CoRE4INET;

class EthernetIIFrameWithQTag;
//
// Represents a AVB Frame
//
// @see CTFrame
//
// @author Philipp Meyer 
packet AVBFrame extends EthernetIIFrameWithQTag
{    
    // ID of the AVB Stream
    //
    // 64 Bit Field
    unsigned long streamID;
    
	string displayString="b=15,15,rect,black,blue,5";
}
