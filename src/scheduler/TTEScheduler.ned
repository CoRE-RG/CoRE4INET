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
package core4inet.scheduler;

//
// TTEthernet scheduler module. The module allows to register Events using the
// registerEvent(SchedulerEvent) method. Allowed Events are:
// - SchedulerActionTimeEvent: Event that is triggered at a specified time in the cycle
// - SchedulerTimerEvent: Event that is triggered after a specified time
//
// The Scheduler can be asked for the current time with the getTicks() method.
// The cycle is configured by the parameters tick and cycle_ticks.
//
// @warning DEPRICATED MODULE, Please use Scheduler Module instead!
// 
// @see Scheduler
//
// @author Till Steinbach
simple TTEScheduler like ITTEScheduler
{
    parameters:
        @display("i=block/cogwheel");
        //Statistic of the current drift (Difference of configured and actual tick length)
        @statistic[currentDrift](title="Current drift"; unit=s; record=vector);
        //Statistic of the beginning of a new cycle
        @statistic[newCycle](title="Start of cycle"; record=count,vector);
        // Length of a tick
        double tick @unit(s) = default(80ns);
        // Maximum clock drift (e.g 16ps for 200ppm at 80ns per tick)
        double max_drift @unit(s) = default(16ps);
        // Clock drift change for the next cycle, you are free to use your desired distribution
        volatile double drift_change @unit(s) = default(uniform(-1ps,1ps));
        // Current length of a tick (with imprecission)
        volatile double current_tick @unit(s) = tick;
        // Number of ticks for one cycle
        int cycle_ticks @unit(tick) = default(37500tick);
}
