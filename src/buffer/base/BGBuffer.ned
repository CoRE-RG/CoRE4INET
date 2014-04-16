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
package core4inet.buffer.base;

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
