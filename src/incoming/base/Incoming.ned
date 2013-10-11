//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
package ttethernet.incoming.base;
import inet.linklayer.IOutputQueue;

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
    @display("i=block/arrival");
    //Statistic of the amount of packets that were dropped due to no ct violations
    @statistic[ctDropped](title="CT violation"; record=sum);
    gates:
        //input of the ctc
        input in @directIn @labels(EtherFrame);
        //output of the ctc
        output out @labels(EtherFrame-conn);
}
