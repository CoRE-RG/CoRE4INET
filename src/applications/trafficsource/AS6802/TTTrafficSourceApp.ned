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

import core4inet.utilities.classes.IScheduled;

//
// Traffic source application used for time-triggered traffic generators.
//
// @see RCTrafficSourceApp
//
// @author Till Steinbach
simple TTTrafficSourceApp extends CTTrafficSourceAppBase like IScheduled
{
    parameters:
        @class(TTTrafficSourceApp);
        @display("i=,red");

        //Time in the cycle at which the message is being send to the connected buffers
        double action_time @unit(s);

        //Modulo cycles: 1 means message is being send in each cycle, 2 means in every second cycle,
        //and so on. 0 means never
        int modulo = default(1);

        //Period of Scheduler this app is assigned to
        string period = default("period[0]");
        //Oscillator of Scheduler this app is assigned to
        string oscillator = default("oscillator");
        //Timer of Scheduler this app is assigned to
        string timer = default("timer");


}
