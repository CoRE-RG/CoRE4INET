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
	#include "RCFrame_m.h"
}}

class CoRE4INET::RCFrame;

packet RCFrame;

namespace CoRE4INET;

//
// Identifier for different types of Protocol Control Frame (PCF)
//
// @see PCFrame
//
// @author Till Steinbach
enum PCFType
{
    //Coldstart Frame (CS)
    CS_FRAME = 1;
    //Integrate Frame (IN)
	IN_FRAME = 2;
	//Coldstart Acknowledge (CA)
	CA_FRAME = 3;
};

//
// Represents a Protocol Control Frame (PCF)
//
// @see RCFrame
//
// @author Till Steinbach
packet PCFrame extends RCFrame
{   
    // Set PCF Bytelength
    byteLength = 64;
    	
    // pcf_integration_cycle: Represents the integration cycle in which the protocol control frame was sent
    //
    // 32 Bit field
	uint32_t integration_cycle;
	
	// pcf_membership_new: Bit vector with a static configured one-to-one relationship from a bit to a Synchronization Master
	//
	// 32 Bit field
	uint32_t membership_new;
	
	// pcf_sync_priority: Static configured value in each Synchronization Master, Synchronization Client, and Compression Master
	//
	// 8 Bit field
	uint8_t sync_priority;

	// pcf_sync_domain: Static configured value in each Synchronization Master, Synchronization Client, and Compression Master
	//
	// 8 Bit field
	uint8_t sync_domain;
	
	// pcf_type: Defines the frame type of a Protocol Control Frame
	//
	// 4 Bit field
	uint8_t type @enum(PCFType);
	
	// pcf_transparent_clock: stores the accumulated delay of a Protocol Control Frame up to the consumer.
	//
	// Time is represented as multiples of picoseconds
	//
	// 64 Bit field
	uint64_t transparent_clock;
	
	string displayString="b=15,15,rect,white,orange,5";
}