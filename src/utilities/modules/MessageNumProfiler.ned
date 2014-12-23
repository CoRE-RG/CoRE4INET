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

package core4inet.utilities.modules;

// The MessageNumProfiler is able to profile the number of messages each module
// stores. In a configurable time interval it triggers a profile run which
// recursively scans all modules starting at the root. This allows to find
// misconfigured modules and memory leaks.
simple MessageNumProfiler
{
    parameters:
        //Print messages to std::cerr instead of EV
        bool print_cerr = default(true);
        //Also print the messages residing in the module
        bool print_msgs = default(true);
        // Interval in which the profiler is run
        double interval @unit(s) = default(1s);
        // Maximum allowed number of messages in the module (Modules with less
        // messages are not evaluated
        int max_messages = default(0);
        // Maximum messages in the whole system (-1 means do not check)
        int max_live_messages = default(-1);
        // Maximum messages in the scheduler (-1 means do not check)
        int max_scheduled_messages = default(-1);
        // Throw exceptionwhen limits are not met. Simulation is beeing stopped
        bool throw_error = default(false);
        @display("i=block/cogwheel");
}
