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

#ifndef __CORE4INET_IEEE8021QCIFILTER_H_
#define __CORE4INET_IEEE8021QCIFILTER_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/base/avb/AVBDefs.h"
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/gate/IEEE8021QciGate.h"
//Auto-generated Messages
#include "core4inet/linklayer/filtering/IEEE8021Qci/IEEE8021QciCtrl_m.h"

namespace CoRE4INET {

/**
 * @brief Class representing the IEEE 802.1Qci stream filter module
 *
 * @author Philipp Meyer
 */
class IEEE8021QciFilter : public virtual cSimpleModule
{
  private:
    /**
     * @brief Stream ID of the stream filter
     */
    unsigned long streamID;
    /**
     * @brief Gate ID responsible for the stream
     */
    unsigned int gateID;
    /**
     * @brief Meter ID responsible for the stream
     */
    unsigned int meterID;

  public:
    /**
     * @brief Get stream ID
     *
     * @return stream ID
     */
    unsigned long getStreamID()
    {
        return this->streamID;
    }
    /**
    * @brief Get gate ID
    *
    * @return gate ID
    */
    unsigned int getGateID()
    {
        return this->gateID;
    }
    /**
    * @brief Get meter ID
    *
    * @return meter ID
    */
    unsigned int getMeterID()
    {
        return this->meterID;
    }

  protected:
    /**
     * @brief Initialize the module
     */
    virtual void initialize();
    /**
     * @brief Reveives messages from the IEEE 802.1Qci input module encapsulates control data and forwards them to the responsible stream gate
     *
     * @param msg the incoming message
     */
    virtual void handleMessage(cMessage *msg);
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char *parname);
};

} //namespace

#endif
