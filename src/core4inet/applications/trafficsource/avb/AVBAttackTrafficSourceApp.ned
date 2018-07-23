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

package core4inet.applications.trafficsource.avb;

//
// Module that generates attack pattern stimuli. Also supports valid behavior
//
// @see ~AVBTrafficSourceApp
//
// @author Philipp Meyer
//
simple AVBAttackTrafficSourceApp extends AVBTrafficSourceApp
{
    parameters:
        @class(AVBAttackTrafficSourceApp);
        @display("i=,blue");
        
        // One of the attack pattern: No, SimpleSpam, IntervalSpam, WaitAndSpam
        string attackPattern = default("No");
        // Size of spam in number of frames
        int spamSize = default(0);
        // Wait interval between spams
        volatile double spamWaitInterval @unit(s) = default(125us);        
}
