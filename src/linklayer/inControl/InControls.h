#ifndef __TTE4INET_INCONTROLS_H_
#define __TTE4INET_INCONTROLS_H_


#include <BaseInControl.h>
#include <BEInControl.h>
#include <CTInControl.h>

namespace TTEthernetModel{

/**
* @brief Class representing the BE_InControl module
*
* This module only handles incoming best-effort traffic.
*
* @see BaseInControl
*/
class BE_InControl: public BEInControl<BaseInControl>{};

/**
* @brief Class representing the CT_BE_InControl module
*
* This module handles incoming critical (TT, RC and PCF) and best-effort traffic.
*
* @see BaseInControl, BEInControl
*/
class CT_BE_InControl: public CTInControl<BEInControl<BaseInControl> >{};

}

#endif
