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
// TODO auto-generated module
//
simple TicApp extends TTEApplicationBase
{
    parameters:
    	@class(TicApp);
    	//Statistic of the amount of packets that were received by the application
        @statistic[rxPk](title="RX Packets"; record=count,vector);
        //Application Roundtrip Time
        @statistic[roundtrip](title="Roundtrip time"; unit=s; record=stats,histogram,vector);
        int counter = 0;
        int ct_id;
        int action_time;
}
