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
package core4inet.linklayer.port;


//
// Interface of TTEthernet ports. A port is a virtual instance that can receive
// critical traffic through its gates.
//
// Modules implementing IPort are not necessarily physical ports.
//
// @see TTEPHYPort, Sync, IApplication
//
// @author Till Steinbach
moduleinterface IPort
{
    gates:
        //Input for time-triggered traffic
        input TTin @directIn @labels(TTFrame);
        //Input for rate-constrained traffic
        input RCin @directIn @labels(RCFrame);
}
