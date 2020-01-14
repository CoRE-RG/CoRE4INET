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

package core4inet.linklayer.shaper.IEEE8021Qbv.selectionAlgorithm;

//
// Simple IEEE 802.1Qbv transmission selection algorithm (tsa) module.
//
// This tsa is always open. Can be used as base module for tsa modules.
//
// @see ~IIEEE8021QbvSelectionAlgorithm
//
// @author Philipp Meyer
//
simple IEEE8021QbvSelectionAlgorithm like IIEEE8021QbvSelectionAlgorithm
{
    parameters:
        @class(IEEE8021QbvSelectionAlgorithm);
        
        //Signal emitted when state changes
        @signal[NF_QBV_STATE_CHANGED](type=long);
        
        // State of the gate. 'o' (OPEN) or 'C' (CLOSED).
        string state = default("o");
}
