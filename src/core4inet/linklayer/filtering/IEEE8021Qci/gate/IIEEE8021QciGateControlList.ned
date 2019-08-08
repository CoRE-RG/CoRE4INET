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

import core4inet.utilities.classes.IScheduled;

//
// Interface to be implemented by IEEE 802.1Qci gate control list modules.
//
// @warning Since this is an abstract module please do not instantiate it!
//
// @see ~IEEE8021QciGateControlList, ~IScheduled
//
// @author Philipp Meyer
//
moduleinterface IIEEE8021QciGateControlList extends IScheduled
{
    parameters:
        @display("i=block/table");
        
    gates:
         // Input gate for the incoming SchedulerTimerEvent messages
        input schedulerIn @directIn;
}
