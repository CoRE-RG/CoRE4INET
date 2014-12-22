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

//
// TODO auto-generated module
//
simple MessageNumProfiler
{
    parameters:
        bool print_cerr = default(true);
        bool print_msgs = default(true);
        double interval @unit(s) = default(1s);
        int max_messages = default(0);
        int max_live_messages = default(-1);
        int max_scheduled_messages = default(-1);
        bool throw_error = default(false);
}
