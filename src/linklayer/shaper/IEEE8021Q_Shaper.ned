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
package core4inet.linklayer.shaper;

import core4inet.linklayer.shaper.base.IShaper;

//A Shaper for IEEE802.1Q-tagged messages.
//
//The IEEE8021Q Shaper handles Q-tagged and best-effort traffic
//
// @see IShaper
//
// @author Philipp Meyer
//
simple IEEE8021Q_Shaper like IShaper
{
    parameters:
        @class(IEEE8021Q_Shaper);
        //Signal emitted when queue length of the rc queue changes, contains new queue length
        @signal[q*QueueLength](type=unsigned long);
        //Statistic of the queue length of rate-constrained frames
        @statisticTemplate[qQueueLength](title="Q-Queue Length ($name)"; record=vector; interpolationmode=sample-hold);

    gates:
        //Input for best-effort frames from the upper layer (EtherLLC or IMacRelayUnit)
        input in @labels(EtherFrame);
        //Output to the lower layer (MAC layer)
        output out @labels(EtherFrame);
}
