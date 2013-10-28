cplusplus {{
    #include "CTFrame.h"
}}

class TTEthernetModel::CTFrame;

packet CTFrame;

namespace TTEthernetModel;
//
// Represents a AVB Frame
//
// @see CTFrame
//
// @author Philipp Meyer 
packet AVBFrame extends CTFrame
{    
    // ID of the AVB Stream
    //
    // 64 Bit Field
    unsigned long streamID;
    
	string displayString="b=15,15,rect,black,blue,5";
}
