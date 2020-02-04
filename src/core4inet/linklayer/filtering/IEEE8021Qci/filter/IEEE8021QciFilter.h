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

#ifndef CORE4INET_IEEE8021QCIFILTER_H_
#define CORE4INET_IEEE8021QCIFILTER_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/base/avb/AVBDefs.h"
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/gate/IEEE8021QciGate.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
//CoRE4INET Auto-generated Messages
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"
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
    /**
     * @brief Pointer to the SRP Table
     */
    SRPTable *srpTable;

  public:
    /**
     * @brief Match frame against stream filter
     *
     * @param frame to match
     *
     * @return true if frame matches with stream filter
     */
    virtual bool isMatching(inet::EtherFrame* frame);
    long getStreamId() const;
    void setStreamId(long streamId);
    unsigned int getGateId() const;
    void setGateId(unsigned int gateId);
    unsigned int getMeterId() const;
    void setMeterId(unsigned int meterId);

  protected:
    /**
     * @brief Initialize the module
     */
    virtual void initialize();
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char *parname);
    /**
     * @brief Reveives messages from the IEEE 802.1Qci input module encapsulates control data and forwards them to the responsible stream gate
     *
     * @param msg the incoming message
     */
    virtual void handleMessage(cMessage *msg);



};

} //namespace

#endif
