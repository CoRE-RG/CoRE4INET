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

package core4inet.applications.examples.rt_tictoc;

import core4inet.applications.AS6802.CTApplicationBase;

//
// Toc Application used for the rt_tictoc example.
// Receives TT messages with Tic-Request payload and answers
// with RC messages with Toc-Response payload.
//
//
// @see rt_tictoc, TicApp
//
// @author Till Steinbach
simple TocApp extends CTApplicationBase
{
    parameters:
        @class(TocApp);
        @display("i=block/routing,gold");
        //Counter is increased on incoming Tic messages
        int counter = 0;
        //CT-ID used for the messages to send
        int ct_id;
}
