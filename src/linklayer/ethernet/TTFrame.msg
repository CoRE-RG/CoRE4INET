cplusplus {{
#include "CTFrame_m.h"
}}

class TTEthernetModel::CTFrame;

packet CTFrame;

namespace TTEthernetModel;
//
// Represents a TT frame
//
// @see CTFrame
//
// @author Till Steinbach
packet TTFrame extends CTFrame
{    
	string displayString="b=15,15,rect,black,red,5";
}
