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

import core4inet.linklayer.filtering.IEEE8021Qci.gate.IIEEE8021QciGateControlList;

//
// Module that stores a IEEE 802.1Qci gate control list and propagates its states to the gates over time.
//
// @see ~IIEEE8021QciGateControlList, ~IIEEE8021QviGate, ~IEEE8021QviGate
//
// @author Philipp Meyer
//
simple IEEE8021QciGateControlList like IIEEE8021QciGateControlList
{
    parameters:
        @class(IEEE8021QciGateControlList);
        @display("i=block/table");
        // Control list (Syntax: <controlListRow[0]{<gate[0]State>,...,<gate[numGates]State>:<activationTimeInPeriod>}>;<controlListRow[1]>;...;<controlListRow[n];)
        string controlList = default("");
        // Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("^.^.^.scheduler.oscillator");
        // Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("^.^.^.scheduler.timer");
        //Period of Scheduler this gate control list is assigned to
        string period = default("period[0]");
        
    gates:
        // Input gate for the incoming SchedulerTimerEvent messages
    	input schedulerIn @directIn;        
}
