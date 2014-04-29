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

package core4inet.scheduler.period;

//
// Period Module: Periods define the cycles for events
//
// @author Till Steinbach
//
simple Period
{
    parameters:
        //Signal emitted when a new cycle starts
        @signal[newCycle]();
        //Statistic of the beginning of a new cycle
        @statistic[newCycle](title="Start of cycle"; record=count,vector; interpolationmode=none);
        // Number of ticks for one cycle
        int cycle_ticks @unit(tick) = default(37500tick);
        // Number of ticks offset
        int offset_ticks @unit(tick) = default(0tick);
        @display("i=block/table");
    gates:
        //Output to the timer module (currently unused)
        output out;
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
