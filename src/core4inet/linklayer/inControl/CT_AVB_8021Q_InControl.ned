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

//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when avb or critical traffic to the CTC module (via sendDirect).
//
// @see ~CT_BE_InControl, ~EtherLLC, ~IMacRelayUnit, ~IOutputQueue
//
// @author Till Steinbach
//
simple CT_AVB_8021Q_InControl extends CT_BE_InControl
{
    parameters:
        @display("i=block/classifier");
        @class(CT_AVB_8021Q_InControl);

        //Untagged VLAN. Untagged incoming frames get tagged with this VLAN.
        int untaggedVID = default(0);
        //Interface allows frames with this VLAN to enter
        string taggedVIDs = default("0");
}
