package ttethernet.buffer.base;

//
// Represents an abstract Buffer for background traffic. Messages are sent immediatly to the LLC
//
//
// @warning Do not instantiate the module. Use BGQueueBuffer instead!
//
// @todo The BGBuffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see BGQueueBuffer, Buffer, SchedulerActionTimeEvent, TTEScheduler
//
// @author Till Steinbach
simple BGBuffer extends Buffer
{
        parameters:
        //BGBuffer is implemented by the BGBuffer C++ Class
        @class(BGBuffer);
        @display("i=,green");
}
