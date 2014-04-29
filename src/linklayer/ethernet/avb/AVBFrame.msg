cplusplus {{
    #include "EtherFrame_m.h"
}}

class ::EtherFrame;

namespace CoRE4INET;
//
// Represents a AVB Frame
//
// @see CTFrame
//
// @author Philipp Meyer 
packet AVBFrame extends EtherFrame
{    
    // ID of the AVB Stream
    //
    // 64 Bit Field
    unsigned long streamID;
    
	string displayString="b=15,15,rect,black,blue,5";
}
