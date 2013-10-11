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
*
* @author Till Steinbach
*/
class BE_InControl: public BEInControl<BaseInControl>{};

/**
* @brief Class representing the CT_BE_InControl module
*
* This module handles incoming critical (TT, RC and PCF) and best-effort traffic.
*
* @see BaseInControl, BEInControl
*
* @ingroup AS6802
*
* @author Till Steinbach
*/
class CT_BE_InControl: public CTInControl<BEInControl<BaseInControl> >{};

}

#endif
