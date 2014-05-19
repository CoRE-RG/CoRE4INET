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
package core4inet.linklayer.ethernet.base;

import inet.linklayer.ethernet.EtherLLC;

//
// This module forwards frames (~EtherFrame) to the bg buffers
//
//
// @see EtherLLC, SRProtocol
// 
// @author Till Steinbach
//
simple BGEtherLLC extends EtherLLC
{
    parameters:
        @class(BGEtherLLC);
        @display("i=block/fork");
    gates:
        //best-effort message in
        input bgIn @loose;
        //best-effort message out
        output bgOut @loose;
}

