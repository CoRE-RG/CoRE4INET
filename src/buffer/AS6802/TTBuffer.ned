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

import core4inet.utilities.classes.IScheduled;

//
// Represents an abstract Buffer for time-triggerd traffic. Messages are sent using the configured
// send window.
//
// The TTBuffer registers a timer (SchedulerActionTimeEvent) at the scheduler module (TTEScheduler) to send its
// Message in conformance with the send window.
//
// @warning Do not instantiate the module. Use TTDoubleBuffer or TTQueueBuffer instead!
//
// @todo The TTBuffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see TTDoubleBuffer, TTQueueBuffer, Buffer, SchedulerActionTimeEvent, TTEScheduler
//
// @author Till Steinbach
simple TTBuffer extends CTBuffer like IScheduled
{
    parameters:
        //TTBuffer is implemented by the TTBuffer C++ Class
        @class(TTBuffer);
        @display("i=,red");
        //Beginning of the send window in number of ticks (Changes to this parameter will get active for future scheduled frames only)
        int sendWindowStart @unit(tick);
        //End of the send window in number of ticks
        int sendWindowEnd @unit(tick) = default(0tick);

        //Period of Scheduler this buffer is assigned to
        string period = default("period[0]");
        string oscillator = default("oscillator");
        string timer = default("timer");
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;

}
