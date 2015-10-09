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
// Dummy synchronisation module that does not correct the clock.
// It is used in simulations where no synchronisation is required
//
// @see ISync
//
// @author Till Steinbach
simple NoSync like ISync
{
    parameters:
        @class(NoSync);
        @display("i=block/timer");

        //Signal emited when sync state changes (e.g. SYNC, ASYNC, ...)
        @signal[NF_SYNC_STATE_CHANGE](type=CoRE4INET::SyncNotification);

    gates:
        //Input for time-triggered traffic
        input TTin @directIn @labels(CTFrame);
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
        //Input for scheduler messages
        input schedulerIn @directIn;
}
