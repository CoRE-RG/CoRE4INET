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

//
// A Shaper that handles TT, AVB, PCF, RC and BE traffic
// This shaper handles traffic in the following order (highest to lowest priority):
// - time-triggered
// - AVB Class A
// - AVB Class B
// - PCF
// - rate-constrained
// - best-effort
//
// @see ~TT_AVBClassA_PCF_RC_BE_Shaper
//
// @author Philipp Meyer
//
simple TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper extends TT_AVBClassA_PCF_RC_BE_Shaper
{
    parameters:
        @display("i=block/classifier");
        @class(TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper);
        
        //Signal emitted when queue length of the avb queue changes, contains new queue length
        @signal[avbBQueueLength](type=unsigned long; unit=packets);
        //Statistic of the queue length of time-triggered frames
        @statistic[avbBQueueLength](title="AVBB-Queue Length"; unit=packets; record=vector,stats; interpolationmode=sample-hold);

    gates:
        //Input for AVB class B frames from the buffers
        input AVBBin @labels(TTFrame);
}
