package ttethernet.buffer.AS6802;

//
// Represents a double buffer for rate-constrained traffic. Messages are sent using the configured
// gandwidth alocation gap.
//
// The buffer stores only one message at a time that is overwritten on each insert.
// The buffer sends a copy of the stored frame after each bag.
//
// @see RCBuffer, Buffer,
//
// @author Till Steinbach
simple RCDoubleBuffer extends RCBuffer
{
    //RCDoubleBuffer is implemented by the RCDoubleBuffer C++ Class
    @class(RCDoubleBuffer);
    
}
