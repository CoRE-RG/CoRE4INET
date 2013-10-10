package ttethernet.buffer.AS6802;

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
