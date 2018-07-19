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

import core4inet.utilities.classes.ITimed;

//
// The CreditBasedMeter (CBM) is a simple module
// It represents a meter that filters traffic in dependency of a credit value
//
// @see ~IIEEE8021QciMeter, ~IEEE8021QciMeter
//
// @author Philipp Meyer
//
simple CreditBasedMeter extends IEEE8021QciMeter like ITimed
{
    parameters:
        @class(CreditBasedMeter);
        // Signal emitted when the credit of the CBM algorithm changes
        @signal[credit](type=long);
        // Signal that is emitted when the CBM receives a frame
        @signal[frameReceived](type=long);
        // Signal that is emitted when the CBM drops a frame
        @signal[frameDropped](type=long);
        // Statistic for the credit of the CBM algorithm
        @statistic[credit](title="Credit"; source=credit; unit=b; record=vector; interpolationmode=linear;);
        // Statistic for received frames
        @statistic[framesReceived](title="Frames Received"; source=frameReceived; unit=B; record=vector; interpolationmode=none;);
        // Statistic for dropped frames
        @statistic[framesDropped](title="Frames Dropped"; source=frameDropped; unit=B; record=vector; interpolationmode=none;);
        
        // Maximum burst length allowed by the CBM in number of frames
        int maxBurst = default(4);
        // SRClass of the CBM
        string srClass = default("A");
        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("^.^.^.scheduler.oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("^.^.^.scheduler.timer");
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
