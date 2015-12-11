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

import core4inet.applications.base.ApplicationBase;

//
// Abstract base traffic source application used for various traffic generators.
// Uses CTFrame with encapsulated cPacket as payload
// Since this is an abstract module please do not instantiate it
//
// @see ~ApplicationBase, ~TTTrafficSourceApp, ~RCTrafficSourceApp
//
// @author Till Steinbach
//
simple TrafficSourceAppBase extends ApplicationBase
{
    parameters:
        @class(AbstractSimpleModule);
        @display("i=block/source");

        // Trafficsource enabled or disabled
        bool enabled = default(true);
        // Start time
        double startTime @unit(s) = default(0s);
        //Size of the payload of the message (size of encapsulated cPacket) that is being generated
        volatile int payload @unit(Byte) = default(46Byte);
        
        @signal[payloadSignal];
        @statistic[payloadOverTime](title="payload over time"; source=payloadSignal; unit=B; record=stats?,histogram?,vector?; interpolationmode=linear);
}
