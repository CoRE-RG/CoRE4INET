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
package core4inet.linklayer.inControl;

import core4inet.linklayer.inControl.base.BE_InControl;


//
// Module for incoming traffic from MAC layer. The traffic is checked for
// critical traffic ID and then forwarded either as best-effort traffic to
// the upper layer or when critical traffic to the CTC module (via sendDirect).
//
// @see EtherLLC, IMacRelayUnit, IOutputQueue
//
// @author Till Steinbach
simple CT_BE_InControl extends BE_InControl
{
    parameters:
        @display("i=block/classifier");
        @class(CT_BE_InControl);
        //Statistic of the amount of packets that were dropped due to no configured buffer/ctc
        @signal[ctDropped](type=EtherFrame);
        @statistic[ctDropped](title="Unconfigured CT dropped"; source=droppedPk; record=count; interpolationmode=none);

        @signal[rxPk](type=EtherFrame);
       
       //Statistic of the End-to-end latency for each packet that is received by the buffer
       	@statistic[latencyReceive](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram,vector; interpolationmode=none);
        
        //Statistic of the End-to-end latency for each packet when it lefts the buffer
        @statistic[jitterTransmit](title="Jitter for transmitted Packets"; source="SubtractActualFromLast(messageAge(txPk))"; unit=s; record=count,min,max,vector; interpolationmode=none);

		//Statistic for the variance of the end-to-end latency for received and transmitted packets
        @statistic[jitterReceive](title="Jitter for received Packets"; source="SubtractActualFromLast(messageAge(rxPk))"; unit=s; record=count,min,max,vector; interpolationmode=none);
        @statistic[latencyTransmit](title="End-to-end latency"; source="messageAge(txPk)"; unit=s; record=stats,histogram,vector; interpolationmode=none);

         //Statistic of the amount of packets that were receive for each interval
        @statistic[availableBandwidth](title="Available Bandwidth for each Interval in Percent"; source=rxPk; record=count,"IntervalAvailableBandwidthPercent(packetBits)?"; interpolationmode=none);
        @statistic[linkUtilization](title="Link usage for each Interval in Percent"; source=rxPk; record=count,"IntervalSumVectorPercent( packetBits )?"; interpolationmode=none);
        
        //Statistics the size of packets that were received for each interval
        @statistic[bandwidthInterval](title="Bandwidth for each Interval"; source=rxPk; record=count, "IntervalCountVector(packetBytes)?", "IntervalSumVector(packetBytes)?", "IntervalAvgVector(packetBytes)?", "IntervalMinVector(packetBytes)?", "IntervalMaxVector(packetBytes)?", "IntervalVarianceVector(packetBytes)?"; interpolationmode=none);
         //Records the capacity for each packet that is received by the buffer. The Capacity is the relation between payload and packetsize
        @statistic[capacityInterval](title="Capacity for each Interval"; source=rxPk; record=count,"IntervalCapacityRecorder(packetBytes(innerMessage))?","IntervalCountVector(packetBytes(innerMessage))?","IntervalSumVector(packetBytes(innerMessage))?","IntervalAvgVector(packetBytes(innerMessage))?","IntervalMinVector(packetBytes(innerMessage))?","IntervalMaxVector(packetBytes(innerMessage))?","IntervalVarianceVector(packetBytes(innerMessage))?"; interpolationmode=none);
       
        //Floating Statistics (Slower)
        @statistic[bandwidthIntervalFloating](title="Floating Bandwidth for each Interval"; source=rxPk; record=count,"sum(packetBytes)?","vector(packetBytes)?","floatingIntervalCountVector(packetBytes)?","floatingIntervalSumVector(packetBytes)?","floatingIntervalAvgVector(packetBytes)?"; interpolationmode=sample-hold);
        @statistic[capacityIntervalFloating](title="Floating Capacity for each Interval"; source=rxPk; record=count,"floatingIntervalCapacityRecorder(innerMessagePacketBytes)?","sum(innerMessagePacketBytes)?","vector(innerMessagePacketBytes)?","floatingIntervalCountVector(innerMessagePacketBytes)?","floatingIntervalSumVector(innerMessagePacketBytes)?","floatingIntervalAvgVector(innerMessagePacketBytes)?"; interpolationmode=sample-hold);
        @statistic[availableBandwidthFloating](title="Available Bandwidth for each Interval in Percent"; source=rxPk; record=count,"floatingIntervalAvailableBandwidthPercent(packetBits)?"; interpolationmode=none);
        @statistic[linkUtilizationFloating](title="Link usage for each Interval in Percent"; source=rxPk; record=count,"floatingIntervalSumVectorPercent( packetBits )?"; interpolationmode=none);


		//Critical traffic marker of the buffer
        int ct_marker;
        //Critical traffic mask of the buffer
        int ct_mask;
        //Comma seperated list of ctc modules the input uses
        string ct_incomings = default("");
}
