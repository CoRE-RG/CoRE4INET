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
package core4inet.linklayer.inControl.base;

import core4inet.utilities.classes.Timed;


//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when critical traffic to the CTC module (via sendDirect).
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple BE_InControl extends Timed like IInControl
{
    parameters:
        @display("i=block/classifier");
        @class(BE_InControl);
        // if true, all packets are received, otherwise only the ones with matching destination MAC address (This does not affect CT-Frames)
        bool promiscuous = default(false);
    gates:
        //Input from the lower layer (MAC layer)
        input in @labels(EtherFrame);
        //Output for best-effort frames to the upper layer (EtherLLC or IMacRelayUnit)
        output out @labels(EtherFrame);

}
