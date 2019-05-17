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

package core4inet.linklayer.shaper.IEEE8021Qbv.selection;

//
// @author Philipp Meyer
//
simple IEEE8021QbvSelection like IIEEE8021QbvSelection
{
    parameters:
        @display("i=block/join");
        int numPCP = default(8);
    gates:
        input in @label(EtherFrame) @directIn;
        output out @labels(EtherFrame);
}