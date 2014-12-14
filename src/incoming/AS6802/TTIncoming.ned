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
import core4inet.utilities.classes.IScheduled;

//
// Module for the conformance checks of incoming time-triggered traffic.
//
// The traffic is checked for conformance with the receive window and afterwards
// delayed until the permanence point in time (permanence_pit). Therefore it registers a
// timer message (SchedulerActionTimeEvent) with the schduler module (TTEScheduler)
//
// @see Incoming, SchedulerActionTimeEvent, TTEScheduler
//
// @author Till Steinbach
simple TTIncoming extends Incoming like IScheduled
{
    parameters:
        @display("i=,red");
        //TTIncoming is implemented by the TTIncoming C++ Class
        @class(TTIncoming);
        //Beginning of the receive window in number of ticks (-1 means no receive window)
        int receive_window_start @unit(tick);
        //End of the receive window in number of ticks (-1 means no receive window)
        int receive_window_end @unit(tick);
        //permanence point in time in number of ticks (-1 means no permanence point, frame is relayed immediately)
        int permanence_pit @unit(tick);
        //Period of Scheduler this ctc is assigned to
        string period = default("period[0]");
        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("timer");
        //Hardware delay is set to 0s as the forwarding is scheduled (permanence_pit)
        hardware_delay = 0s;
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
