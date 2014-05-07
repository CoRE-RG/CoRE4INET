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

package core4inet.applications.base;

//
// Interface to be implemented by application models.
// Since this is an abstract module please do not instantiate it
//
//
// @see TTEAPIApplicationBase
//
// @author Till Steinbach
moduleinterface IApplication
{
    parameters:
        @display("i=block/app");
        //Comma seperated list of buffer modules the application is allowed to use
        string buffers;
        //Name shown above the module
        string displayName;
    gates:
         //Input gate for the incoming SchedulerActionTimeEvent messages
        input schedulerIn;
}
