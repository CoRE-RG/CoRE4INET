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
package core4inet.buffer.AS6802;

import core4inet.buffer.base.Buffer;


//
// Abstract base Buffer used for critical traffic Buffers of TTEthernet.
// Since this is an abstract module please do not instantiate it
//
// @warning Currently the out gate is not used. Instead the buffer sends its
// message via sendDirect to all via addDestinationGate() registred gates.
//
// @todo The CTBuffer module should be converted to an interface since it should
// not be used directly in simulation.
//
// @see Buffer
//
// @author Till Steinbach
simple CTBuffer extends Buffer
{
    parameters:
        @display("i=block/buffer");
        //Priority of the buffer (currently only used for rate-constrained traffic)
        int priority = default(-1);
        //Critical traffic ID of the buffer
        int ct_id;
        //Critical traffic marker of the buffer
        int ct_marker;
        //Critical traffic mask of the buffer
        int ct_mask;

}
