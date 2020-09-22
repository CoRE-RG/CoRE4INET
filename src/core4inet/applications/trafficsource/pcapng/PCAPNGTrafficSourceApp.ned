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

package core4inet.applications.trafficsource.pcapng;

import core4inet.applications.base.ApplicationBase;

//
// Traffic source application used for pre-recorded traffic from pcap- and pcapng-files.
//
// @author Sandra Reider
//
simple PCAPNGTrafficSourceApp extends ApplicationBase
{
    parameters:
        @class(PCAPNGTrafficSourceApp);
        @display("i=block/source"); // TODO: Farbe wählen. bg -> green, ieeeq -> blue
        
        //Default bgOut is best-effort buffer
        buffers = default("bgOut");

        // Trafficsource enabled or disabled
        bool enabled = default(true);
        // Start time
        double startTime @unit(s) = default(0s);
        // name of pcapng-file
        string pcapngFilename = default("");
        // destination MAC address
        string destAddress = default("auto");
        // destination MAC address
        string filterDestAddress = default("auto");
        // source MAC address
        string filterSrcAddress = default("auto");
        // priority of q-Frames
        int pcp = default(-1); 
    
}
