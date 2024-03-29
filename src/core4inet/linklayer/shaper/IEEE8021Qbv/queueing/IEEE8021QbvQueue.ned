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

package core4inet.linklayer.shaper.IEEE8021Qbv.queueing;

import core4inet.buffer.base.BGQueueBuffer;

// A queue buffer module for IEEE 802.1Qbv transmission selection.
//
// @see ~IBuffer, ~BGQueueBuffer
//
// @author Philipp Meyer
//
simple IEEE8021QbvQueue extends BGQueueBuffer
{
    parameters:
        @class(IEEE8021QbvQueue);
        
        //Signal emitted when state changes
        @signal[NF_QBV_STATE_CHANGED](type=long);
        //Statistic of the state
        @statistic[state](title="State"; source=NF_QBV_STATE_CHANGED; record=vector; interpolationmode=sample-hold;);
}
