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

package core4inet.linklayer.ethernet.avb;

//
// TODO auto-generated module
//
simple SRPEtherEncapAdapter
{
    parameters:
        @class(SRPEtherEncapAdapter);
        @display("i=block/join");
        
    gates:
        //SRP message in from SRP protocol module
        input srpIn;
        //SRP message out to SRP protocol module
        output srpOut;
        
        input encapIn[];
        output encapOut[];
}
