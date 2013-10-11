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

package ttethernet.scheduler.oscillator;


moduleinterface IOscillator{
	parameters:
	    @display("i=block/mac");
	    //Statistic of the current drift (Difference of configured and actual tick length in seconds)
        @statistic[currentDrift](title="Current drift"; unit=s; record=vector);
	    // Length of a tick
        double tick @unit(s);
        // Current length of a tick (with imprecission)
        volatile double current_tick @unit(s);
    gates:
        output out;    
}