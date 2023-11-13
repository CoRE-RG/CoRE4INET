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

#ifndef CORE4INET_CREDITBASEDSHAPER_H_
#define CORE4INET_CREDITBASEDSHAPER_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selectionAlgorithm/IEEE8021QbvSelectionAlgorithm.h"
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
#include "core4inet/base/avb/AVBDefs.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @brief Implementation of the Credit Based Shaper (CBS) traffic selection algorithm.
 *
 * @author Philipp Meyer
 *
 * @sa IEEE8021QbvSelectionAlgorithm, Timed, cListener
 */
class CreditBasedShaper : public virtual IEEE8021QbvSelectionAlgorithm, Timed, cListener
{
  protected:
    /**
     * @brief Signal that is emitted every time the credit is recalculated.
     */
    static simsignal_t creditSignal;
    /**
     * @brief Signal that is emitted every time the reserved bandwidth is updated.
     */
    static simsignal_t reservedBandwidthSignal;

  private:
    /**
     * @brief Current credit of the CBS.
     */
    int credit;
    /**
     * @brief Task Event is Scheduled
     */
    bool isScheduled;
    /**
     * @brief Size the corresponding queue.
     */
    unsigned long queueSize;
    /**
     * @brief Previous Size the corresponding queue.
     */
    unsigned long previousQueueSize;
    /**
     * @brief Time when credit is being calculated.
     */
    simtime_t newTime;
    /**
     * @brief Time until the credit was previously calculated.
     */
    simtime_t oldTime;
    /**
     * @brief Bandwidth of the port where the CBS is attached.
     */
    unsigned int portBandwidth;
    /**
     * The reserved bandwidth of the CBS set in the idle slope parameter.
     */
    unsigned long reservedBandwidth;
    /**
     * @brieg VLAN Priority code point of the shaper.
     */
    uint8_t pcp;
    /**
     * @brief Pointer to SRPTable module.
     */
    SRPTable* srpTable;
    /**
     * @brief Outgoing Channel used to calculate transmission duration.
     */
    cChannel *outChannel;

  public:
    /**
     * @brief Constructor
     */
    CreditBasedShaper();
    /**
     * @brief Destructor
     */
    virtual ~CreditBasedShaper() override {}
    /**
     * @brief Check if CBS state is open.
     *
     * @return true if state is open
     */
    virtual bool isOpen() override;
    /**
     * @brief Set the idle slope (reserved bandwidth) of this cbs to a specific value.
     * @note this will override reservations in the SRTable
     * @param bandwidth
     */
    virtual void setIdleSlope(unsigned long bandwidth);

  protected:
    virtual void initialize() override;
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname) override;
    /**
     * @brief Handles incoming SchedulerTimerEvents.
     *
     * @param msg incoming SchedulerTimerEvent
     */
    virtual void handleMessage(cMessage *msg) override;
    /**
     * @brief Receives signals from mac for CBS calculations and state.
     */
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) override;
    /**
     * @brief Receives signals from queue for CBS calculations and state.
     */
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, unsigned long l, cObject *details) override;

  private:
    /**
     * @brief Calculates the idleslope of the CBS.
     *
     * @param maxCreditZero true if the credit should not be incremented above zero
     */
    void idleSlope(bool maxCreditZero);
    /**
     * @brief Calculates the sendslope of the CBS.
     *
     * @param duration sending duration of a frame
     */
    void sendSlope(simtime_t duration);
    /**
     * @brief Get the current time from the timer module.
     */
    simtime_t getCurrentTime();
    /**
     * @brief Refresh the IEEE8021QbvSelectionAlgorithm state.
     */
    void refreshState();
};

} //namespace

#endif
