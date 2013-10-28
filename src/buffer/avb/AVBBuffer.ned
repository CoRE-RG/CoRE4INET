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

package ttethernet.buffer.avb;

import ttethernet.buffer.base.Buffer;

//
// Represents an abstract Buffer for audio-video bridging traffic. Messages are sent using the Credit Based Shaper Algorithm.
//
// @warning Do not instantiate the module. Use AVBDoubleBuffer or AVBQueueBuffer instead!
//
// @see AVBDoubleBuffer, AVBQueueBuffer, Buffer, SchedulerActionTimeEvent, Scheduler
//
// @author Philipp Meyer
simple AVBBuffer extends Buffer
{
    parameters:
        @class(AVBBuffer);
        @display("i=,blue");
        
        //Statistic of the credit of the CBS algorithm
        @statistic[credit](title="Credit"; record=vector);
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
