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

import core4inet.scheduler.timer.Timer;
import core4inet.scheduler.oscillator.IOscillator;
import core4inet.scheduler.period.Period;

//
// The Scheduler provides timing events for other modules. 
//
// @see ~ITTEScheduler, ~Timer, ~IOscillator, ~Period
//
// @author Till Steinbach
//
module Scheduler like ITTEScheduler
{
    parameters:
        @display("i=block/cogwheel;bgb=293,141");
        
        // Number of Periods
        int numPeriods = default(1);
        // Length of a tick
        double tick @unit(s) = default(80ns);
        
    submodules:
        // Implements a timer with adjustable precision that may be synchronized by a synchronization module
        timer: Timer {
            @display("p=160,40");
            gates:
                period_in[parent.numPeriods];
        }
        
        // Module representing an oscillator with a simple clock drift behavior.
        oscillator: <default("SimpleOscillator")> like IOscillator {
            parameters:
                @display("p=70,40");
                tick = parent.tick;
        }
        
        // Periods define the cycles for events
        period[numPeriods]: Period {
            @display("p=70,100,row,60");
        }
        
    connections:
        for i=0..sizeof(period)-1 {
            period[i].out --> timer.period_in[i];
        }
        oscillator.out --> timer.oscillator_in;
}
