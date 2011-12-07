package ttethernet.buffer;

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
    //TTQueueBuffer is implemented by the TTQueueBuffer C++ Class
    @class(TTQueueBuffer);
    @display("q=frames");
    //Statistic of the queue length of the buffer
    @statistic[queueLength](title="Queue Length"; record=vector; interpolationmode=sample-hold);
    
}