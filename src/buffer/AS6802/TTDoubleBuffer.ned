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
package core4inet.buffer.AS6802;

//
// Represents a double buffer for time-triggered traffic. Messages are sent using the configured
// send window.
//
// The buffer stores only one message at a time that is overwritten on each insert.
// The buffer sends a copy of the stored frame after each bag.
//
// @see TTBuffer, Buffer,
//
// @author Till Steinbach
simple TTDoubleBuffer extends TTBuffer
{
    //TTDoubleBuffer is implemented by the TTDoubleBuffer C++ Class
    @class(TTDoubleBuffer);

}
