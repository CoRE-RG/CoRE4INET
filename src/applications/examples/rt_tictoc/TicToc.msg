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

namespace CoRE4INET;

//
// Messages for the rt_tictoc Examples
//
// @author Till Steinbach
//
packet TicToc {
    //All messages use minimum size payload
    byteLength = 46;
    //Counter transportet through the network
    unsigned int count = 0;
    //Start time to calculate roundtrip time
    simtime_t roundtrip_start;
}

//
// Tic-Message for the rt_tictoc Examples
//
// @author Till Steinbach
//
packet Tic extends TicToc{
    //Request message
    string request = "Hello!";
}

//
// Toc-Message for the rt_tictoc Examples
//
// @author Till Steinbach
//
packet Toc extends TicToc{
    //Response message
    string response = "World!";
}