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

package ttethernet.scheduler;

import ttethernet.scheduler.oscillator.IOscillator;

module Scheduler like ITTEScheduler
{
    parameters:
        @display("i=block/cogwheel;bgb=293,141");
        int numPeriods = default(1);
    submodules:
        timer: Timer {
            @display("p=85,87");
            gates:
                in[numPeriods];
        }
        oscillator: <default("SimpleOscillator")> like IOscillator {
            @display("p=87,25");
        }
        periods[numPeriods]: Period {
            @display("p=202,87");
        }
    connections:
        for i=0..sizeof(periods)-1 {
            periods[i].out --> timer.in[i];
        }
}
