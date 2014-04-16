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

package core4inet.applications.trafficsource.avb;

import core4inet.applications.trafficsource.base.TrafficSourceAppBase;
import core4inet.utilities.classes.ITimed;

//
// Traffic source application used for audio-video bridging traffic generators.
//
// @see TrafficSourceAppBase
//
// @author Philipp Meyer
simple AVBTrafficSourceApp extends TrafficSourceAppBase like ITimed
{
    parameters:
        @class(AVBTrafficSourceApp);
        @display("i=,blue");

        // True => AVB Talker / Default False => AVB Listener
        bool talker = default(false);

        // Countdown till first Talker Advertise
        double advertise_time @unit(s) = default(0);

        // ID of the AVB Stream
        double streamID = default(0);

        // Count of send Frames per 125us interval
        int intervalFrames = default(1);

        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("timer");
    gates:
        input SRPin @directIn @labels(SRPFrame);
}
