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
package core4inet.buffer.base;

//
// Represents a queue buffer for background traffic. Messages are forwarded immediatly
//
// The buffer stores "size" messages in a fifo queue.
// The buffer removes and sends the first message in the queue.
// The when full the oldest frame is dropped before inserting the new frame. Can be configured to drop new frame instead
// using the dropNew parameter (default: false)
//
// @see BGBuffer, Buffer,
//
// @author Till Steinbach
//
simple BGQueueBuffer extends BGBuffer
{
    parameters:
        @display("q=frames");
        //BGQueueBuffer is implemented by the BGQueueBuffer C++ Class
        @class(BGQueueBuffer);
        
        //Signal emitted when queuelength changes, contains new length
        @signal[length](type=unsigned long; unit=packets);
        //Signal emitted when queuelength changes, contains new size in bytes
        @signal[size](type=unsigned long; unit=B);
        //Signal emitted when frame is dropped due to buffer overflow, contains dropped EtherFrame
        @signal[dropped](type=inet::EtherFrame);
        //Signal emitted when a frame is dequeued, contains the time spent in the queue
        @signal[delay](type=double; unit=s);
        
        //Statistic of the queue length of the buffer
        @statistic[length](title="Queue Length"; source=length; record=vector; unit=packets; interpolationmode=sample-hold);
        //Statistic of the queue size of the buffer in bytes
        @statistic[size](title="Queue Size"; source=size; record=vector; unit=B; interpolationmode=sample-hold);
        //Statistic of the amount of packets that were dropped due to buffer overflows
        @statistic[dropped](title="Dropped frames"; source=dropped; record=count; unit=packets);
        //Statistic of the queueing delay of packets that were dropped due to buffer overflows
        @statistic[delay](title="Queueing delay"; source=delay; record=vector,stats; unit=s);
        
        //Maximum size of the buffer negative means infinite
        int size = default(-1);
        //Dropping policy, Should the newest frame instead of the oldest frame be dropped when the buffer is full (see size parameter)
        bool dropNew = default(false);
}
