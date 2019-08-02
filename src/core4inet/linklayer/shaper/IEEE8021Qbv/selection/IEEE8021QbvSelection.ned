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

package core4inet.linklayer.shaper.IEEE8021Qbv.selection;

//
// IEEE 802.1Qbv transmission selection.
//
// @see ~IIEEE8021QbvSelection
//
// @author Philipp Meyer
//
simple IEEE8021QbvSelection like IIEEE8021QbvSelection
{
    parameters:
        @display("i=block/join");
        //Signal emitted when a frame is chosen to be forwarded, contains received EtherFrame
        @signal[qPcp*Pk](type=inet::EtherFrame);
        @signal[qPcp*PkAge](type=simtime_t);
        //Statistic of the amount of packets that were received by the application
        @statisticTemplate[qPcpPk](title="Received Packets"; record=count; unit=packets);
        //Statistic of the amount of bytes that were received by the application
        @statisticTemplate[qPcpBytes](title="Received Bytes"; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none); //possible parameter e.g.: **.floatingintervalvectorrecorder-measure-interval = 20ms for floatingIntervalRecorders
        //End-to-end latency
        @statisticTemplate[qPcpLatency](title="End-to-end latency"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        // Number of priorities.
        int numPCP = default(8);
    gates:
        // Input for selected inet::EtherFrame messages.
        input in @label(EtherFrame) @directIn;
        // Output to the MAC module.
        output out @labels(EtherFrame);
}
