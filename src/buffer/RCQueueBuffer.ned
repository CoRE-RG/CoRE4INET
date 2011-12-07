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
    //RCQueueBuffer is implemented by the RCQueueBuffer C++ Class
    @class(RCQueueBuffer);
    @display("q=frames");
    //Statistic of the queue length of the buffer
    @statistic[queueLength](title="Queue Length"; record=vector; interpolationmode=sample-hold);
    
}