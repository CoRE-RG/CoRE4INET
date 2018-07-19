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

package core4inet.linklayer.filtering;

import core4inet.linklayer.filtering.IEEE8021Qci.IEEE8021QciInput;
import core4inet.linklayer.filtering.IEEE8021Qci.IEEE8021QciOutput;
import core4inet.linklayer.filtering.IEEE8021Qci.filter.IIEEE8021QciFilter;
import core4inet.linklayer.filtering.IEEE8021Qci.gate.IIEEE8021QciGate;
import core4inet.linklayer.filtering.IEEE8021Qci.meter.IIEEE8021QciMeter;

//
// IEEE8021Qci is a compound filtering module implementing the TSN IEEE 802.1Qci Per-Stream Filtering and Policing.
//
// @see ~IFiltering, ~NoFiltering
// 
// @author Philipp Meyer
//
module IEEE8021Qci like IFiltering
{
    parameters:
        @display("i=block/filter");
        // Number of contained stream filters
        int numStreamFilters = default(0);
        // Number of contained stream gates
        int numStreamGates = default(0);
        // Number of contained flow meters
        int numFlowMeters = default(0);

    gates:
        // Input of the filter
        input in;
        // Ouput of the filter
        output out;

    submodules:
        streamInput: IEEE8021QciInput {
            @display("p=50,75");
        }

        streamFilter[numStreamFilters]: <default("IEEE8021QciFilter")> like IIEEE8021QciFilter {
            @display("p=250,100,c,130");
        }

        streamGate[numStreamGates]: <default("IEEE8021QciGate")> like IIEEE8021QciGate {
            @display("p=500,100,c,130");
        }

        flowMeter[numFlowMeters]: <default("IEEE8021QciMeter")> like IIEEE8021QciMeter {
            @display("p=750,100,c,130");
        }

        streamOutput: IEEE8021QciOutput {
            @display("p=950,75");
        }

    connections allowunconnected:
        in --> streamInput.upperLayerIn;
        streamInput.out --> streamOutput.in;
        streamOutput.upperLayerOut --> out;
}
