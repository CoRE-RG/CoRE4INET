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
    //INET
    #include "MACAddress.h"
}}

class noncobject MACAddress;

namespace CoRE4INET;

//
// Represents a Stream Reservation Protokol Frame (SRP)
//
// @see EtherFrame
//
// @author Philipp Meyer
packet SRPFrame{
    
    // ID of the AVB Stream
    // 64 Bit Field (48bit MAC + 16bit UniqueID)
	uint64_t streamID;
	
		
	// for internal implementation:
	string displayString="b=15,15,rect,black,black,5";
}

packet TalkerAdvertise extends SRPFrame{
    byteLength = 25;
    
    // DataFrameParameters => destination adress and vlan identifier
	// 64 Bit Field
	MACAddress destination_address; //only one Talker allowed per destination_address
	uint16_t vlan_identifier;
	
	// TSpec => Max frame size and sending interval of an AVB stream
	// 32 Bit Field
	uint16_t MaxFrameSize;
	uint16_t MaxIntervalFrames;
	
	
	// PriorityAndRank => Data Frame Priority: 6 = SRClass A & 5 = SRClass B
	// 8 Bit Field (3 Bit Data Frame Priority | 1 Bit Rank | 4 Bit Reserved (Zero filled))
	uint8_t priorityAndRank;
	
	// notused
	// 32 Bit Field
	uint32_t accumulatedLatency;
}

packet TalkerFailed extends TalkerAdvertise{
    byteLength = 34;
    // FailureInformation
	//
	// 72 Bit Field
}

packet ListenerReady extends SRPFrame{
	byteLength = 8;
	
	uint16_t vlan_identifier;
}

packet ListenerAskingFailed extends SRPFrame{
    byteLength = 17;
    // FailureInformation
	//
	// 72 Bit Field
	
	uint16_t vlan_identifier;
}

packet ListenerReadyFailed extends ListenerReady{
    byteLength = 17;
    // FailureInformation
	//
	// 72 Bit Field
}
