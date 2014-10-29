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
package core4inet.incoming.AS6802;

import core4inet.incoming.base.Incoming;
import core4inet.utilities.classes.ITimed;
//
// Module for the conformance checks of incoming rate-constrained traffic.
//
// The traffic is checked for conformance with the bag.
//
// @see Incoming,
//
// @author Till Steinbach
simple RCIncoming extends Incoming like ITimed
{
    parameters:
        @display("i=,orange");
        //RCIncoming is implemented by the RCIncoming C++ Class
        @class(RCIncoming);
        // Bandwidth allocation gap in number of ticks (Changes to this parameter will get active for future frames only)
        int bag @unit(tick) = default(0tick);
        // Maximum jitter for the bandwidth allocation gap in number of ticks
        int jitter @unit(tick) = default(0tick);

        string oscillator = default("oscillator");
        string timer = default("timer");
}
