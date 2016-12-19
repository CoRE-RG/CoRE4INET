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
 
package core4inet.linklayer.shaper;

import core4inet.utilities.classes.ITimed;

//
//A Shaper that handles TT, PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - time-triggered
// - PCF
// - rate-constrained
// - best-effort
//
// @see ~PCF_RC_BE_Shaper, ~ITimed
//
// @author Till Steinbach
//
simple TT_PCF_RC_BE_Shaper extends PCF_RC_BE_Shaper like ITimed
{
    parameters:
        @display("i=block/classifier");
        @class(TT_PCF_RC_BE_Shaper);
        
        //Signal emitted when queue length of the tt queue changes, contains new queue length
        @signal[ttQueueLength](type=unsigned long; unit=packets);
        //Statistic of the queue length of time-triggered frames
        @statistic[ttQueueLength](title="TT-Queue Length"; unit=packets; record=vector,stats; interpolationmode=sample-hold);
        
        //Comma seperated list of TTBuffers that send messages to this port
        string tt_buffers = default("");
        //Safety margin for TT-Messages in ticks (musst be set according to maximum clock correction!)
        int safety_margin = default(5);
        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("^.^.scheduler.oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("^.^.scheduler.timer");
        
    gates:
        //Input for time-triggered frames from the buffers
        input TTin @labels(TTFrame);
}
