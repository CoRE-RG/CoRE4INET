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
package core4inet.incoming.AS6802;

import core4inet.incoming.base.Incoming;

//
// Module for the conformance checks of incoming protocol control frames.
//
// The traffic is checked for conformance with pcfType.
//
// @warning Only the bag parameter is used!
//
// @see Incoming,
//
// @author Lazar Todorov, Till Steinbach
simple PCFIncoming extends Incoming
{
    parameters:
        @display("i=,green");
        //PCFIncoming is implemented by the PCFIncoming C++ Class
        @class(PCFIncoming);
        //Allowed PCF-Type for this CTC (CS = 1; IN = 2; CA = 3)
        int pcfType = default(1);
}