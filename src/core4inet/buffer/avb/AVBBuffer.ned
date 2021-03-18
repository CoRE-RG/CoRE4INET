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

package core4inet.buffer.avb;
import core4inet.utilities.classes.ITimed;

import core4inet.buffer.base.Buffer;

//
// Represents an abstract buffer for audio-video bridging traffic. Messages are sent using the Credit Based Shaper algorithm.
//
// @warning Do not instantiate the module. Use AVBDoubleBuffer or AVBQueueBuffer instead!
//
// @see AVBQueueBuffer, Buffer, SchedulerActionTimeEvent, Scheduler
//
// @author Philipp Meyer
//
simple AVBBuffer extends Buffer like ITimed
{
    parameters:
        @class(AbstractSimpleModule);
        @display("i=,blue");
        //Signal emitted when the credit of the CBS algorithm changes
        @signal[credit](type=long);
        //Statistic of the credit of the CBS algorithm
        @statistic[credit](title="Credit"; source=credit; unit=b; record=vector; interpolationmode=linear;);

		// Stream Reservation Class of the AVB Buffer
        string srClass = default("A");
        //Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator
        string oscillator = default("^.scheduler.oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer
        string timer = default("^.scheduler.timer");
        
	//SRP Table module, default name is srpTable
        string srpTable = default("^.srpTable");
        
        //SRP Module path, default not found --> getParentModule()->getSubmodule("phy", getIndex())
        string srpModule = default("");
    gates:
        //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn @directIn;
}
