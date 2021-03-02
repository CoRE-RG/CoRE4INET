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

package core4inet.linklayer.filtering.IEEE8021Qci.gate;

//
// TODO auto-generated module
//
simple IEEE8021QciGateWithLossCounter extends IEEE8021QciGate
{
    parameters:
        @class(IEEE8021QciGateWithLossCounter);
        @signal[zeroFramesPassedInOpenPhase](type=unsigned long);
        @signal[noOfFramesMissedInOpenPhase](type=unsigned long);
        @statistic[zeroFramesPassedInOpenPhases](titel="zero frames passed in open phases"; source=zeroFramesPassedInOpenPhase; record=count,vector; interpolationmode=none;);
        @statistic[noOfFramesMissedInOpenPhases](title="number of frames missed in open phases"; source=noOfFramesMissedInOpenPhase; unit=packets; record=count,vector; interpolationmode=none;);
		int expectedNumberOfFramesPerOpenPhase = default(1);
		int deviationOfExpextedNumberOfFrames = default(0);
}
