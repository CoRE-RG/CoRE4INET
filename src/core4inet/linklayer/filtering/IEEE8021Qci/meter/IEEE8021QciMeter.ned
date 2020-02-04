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

package core4inet.linklayer.filtering.IEEE8021Qci.meter;

//
// Base module for IEEE 802.1Qci meter.
//
// @author Philipp Meyer
//
simple IEEE8021QciMeter like IIEEE8021QciMeter
{
    parameters:
    	@display("b=,,,green");
    	// Signal that is emitted when the module receives a frame
    	@signal[frameReceived](type=long);
        // Signal that is emmitted when the module sends a frame 
    	@signal[frameSent](type=long);
    	// Signal that is emitted when the module drops a frame
        @signal[frameDropped](type=long);
        // Statistic for received frames
        @statistic[framesReceived](title="Frames Received"; source=frameReceived; unit=B; record=vector; interpolationmode=none;);
        // Statistic for send frames
        @statistic[framesSent](title="Frames Send"; source=frameSent; unit=B; record=vector; interpolationmode=none;);
        // Statistic for dropped frames
        @statistic[framesDropped](title="Frames Dropped"; source=frameDropped; unit=B; record=vector; interpolationmode=none;);
        
    gates:
        // Input of the meter module
        input in;
}
