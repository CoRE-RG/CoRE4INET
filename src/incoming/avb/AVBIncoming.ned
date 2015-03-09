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

package core4inet.incoming.avb;

import core4inet.incoming.base.Incoming;

//
// Module for the conformance checks of incoming audio-video bridging traffic.
//
// TODO: Inheritance: PArent should be base.Incoming
//
// @author Philipp Meyer
simple AVBIncoming extends Incoming
{
    parameters:
        //AVBIncoming is implemented by the AVBIncoming C++ Class
        @class(AVBIncoming);
        @display("i=block/arrival,blue");
        
    gates:
        //outputs for AVB Frames
        output AVBAout[] @labels(AVBFrame);
        output AVBBout[] @labels(AVBFrame);
}
