package ttethernet.buffer;

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
    //BGQueueBuffer is implemented by the BGQueueBuffer C++ Class
    @class(BGQueueBuffer);
    //Statistic of the queue length of the buffer
    @statistic[queueLength](title="Queue Length"; record=vector);
}
