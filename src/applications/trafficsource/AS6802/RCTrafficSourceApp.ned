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

package core4inet.applications.trafficsource.AS6802;

import core4inet.utilities.classes.ITimed;

//
// Traffic source application used for rate-constrained traffic generators.
//
// @see TTTrafficSourceApp
//
// @author Till Steinbach
simple RCTrafficSourceApp extends CTTrafficSourceAppBase like ITimed
{
    parameters:
        @class(RCTrafficSourceApp);
        @display("i=,orange");

        //Sending interval for the rate constrained messages (any build in disstribution can be used)
        volatile double interval @unit(s);

        //Oscillator of Scheduler this app is assigned to
        string oscillator = default("oscillator");
        //Timer of Scheduler this app is assigned to
        string timer = default("timer");
}
