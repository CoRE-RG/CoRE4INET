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
package core4inet.synchronisation.base;

import core4inet.utilities.classes.Scheduled;

//
// Dummy synchronisation module that corrects the clock with a certain imprecission.
// It uses the simulation time as basis.
//
// @see ISync
//
// @author Till Steinbach
simple DummySync extends Scheduled like ISync
{
    parameters:
        @class(DummySync);
        @display("i=block/timer");

        //Signal emited when sync state changes (e.g. SYNC, ASYNC, ...)
        @signal[NF_SYNC_STATE_CHANGE](type=CoRE4INET::SyncNotification);

        // The time in the cycle (in ticks) when the synchronisation is triggered
        int action_time = default(0);

        // The precission of the synchronisation
        double precission @unit(s) = default(500ns);

    gates:
        //Input for time-triggered traffic
        input TTin @directIn @labels(CTFrame);
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
        //Input for scheduler messages
        input schedulerIn @directIn;
}
