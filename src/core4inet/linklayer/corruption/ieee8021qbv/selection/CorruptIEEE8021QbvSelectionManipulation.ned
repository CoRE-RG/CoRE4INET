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

package core4inet.linklayer.corruption.ieee8021qbv.selection;

import core4inet.linklayer.corruption.ieee8021qbv.selection.CorruptIEEE8021QbvSelectionBase;

//
// Module for the manipulation of network traffic at IEEE 802.1Qbv traffic selection level
//
// @author Philipp Meyer
//
simple CorruptIEEE8021QbvSelectionManipulation extends CorruptIEEE8021QbvSelectionBase
{
    parameters:
        @class(CorruptIEEE8021QbvSelectionManipulation);
        
        string manipulationDestAddress = default("");
	    string manipulationSrcAddress = default("");
	    int manipulationPriority = default(-1);
	    int manipulationVid = default(-1);
	    volatile int manipulationPayload @unit(Byte) = default(0Byte);
}
