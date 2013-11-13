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
// Extended Scheduler module. The module allows to record the oscillator behaviour
// when the read variable is set to true. The same behaviour can then be replayed
// when setting write to true. This can speed up the simulation significantly as the
// it makes it unnecessary to simulate complex modules such as synchronisation or
// oscillator behaviour more than once.
//
// @see TTEScheduler
//
// @author Lazar Todorov, Till Steinbach
simple RecordPlaybackScheduler extends TTEScheduler
{
    parameters:
        @class(RecordPlaybackScheduler);
        // Id for recording/playback
        int id = default(0);
        // Playback drifts
        bool read = default(false);
        // Record drifts
        bool write = default(false);
}
