package ttethernet.buffer.base;

//
// Represents a queue buffer for background traffic. Messages are sent immediatly to LLC
//
// The buffer stores infinit messages in a fifo queue.
// The buffer removes and sends the first message in the queue.
//
// @see BGBuffer, Buffer,
//
// @author Till Steinbach
simple BGQueueBuffer extends BGBuffer
{
    parameters:
        //BGQueueBuffer is implemented by the BGQueueBuffer C++ Class
        @class(BGQueueBuffer);
        //Statistic of the queue length of the buffer
        @statistic[queueLength](title="Queue Length"; record=vector; interpolationmode=sample-hold);
        //Statistic of the amount of packets that were dropped due to buffer overflows
        @statistic[ctDropped](title="CT dropped"; record=sum);
        //Size of the buffer negative means infinite
        int size = default(-1);
        //Dropping policy, Should the newest frame instead of the oldest frame be dropped when the buffer is full (see size parameter)
        bool drop_new = default(false);
}
