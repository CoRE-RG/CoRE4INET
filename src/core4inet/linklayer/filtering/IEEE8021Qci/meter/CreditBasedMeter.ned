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

package core4inet.linklayer.filtering.IEEE8021Qci.meter;

import core4inet.utilities.classes.ITimed;
//
// @author Philipp Meyer
//
simple CreditBasedMeter extends IEEE8021QciMeter like ITimed
{
    parameters:
        @class(CreditBasedMeter);
        
        int maxBurst = default(4);
        string srClass = default("A");
        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("^.^.^.scheduler.oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("^.^.^.scheduler.timer");
}
