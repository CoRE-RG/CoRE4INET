package ttethernet.buffer.AS6802;

//
// Represents a queue buffer for time-triggered traffic. Messages are sent using the configured
// send window.
//
// The buffer stores infinit messages in a fifo queue.
// The buffer removes and sends the first message in the queue.
//
// @see TTBuffer, Buffer,
//
// @author Till Steinbach
simple TTQueueBuffer extends TTBuffer
{
    parameters:
        //TTQueueBuffer is implemented by the TTQueueBuffer C++ Class
        @class(TTQueueBuffer);
        @display("q=frames");
        //Statistic of the queue length of the buffer
        @statistic[queueLength](title="Queue Length"; record=vector; interpolationmode=sample-hold);
        //Statistic of the amount of packets that were dropped due to buffer overflows
        @statistic[ctDropped](title="CT dropped"; record=sum);
        //Size of the buffer negative means infinite
        int size = default(-1);
    	//Dropping policy, Should the newest frame instead of the oldest frame be dropped when the buffer is full (see size parameter)
        bool drop_new = default(false);
}