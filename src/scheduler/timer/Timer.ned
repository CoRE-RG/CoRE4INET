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

package core4inet.scheduler.timer;

//
// Timer Module:  Implements a timer with an attached oscillator with adjustable precision that may be synchronized by a
// synchronization module
//
// @see IOscillator, IPeriod
//
// @author Till Steinbach
//
simple Timer
{
    parameters:
        @display("i=block/timer");
        //Signal emitted when the clock is corrected, contains the signed number of ticks that is added to the clock
        @signal[clockCorrection](type=long);
        //Statistic of the clock correction in ticks
        @statistic[clockCorrection](title="Clock correction"; unit=s; record=vector);
    gates:
        //Input from the period modules (currently unused)
        input period_in[];
         //Input from the oscillator module (currently unused)
        input oscillator_in;
}
