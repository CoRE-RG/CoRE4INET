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

package core4inet.linklayer.filtering.IEEE8021Qci.filter;

//
// Base module for IEEE 802.1Qci filter. Forwards all messages to the configured stream gate.
//
// @see ~IIEEE8021QciFilter
//
// @author Philipp Meyer
//
simple IEEE8021QciFilter like IIEEE8021QciFilter
{
    parameters:
        @display("i=block/table");
        // Stream ID of the stream filter
        int streamID = default(0);
        // Gate ID responsible for the stream
        int gateID = default(-1);
        // Meter ID responsible for the stream
        int meterID = default(-1);
        
    gates:
        // Input of the stream filter
        input in;
}
