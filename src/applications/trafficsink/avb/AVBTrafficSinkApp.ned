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

package core4inet.applications.trafficsink.avb;

import core4inet.applications.trafficsink.base.TrafficSinkApp;

//
// Traffic sink application used for statistics collection of AVB traffic.
//
// The module waits until a talker with the specified stream id was registered at the srpTable, then
// registeres itself as a listener for the stream and waits for incoming frames to record statistics
//
// @see TrafficSinkApp
//
// @author Till Steinbach
simple AVBTrafficSinkApp extends TrafficSinkApp
{
    parameters:
        @class(AVBTrafficSinkApp);
        @display("i=block/sink,blue");
        // ID of the AVB Stream
        int streamID;
        // VLAN identifier of the AVB Stream
        int vlan_id = default(2);
        //Interval in which a subscription is updated
        double updateInterval @unit("s") = default(6s);
        //Interval in which a subscription is reregistered after a timeout
        double retryInterval @unit("s") = default(1s);
    gates:
        // Gate for incoming AVB frames
        input AVBin @directIn;
}
