cplusplus {{
        #include "EtherFrame_m.h"
}}

class ::EtherFrame;

namespace TTEthernetModel;

//
// Represents a Stream Reservation Protokol Frame (SRP)
//
// @see EtherFrame
//
// @author Philipp Meyer
packet SRPFrame extends EtherFrame{
    
    
    // ID of the AVB Stream
    //
    // 64 Bit Field
	unsigned long streamID;
	
	
	// notused
	//
	// 64 Bit Field
	unsigned long DataFrameParameters;
	
	// tSpec => Max frame size and sending interval of an AVB stream
	//
	// 32 Bit Field
	unsigned int MaxFrameSize;
	unsigned int MaxIntervalFrames;
	
	
	// notused
	//
	// 8 Bit Field
	unsigned char priorityAndRank;
	
	// notused
	//
	// 32 Bit Field
	unsigned int accumulatedLatency;
	
	// FailureInformation
	//
	// 72 Bit Field
	
	// for internal implementation:
	string displayString="b=15,15,rect,black,black,5";
	unsigned int portIndex;
}
