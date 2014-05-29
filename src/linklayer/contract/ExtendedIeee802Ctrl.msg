//
// Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


cplusplus {{
    //INET
	#include "Ieee802Ctrl_m.h"
	
	#define SWITCH_PORT_BROADCAST -1
}}


class noncobject ::Ieee802Ctrl;

namespace CoRE4INET;

//
// Control structure for communication between LLC and higher layers
//
class ExtendedIeee802Ctrl extends Ieee802Ctrl
{
    int notSwitchPort = -1; // swich port index to exclude (only in swiches)
}
