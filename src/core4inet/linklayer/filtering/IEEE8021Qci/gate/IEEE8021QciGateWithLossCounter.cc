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

#include "IEEE8021QciGateWithLossCounter.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciGateWithLossCounter);

simsignal_t IEEE8021QciGateWithLossCounter::zeroFramesPassedInOpenPhaseSignal = registerSignal("zeroFramesPassedInOpenPhase");
simsignal_t IEEE8021QciGateWithLossCounter::noOfFramesMissedInOpenPhaseSignal = registerSignal("noOfFramesMissedInOpenPhase");

void IEEE8021QciGateWithLossCounter::close()
{
    IEEE8021QciGate::close();
    if (this->numFramesPassed == this->lastNumFramesPassed)
    {
        this->emit(this->zeroFramesPassedInOpenPhaseSignal, 1UL);
    }
    if ((this->numFramesPassed - this->lastNumFramesPassed - this->deviationOfExpextedNumberOfFrames) < this->expectedNumberOfFramesPerOpenPhase)
    {
        this->emit(this->noOfFramesMissedInOpenPhaseSignal, this->expectedNumberOfFramesPerOpenPhase - (this->numFramesPassed - this->lastNumFramesPassed - this->deviationOfExpextedNumberOfFrames));
    }
    this->lastNumFramesPassed = this->numFramesPassed;
}

void IEEE8021QciGateWithLossCounter::initialize()
{
    IEEE8021QciGate::initialize();
    this->lastNumFramesPassed = this->numFramesPassed;
}

void IEEE8021QciGateWithLossCounter::handleParameterChange(const char *parname)
{
    IEEE8021QciGate::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "expectedNumberOfFramesPerOpenPhase"))
    {
        this->expectedNumberOfFramesPerOpenPhase = this->par("expectedNumberOfFramesPerOpenPhase").intValue();
    }
    if (!parname || !strcmp(parname, "deviationOfExpextedNumberOfFrames"))
    {
        this->deviationOfExpextedNumberOfFrames = this->par("deviationOfExpextedNumberOfFrames").intValue();
    }
}

} //namespace
