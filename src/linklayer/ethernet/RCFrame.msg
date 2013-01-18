cplusplus {{
#include "CTFrame.h"
}}

class TTEthernetModel::CTFrame;

packet CTFrame;

namespace TTEthernetModel;
//
// Represents a RC frame
//
// @see CTFrame
//
// @author Till Steinbach
packet RCFrame extends CTFrame
{    
    string displayString="b=15,15,rect,black,orange,5";

}