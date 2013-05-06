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
    
    
    //
    //
    // 64 Bit Field
	unsigned long streamID;
	
	
	//
	//
	// 64 Bit Field
	unsigned long DataFrameParameters;
	
	//
	//
	// 32 Bit Field
	unsigned int tSpec;
	
	//
	//
	// 8 Bit Field
	unsigned char priorityAndRank;
	
	//
	//
	// 32 Bit Field
	unsigned int accumulatedLatency;
	
	// FailureInformation
	//
	// 72 Bit Field
	
	
	string displayString="b=15,15,rect,black,black,5";
	unsigned int portIndex;
}
