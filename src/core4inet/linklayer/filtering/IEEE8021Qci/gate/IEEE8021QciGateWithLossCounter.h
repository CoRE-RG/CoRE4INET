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

#ifndef __CORE4INET_IEEE8021QCIGATEWITHLOSSCOUNTER_H_
#define __CORE4INET_IEEE8021QCIGATEWITHLOSSCOUNTER_H_

//CoRE4INET
#include "core4inet/linklayer/filtering/IEEE8021Qci/gate/IEEE8021QciGate.h"

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class IEEE8021QciGateWithLossCounter : public virtual IEEE8021QciGate
{
  private:
    static simsignal_t zeroFramesPassedInOpenPhaseSignal;
    static simsignal_t noOfFramesMissedInOpenPhaseSignal;
    unsigned long expectedNumberOfFramesPerOpenPhase;
    unsigned long deviationOfExpextedNumberOfFrames;
    unsigned long lastNumFramesPassed;

  public:
    virtual void close() override;

  protected:
    virtual void initialize() override;
    virtual void handleParameterChange(const char *parname) override;
};

} //namespace

#endif
