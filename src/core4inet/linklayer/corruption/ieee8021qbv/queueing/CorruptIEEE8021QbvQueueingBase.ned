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

package core4inet.linklayer.corruption.ieee8021qbv.queueing;

import core4inet.linklayer.shaper.IEEE8021Qbv.queueing.IEEE8021QbvQueueing;

//
// TODO auto-generated module
//
simple CorruptIEEE8021QbvQueueingBase extends IEEE8021QbvQueueing
{
	parameters:
	    @class(CorruptIEEE8021QbvQueueingBase);
	    
	    @signal[corruption](type=bool);
	    @statistic[corruptionsPerformed](title="Corruptions Performed"; source=corruption; record=vector; interpolationmode=none;);
	    
	    volatile double corruptionProbability = default(1);
	    volatile double corruptionMinInterval @unit(s) = default(0s);
	    string corruptionDestAddress = default("");
	    string corruptionSrcAddress = default("");
	    int corruptionPriority = default(-1);
	    int corruptionVid = default(-1);
	    volatile int corruptionPayload @unit(Byte) = default(0Byte);
}