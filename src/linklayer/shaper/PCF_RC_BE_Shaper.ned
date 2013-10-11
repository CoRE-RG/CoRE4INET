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
package ttethernet.linklayer.shaper;

import ttethernet.linklayer.shaper.base.BE_Shaper;
import inet.linklayer.IOutputQueue;

//A Shaper that handles PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - PCF
// - rate-constrained
// - best-effort
//
// @see BE_Shaper
//
// @author Till Steinbach
//
simple PCF_RC_BE_Shaper extends BE_Shaper
{
    parameters:
        @class(PCF_RC_BE_Shaper);
		//Statistic of the queue length of protocol control frames
        @statistic[pcfQueueLength](title="PCF-Queue Length"; record=vector; interpolationmode=sample-hold);
    gates:        
        //Input for rate-constrained frames from the buffers
        input RCin @labels(RCFrame);
        //Input for protocol control frames from the buffers
        input PCFin @labels(PCFrame);
}
