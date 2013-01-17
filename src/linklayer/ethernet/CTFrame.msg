cplusplus {{
        #include "EtherFrame_m.h"
}}

class ::EtherFrame;

namespace TTEthernetModel;


//
// Represents a critical traffic frame
//
// CTFrames are displayed as small black rectangles in the GUI
//
// @see EtherFrame
//
// @author Till Steinbach
packet CTFrame extends EtherFrame
{    
        // Critical traffic ID (from MAC) (for TT and RC messages). 
        @customize(true);
        abstract unsigned short ctID;
        
        // Critical traffic marker (from MAC) (for TT and RC messages). 
        @customize(true);
        abstract unsigned int ctMarker;
        
        string displayString="b=15,15,rect,black,kind,5";
}