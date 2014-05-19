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
	unsigned long streamID;
	
	MACAddress streamDA;
	
	// for internal implementation:
	string displayString="b=15,15,rect,black,black,5";
}

packet TalkerAdvertise extends SRPFrame{
    byteLength = 25;
    // notused
	// 64 Bit Field
	unsigned long DataFrameParameters;
	
	// tSpec => Max frame size and sending interval of an AVB stream
	// 32 Bit Field
	unsigned int MaxFrameSize;
	unsigned int MaxIntervalFrames;
	
	
	// notused
	// 8 Bit Field
	unsigned char priorityAndRank;
	
	// notused
	// 32 Bit Field
	unsigned int accumulatedLatency;
}

packet TalkerFailed extends SRPFrame{
}

packet ListenerReady extends SRPFrame{
	byteLength = 8;
}

packet AskingFailed extends SRPFrame{
    // FailureInformation
	//
	// 72 Bit Field
}

packet ListenerFailed extends SRPFrame{
    // FailureInformation
	//
	// 72 Bit Field
}

packet ListenerReadyFailed extends ListenerReady{
    // FailureInformation
	//
	// 72 Bit Field
}
