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

package ttethernet.applications.trafficsource;

//
//
// @see TrafficSourceAppBase
//
// @author Philipp Meyer
simple AVBTrafficSourceApp extends TrafficSourceAppBase
{
    parameters:
        @class(AVBTrafficSourceApp);
        @display("i=,blue");
        
        bool talker = default(false);
        double advertise_time @unit(s) = default(0);
        double streamID = default(0);
        int intervalFrames  = default(1);
        int frameSize = default(80);
    gates:
        input SRPin @directIn @labels(SRPFrame);
}
