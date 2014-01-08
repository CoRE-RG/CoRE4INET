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
package core4inet.linklayer.shaper.base;

//A Shaper for best-effort messages.
//
//The BE_Shaper only handles best-effort traffic
//
// @see IShaper
//
// @author Till Steinbach
//
simple BE_Shaper like IShaper
{
    parameters:
        @class(BE_Shaper);
        @display("i=block/classifier");
        //Signal emitted when queue length of the be queue changes, contains new queue length
        @signal[beQueueLength](type=unsigned long);
        //Statistic of the queue length of best-effort frames
        @statistic[beQueueLength](title="BE-Queue Length"; record=vector; interpolationmode=sample-hold);

    gates:
        //Input for best-effort frames from the upper layer (EtherLLC or IMacRelayUnit)
        input in @labels(EtherFrame);
        //Output to the lower layer (MAC layer)
        output out @labels(EtherFrame);
}
