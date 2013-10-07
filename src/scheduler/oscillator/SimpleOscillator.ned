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

//
// TODO auto-generated module
//
simple SimpleOscillator extends Oscillator
{
    parameters:
        @class(SimpleOscillator);
        // Maximum clock drift (e.g 16ps for 200ppm at 80ns per tick)
        double max_drift @unit(s) = default(16ps);
        // Clock drift change for the next cycle, you are free to use your desired distribution
        volatile double drift_change @unit(s) = default(uniform(-1ps,1ps));
}
