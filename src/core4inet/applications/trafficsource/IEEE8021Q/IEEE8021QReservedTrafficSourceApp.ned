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

package core4inet.applications.trafficsource.IEEE8021Q;

import core4inet.applications.trafficsource.IEEE8021Q.IEEE8021QTrafficSourceApp;
import core4inet.utilities.classes.ITimed;

//
// Traffic source application used for asynchronous SRP reserved IEEE 802.1Q traffic
//
// @see ~IEEE8021QTrafficSourceApp, ~ITimed, ~AVBTrafficSourceApp, ~BGTrafficSourceApp
//
// @author Timo Häckel
//
simple IEEE8021QReservedTrafficSourceApp extends IEEE8021QTrafficSourceApp like ITimed
{
    parameters:
        @class(IEEE8021QReservedTrafficSourceApp);
        // interval between sending frames
        sendInterval = default(0s); // if sendInterval is 0, intervalFrames and srClass interval will define it
        // ID of the AVB Stream
        int streamID = default(0);     
        // Stream Reservation Class of the AVB Stream
        string srClass = default("A");
        // Number of frames per interval
        int intervalFrames = default(1);     
        // Variation of frame forwarding interval
        volatile double intervalInaccurracy @unit(s) = default(0s);     
        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("^.scheduler.oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("^.scheduler.timer");
        // Is statically reserved, if true no talker advertise will be sent 
        bool isStatic = default(false);   
        // path to the srpTable module in the node
        string srpTable = default("^.srpTable");
}
