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

cplusplus {{
#include "INETDefs.h"

//This disables warnings for this class!
#pragma GCC system_header
}}

namespace CoRE4INET;

//
// Represents payload in an TTEthernet-Message sent over API
//
// @author Till Steinbach
//
packet APIPayload
{
    unsigned char data[]; //The actual payload encoded in bytes
}
