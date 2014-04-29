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

package core4inet.buffer.avb;

//
// Represents a queue buffer for time-triggered traffic. Messages are sent using the Credit Based Shaper Algorithm.
//
// The buffer stores infinit messages in a fifo queue.
// The buffer removes and sends the first message in the queue.
//
// @see AVBBuffer, Buffer,
//
// @author Philipp Meyer
simple AVBQueueBuffer extends AVBBuffer
{
    parameters:
        @class(AVBQueueBuffer);
        @display("q=frames");
        //Signal emitted when queuelength changes, contains new length
        @signal[queueLength](type=unsigned long);
        //Statistic of the queue length of the buffer
        @statistic[queueLength](title="Queue Length"; record=vector; interpolationmode=sample-hold);

        //Size of the buffer negative means infinite
        int size = default(-1);
}
