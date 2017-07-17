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

package core4inet.linklayer.filtering.IEEE8021Qci.gate;

//
// Base module for IEEE 802.1Qci gate. A incoming message is dropped when the gate is closed and forwarded to the configured flow meter if the gate is in state open.
//
// @see ~IIEEE8021QciGate
//
// @author Philipp Meyer
//
simple IEEE8021QciGate like IIEEE8021QciGate
{
    parameters:
        // State of the gate. O (Open) or C (Closed).
        string state = default("O");
        
    gates:
        input in;
}
