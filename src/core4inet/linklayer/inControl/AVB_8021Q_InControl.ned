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

package core4inet.linklayer.inControl;

import core4inet.linklayer.inControl.IEEE8021Q.IEEE8021Q_InControl;

//
// Module for incoming traffic from MAC layer. The traffic is checked for
// type and then forwarded either as common Q traffic to
// the upper layer or avb to the CTC module (via sendDirect).
//
// @see ~IEEE8021Q_InControl, ~EtherLLC, ~IMacRelayUnit, ~IOutputQueue
//
// @author Philipp Meyer
//
simple AVB_8021Q_InControl extends IEEE8021Q_InControl
{
 	parameters:
 	    @display("i=block/classifier");  
 	    @class(AVB_8021Q_InControl);
}