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
// Module that matches on the VLAN id and pcp in  a IEEE 802.1Qci stream filter.
//
// @see ~DestMACFilter, ~IEEE8021QciFilter
//
// @author Philipp Meyer
//
simple QTagFilter extends DestMACFilter
{
    parameters:
        @class(QTagFilter);
        // VLAN id of the stream filter
        int vID = default(-1);
        // PCP of the stream filter
        int pcp = default(-1);
}
