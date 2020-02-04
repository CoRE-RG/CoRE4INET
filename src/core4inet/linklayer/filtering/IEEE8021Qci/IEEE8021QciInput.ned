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

package core4inet.linklayer.filtering.IEEE8021Qci;

//
// Input module of the IEEE 802.1Qci filter
//
// @see ~IEEE8021QciOutput
//
// @author Philipp Meyer
//
simple IEEE8021QciInput
{
    parameters:
        @display("i=block/fork");
        // Signal that is emitted when the module drops a frame
        @signal[frameDropped](type=long);
        // Statistic for dropped frames
        @statistic[framesDropped](title="Frames Dropped"; source=frameDropped; unit=B; record=vector; interpolationmode=none;);
        // If all frames that are not matched with a stream filter are dropped
        bool isWhiteList = default(false); 
    gates:
        // Input from upper layer
        input upperLayerIn;
        // Ouput to the ouput module of the IEEE 802.1Qci filter
        output out;
}
