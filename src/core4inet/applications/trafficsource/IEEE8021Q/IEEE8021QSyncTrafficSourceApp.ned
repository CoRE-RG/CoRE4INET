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

package core4inet.applications.trafficsource.IEEE8021Q;

import core4inet.applications.trafficsource.IEEE8021Q.IEEE8021QTrafficSourceApp;
import core4inet.utilities.classes.IScheduled;

//
// Traffic source application used for synchronized IEEE 802.1Q traffic
//
// @see ~IEEE8021QTrafficSourceApp, ~IScheduled, ~TTTrafficSourceApp, ~BGTrafficSourceApp
//
// @author Philipp Meyer
//
simple IEEE8021QSyncTrafficSourceApp extends IEEE8021QTrafficSourceApp like IScheduled
{
    parameters:
        @class(IEEE8021QSyncTrafficSourceApp);
        
        //Time in the period at which the message is being send to the connected buffers
        double actionTime @unit(s);
        //Modulo cycles: 1 means message is being send in each cycle, 2 means in every second cycle,
        //and so on. 0 means never
        int modulo = default(1);
        //Oscillator of Scheduler this app is assigned to
        string oscillator = default("^.scheduler.oscillator");
        //Timer of Scheduler this app is assigned to
        string timer = default("^.scheduler.timer");
        //Period of Scheduler this app is assigned to
        string period = default("^.scheduler.period[0]");
}
