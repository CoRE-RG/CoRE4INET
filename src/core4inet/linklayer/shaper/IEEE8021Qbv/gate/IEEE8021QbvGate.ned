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

package core4inet.linklayer.shaper.IEEE8021Qbv.gate;

//
// A gate for the IEEE 802.1Qbv transmission selection with gates
//
// @see ~IIEEE8021QbvGate
//
// @author Philipp Meyer
//
simple IEEE8021QbvGate like IIEEE8021QbvGate
{
    parameters:
        @class(IEEE8021QbvGate);
        
        //Signal emitted when state changes
        @signal[NF_QBV_STATE_CHANGED](type=long);
        //Statistic of the state
        @statistic[state](title="State"; source=NF_QBV_STATE_CHANGED; record=vector; interpolationmode=sample-hold;);
        
        // State of the gate. 'o' (OPEN) or 'C' (CLOSED).
        string state = default("o");
}
