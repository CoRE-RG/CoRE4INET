package ttethernet.buffer;

//
// Represents a queue buffer for rate-constrained traffic. Messages are sent using the configured
// gandwidth alocation gap.
//
// The buffer stores infinit messages in a fifo queue.
// The buffer removes and sends the first message in the queue.
//
// @see RCBuffer, Buffer,
//
// @author Till Steinbach
simple RCQueueBuffer extends RCBuffer
{
    parameters:
        //RCQueueBuffer is implemented by the RCQueueBuffer C++ Class
        @class(RCQueueBuffer);
        @display("q=frames");
        //Statistic of the queue length of the buffer
        @statistic[queueLength](title="Queue Length"; record=vector; interpolationmode=sample-hold);
        //Statistic of the amount of packets that were dropped due to buffer overflows
        @statistic[ctDropped](title="CT dropped"; record=sum);
        //Size of the buffer negative means infinite
        int size = default(-1);
    	//Dropping policy, Should the new frame instead of the oldest frame be dropped
        bool drop_new = default(false);
}