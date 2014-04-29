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

import core4inet.linklayer.inControl.base.BE_InControl;
import inet.linklayer.IOutputQueue;

//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when critical traffic to the CTC module (via sendDirect).
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple CT_BE_InControl extends BE_InControl
{
    parameters:
        @display("i=block/classifier");
        @class(CT_BE_InControl);
        //Statistic of the amount of packets that were dropped due to no configured buffer/ctc
        @signal[ctDropped](type=EtherFrame);
        @statistic[ctDropped](title="Unconfigured CT dropped"; source=droppedPk; record=count; interpolationmode=none);

        @signal[rxPk](type=EtherFrame);
        //Bandwidthstatistic
        @statistic[intervalBandwidth](title="Bandwidth per Second"; source=rxPk; record=count,"sum(packetBytes)","vector(packetBytes)","floatingIntervalCountVector(packetBytes)?","floatingIntervalSumVector(packetBytes)?","floatingIntervalAvgVector(packetBytes)?"; interpolationmode=none); //possible parameter e.g.: interval=50ms; for floatingIntervalRecorders

		//Critical traffic marker of the buffer
        int ct_marker;
        //Critical traffic mask of the buffer
        int ct_mask;
        //Comma seperated list of ctc modules the input uses
        string ct_incomings = default("");
}
