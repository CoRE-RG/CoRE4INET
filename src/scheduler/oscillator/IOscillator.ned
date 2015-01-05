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

//
// Interface for a Module representing an oscillator.
//
// @see IOscillator, SimpleOscillator
//
// @author Till Steinbach
//
moduleinterface IOscillator
{
    parameters:
        @display("i=block/mac");
	    //Signal emitted when drift changes, contains new drift
        @signal[currentDrift](type=simtime_t);
	    //Statistic of the current drift (Difference of configured and actual tick length in seconds)
        @statistic[currentDrift](title="Current drift"; unit=s; record=vector);
	    // Length of a tick
        double tick @unit(s);
    gates:
        //Output to the timer module (currently unused)
        output out;
}
