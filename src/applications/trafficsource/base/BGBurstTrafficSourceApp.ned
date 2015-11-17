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

package core4inet.applications.trafficsource.base;

//
// Background burst traffic source application.
// Uses multiple EtherFrame with encapsulated cPacket as payload to generate bursts
// This generator generates bursts with sendInterval distance
//
//
// @see BGTrafficSourceApp
//
// @author Till Steinbach
simple BGBurstTrafficSourceApp extends BGTrafficSourceApp
{
    parameters:
        @class(BGBurstTrafficSourceApp);
        @display("i=block/source,green");

        // total size of the burst
        int burstSize @unit(byte) = default(1MiB);
        
        @signal[burstSizeSignal];
        @statistic[burstSizeOverTime](title="burst size over time"; source=burstSizeSignal; unit=B; record=stats?,histogram?,vector?; interpolationmode=linear);
}
