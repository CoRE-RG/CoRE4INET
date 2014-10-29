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
package core4inet.buffer.AS6802;

import core4inet.utilities.classes.ITimed;
//
// Represents an abstract Buffer for rate-constrained traffic. Messages are sent using the configured
// bandwidth allocation gap.
//
// The RCBuffer registers a timer (SchedulerTimerEvent) at the scheduler module (TTEScheduler) to send its
// Message in conformance with the BAG account.
//
// @warning Do not instantiate the module. Use RCDoubleBuffer or RCQueueBuffer instead! 
// Only the bag parameter is currently used!
//
// @todo The RCBuffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see RCDoubleBuffer, RCQueueBuffer, Buffer, SchedulerTimerEvent, TTEScheduler
//
// @author Till Steinbach
simple RCBuffer extends CTBuffer like ITimed
{
    parameters:
        //RCBuffer is implemented by the RCBuffer C++ Class
        @class(RCBuffer);
        @display("i=,orange");
        // Not used
        int max_dispatch_delay @unit(tick) = default(0tick);
        // Bandwidth allocation gap in number of ticks (Changes to this parameter will get active for future frames only)
        int bag @unit(tick) = default(0tick);
        // Maximum jitter for the bandwidth allocation gap in number of ticks
        int jitter @unit(tick) = default(0tick);

        string oscillator = default("oscillator");
        string timer = default("timer");
    gates:
        //Input gate for the incoming SchedulerTimerEvent messages
        input schedulerIn @directIn;
}
