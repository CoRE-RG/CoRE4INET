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
// Module that matches on the destination MAC address in a IEEE 802.1Qci stream filter.
//
// @see ~IEEE8021QciFilter
//
// @author Philipp Meyer
//
simple MACFilter extends IEEE8021QciFilter
{
    parameters:
        @class(MACFilter);
        // Source MAC address of the stream filter
        string srcAddress = default("00:00:00:00:00:00");
        // Destination MAC address of the stream filter
        string destAddress = default("00:00:00:00:00:00");
}
