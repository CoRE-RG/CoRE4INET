//
// The message is sent by an empty TTBuffer instead of a time-triggered message, to inform
// the outgoing port that the reserved bandwidth may be used by other frames.
//
// @see TTQueueBuffer, TTBuffer,
//
// @author Till Steinbach
message TTBufferEmpty
{    
    //string displayString="b=15,15,rect,white,kind,5";
}
