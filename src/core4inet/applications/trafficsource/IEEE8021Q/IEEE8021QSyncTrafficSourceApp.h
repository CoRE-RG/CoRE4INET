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

#ifndef CORE4INET_IEEE8021QSCHEDULEDTRAFFICSOURCEAPP_H_
#define CORE4INET_IEEE8021QSCHEDULEDTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "core4inet/applications/trafficsource/IEEE8021Q/IEEE8021QTrafficSourceApp.h"
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/utilities/classes/Scheduled.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @brief IEEE802.1Q synchronized traffic source
 *
 * Generates and Sends Q-tagged Ethernetframes based on a synchronized period.
 *
 * @ingroup IEEE8021Q
 *
 * @author Philipp Meyer, Timo Haeckel
 */
class IEEE8021QSyncTrafficSourceApp : public virtual IEEE8021QTrafficSourceApp, public virtual Scheduled, public virtual cListener
{
  private:
    /**
     * @brief caches action_time parameter
     */
    double actionTime;
    /**
     * @brief Caches modulo parameter
     */
    unsigned int modulo;
    /**
     * @brief true when node is synchronized (Frames will be only sent when node runs synchronous)
     */
    bool synchronized;
    /**
     * @brief next scheduled cycle to send a message
     * prevents multiple messages being send in the same cycle, e.g. through clock sync
     * uses modulo parameter to skip cycles if needed
     */
    uint32_t nextCycle;

  public:
    IEEE8021QSyncTrafficSourceApp();

  protected:
    virtual void initialize() override;
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname) override;
    /**
     * @brief handle self messages to send frames
     *
     * @param msg incoming self messages
     */
    virtual void handleMessage(cMessage *msg) override;
    /**
     * @ Receives signal from sync module
     *
     * @param source signal emitting  component
     * @param signalID ID of the signal
     * @param obj representation of the signal
     */
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;
};

} //namespace

#endif
