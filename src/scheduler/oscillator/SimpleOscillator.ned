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

package core4inet.scheduler.oscillator;

import core4inet.utilities.classes.IScheduled;

//
// Module representing an oscillator with a simple clock drift behavior.
// The module schedules a message for every cycle at action_point 0 and then changes the drift by using the drift_change
// parameter.
//
// @see IOscillator, Oscillator
//
// @author Till Steinbach
//
simple SimpleOscillator extends Oscillator like IScheduled
{
    parameters:
        @class(SimpleOscillator);
        // Maximum clock drift
        double max_drift @unit(ppm) = default(200ppm);
        // Clock drift change intensity
        volatile double drift_change @unit(ppm) = default(uniform(12.5ppm,12.5ppm));
        // Period related to the clock drift update
        string period = default("period[0]");
        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node)
        string oscillator = "this";
        //Timer of the timed module (must be set to the name of an timer module in the Node)
        string timer = default("timer");
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
