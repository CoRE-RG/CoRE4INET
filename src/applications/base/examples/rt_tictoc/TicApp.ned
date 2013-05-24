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

package ttethernet.applications.base.examples.rt_tictoc;

import ttethernet.applications.base.TTEApplicationBase;

//
// Tic Application used for the rt_tictoc example.
// Sends TT messages with Tic-Request payload and receives
// RC messages with Toc-Response payload.
//
//
// @see rt_tictoc, TocApp
//
// @author Till Steinbach
simple TicApp extends TTEApplicationBase
{
    parameters:
        @class(TicApp);
        @display("i=block/routing,cyan");
        //Statistic of the amount of packets that were received by the application
        @statistic[rxPk](title="RX Packets"; record=count,vector);
        //Application Roundtrip Time
        @statistic[roundtrip](title="Roundtrip time"; unit=s; record=stats,histogram,vector);
        //Counter is increased on incoming Tic messages
        int counter = 0;
        //CT-ID used for the messages to send
        int ct_id;
        //Time in cycle when the tic message is generated
        int action_time @unit(tick);
}
