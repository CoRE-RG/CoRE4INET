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

import core4inet.linklayer.shaper.base.BE_Shaper;

//
//A Shaper that handles PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - PCF
// - rate-constrained
// - best-effort
//
// @see ~BE_Shaper
//
// @author Till Steinbach
//
simple PCF_RC_BE_Shaper extends BE_Shaper
{
    parameters:
        @class(PCF_RC_BE_Shaper);
        
        //Signal emitted when queue length of the pcf queue changes, contains new queue length
        @signal[pcfQueueLength](type=unsigned long; unit=packets);
		//Statistic of the queue length of protocol control frames
        @statistic[pcfQueueLength](title="PCF-Queue Length"; unit=packets; record=vector,stats; interpolationmode=sample-hold);
        //Signal emitted when queue length of the rc queue changes, contains new queue length
        @signal[rc*QueueLength](type=unsigned long; unit=packets);
        //Statistic of the queue length of rate-constrained frames
        @statisticTemplate[rcQueueLength](title="RC-Queue Length ($name)"; unit=packets; record=vector,stats; interpolationmode=sample-hold);
        //Signal emitted when queue size of the pcf queue changes, contains new queue size in bytes
        @signal[pcfQueueSize](type=unsigned long; unit=B);
        //Statistic of the queue length of pcf frames
        @statistic[pcfQueueSize](title="BE-Queue Size"; unit=B; record=vector,stats; interpolationmode=sample-hold);
        //Signal emitted when queue size of the rc queue changes, contains new queue size in bytes
        @signal[rc*QueueSize](type=unsigned long; unit=B);
        //Statistic of the queue size of rate-constrained frames in bytes
        @statisticTemplate[rcQueueSize](title="RC-Queue Size ($name)"; unit=B; record=vector,stats; interpolationmode=sample-hold);

		//Number of rate-constrained priorities
        int numRCpriority = default(10);
        
    gates:
        //Input for rate-constrained frames from the buffers
        input RCin @labels(RCFrame);
        //Input for protocol control frames from the buffers
        input PCFin @labels(PCFrame);
}
