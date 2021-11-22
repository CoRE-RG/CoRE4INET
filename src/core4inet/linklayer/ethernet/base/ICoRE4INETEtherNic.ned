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

package core4inet.linklayer.ethernet.base;

import inet.linklayer.contract.IWiredNic;

//
// Interface for CoRE4INET Ethernet NICs that supports BG apps and the SRP.
//
moduleinterface ICoRE4INETEtherNic extends IWiredNic
{
    parameters:
        @display("i=block/ifcard");
    gates:        
        // background (BE) traffic input
        input bgIn;
        
        // background (BE) traffic out
        output bgOut;
        
        // stream reservation protocol input
        input srpIn;
        
        // stream reservation protocol output
        output srpOut; 
}
 