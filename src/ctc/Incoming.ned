package ttethernet.ctc;
import inet.networklayer.queue.IOutputQueue;

//
// Abstract module for the conformance checks of incoming traffic.
//
// @warning Since this is an abstract module do not instantiate it! Use RCIncoming or
// TTIncoming instead!
//
// @todo Since this is an abstract module it might be better to make an interface 
//
// @see RCIncoming, TTIncoming,
//
// @author Till Steinbach
simple Incoming like IOutputQueue
{
    //Incoming is implemented by the Incoming C++ Class
    @class(Incoming);
    @display("i=device/firewall");
    gates:
        //input of the ctc
        input in @directIn @labels(CTFrame);
        //output of the ctc
        output out @labels(CTFrame);
}
