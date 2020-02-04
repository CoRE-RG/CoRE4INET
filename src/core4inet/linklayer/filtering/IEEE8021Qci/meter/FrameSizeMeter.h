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

#ifndef CORE4INET_FRAMESIZEMETER_H_
#define CORE4INET_FRAMESIZEMETER_H_

//CoRE4INET
#include "core4inet/linklayer/filtering/IEEE8021Qci/meter/IEEE8021QciMeter.h"

namespace CoRE4INET {

/**
 * @brief Class representing the experimental FrameSizeMeter module
 *
 * @author Philipp Meyer
 *
 * @sa IEEE8021QciMeter
 */
class FrameSizeMeter : public virtual IEEE8021QciMeter
{
  private:
    /**
     * Caches minFrameSize parameter
     */
    size_t minFrameSize;
    /**
     * Caches maxFrameSize parameter
     */
    size_t maxFrameSize;

  protected:
    /**
     * @brief Initializes the FrameSizeMeter
     */
    virtual void initialize() override;
    /**
     * @brief Handles the incoming and outgoing messages of the FrameSizeMeter
     *
     * @param msg incoming IEE8021QciCtrl for the FrameSizeMeter
     */
    virtual void handleMessage(cMessage *msg) override;
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname) override;
};

} //namespace

#endif
