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

package core4inet.applications.AS6802;

import core4inet.applications.base.ApplicationBase;

//
// Abstract base application used for various application models.
// Since this is an abstract module please do not instantiate it
//
//
// @see TTEAPIApplicationBase.ned
//
// @author Till Steinbach
simple CTApplicationBase extends ApplicationBase
{
    parameters:
        @class(CTApplicationBase);
        @display("i=block/app");
        
    gates:
        //Input gate for the incoming time-triggered messages
        input TTin @directIn @labels(TTFrame);
        //Input gate for the incoming rate-constrained messages
        input RCin @directIn @labels(RCFrame);
}
