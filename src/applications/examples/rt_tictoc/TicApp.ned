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
import core4inet.utilities.classes.IScheduled;

//
// Tic Application used for the rt_tictoc example.
// Sends TT messages with Tic-Request payload and receives
// RC messages with Toc-Response payload.
//
//
// @see rt_tictoc, TocApp
//
// @author Till Steinbach
simple TicApp extends CTApplicationBase like IScheduled
{
    parameters:
        @class(TicApp);
        @display("i=block/routing,cyan");
		//Signal emitted when a frame is received, contains received EtherFrame
        @signal[rxPk](type=EtherFrame);
        //Signal emitted when a frame is received, contains roundtrip time
        @signal[roundtrip](type=simtime_t);
		//Statistic of the amount of packets that were received by the application
        @statistic[rxPk](title="RX Packets"; source=rxPk; record=count,"sum(packetBytes)","vector(packetBytes)","floatingIntervalCountVector(packetBytes)?","floatingIntervalSumVector(packetBytes)?","floatingIntervalAvgVector(packetBytes)?"; interval=1s; interpolationmode=none);
        //Statistic of the applications roundtrip time
        @statistic[roundtrip](title="Roundtrip time"; unit=s; record=stats,histogram,vector);
        //Counter is increased on incoming Tic messages
        int counter = 0;
        //CT-ID used for the messages to send
        int ct_id;
        //Time in cycle when the tic message is generated
        int action_time @unit(tick);

		//Oscillator of the timed module (must be set to the name of an oscillator module in the Node) when left empty: oscillator @see IScheduled
        string oscillator = default("oscillator");
        //Timer of the timed module (must be set to the name of an timer module in the Node) when left empty: timer @see IScheduled
        string timer = default("timer");
        //Period of the scheduled module (must be set to the name of a period module in the Node) when left empty: period[0] @see IScheduled
        string period = default("");
}
