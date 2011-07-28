cplusplus {{
#include "EtherFrame_m.h"
}}

class EtherFrame;

packet CTFrame extends EtherFrame
{    
     // Critical traffic ID (for TT and RC messages). 
    unsigned short ctID;
    
    string displayString="b=15,15,rect,white,kind,5";
}
