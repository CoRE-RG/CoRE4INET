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

package core4inet.utilities.classes;

//
// abstract base for a module that uses a scheduler to schedule actions at action points
//
// @author Till Steinbach
//
simple Scheduled extends Timed like IScheduled
{
    parameters:
        @class(Scheduled);
        //Period of the scheduled module (must be set to the name of a period module in the Node) when left empty: period[0]
        string period = default("");
}
