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

#ifndef __CORE4INET_CREDITBASEDMETER_H_
#define __CORE4INET_CREDITBASEDMETER_H_

//INET
#include "inet/linklayer/ethernet/EtherMACFullDuplex.h"
//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/base/avb/AVBDefs.h"
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/filter/IEEE8021QciFilter.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/meter/IEEE8021QciMeter.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Class for a Credit Based Meter (CBM)
 *
 * @author Philipp Meyer
 *
 * @sa IEEE8021QciMeter, Timed, cListener
 */
class CreditBasedMeter : public virtual IEEE8021QciMeter, public virtual Timed, cListener
{
    using Timed::initialize;

  public:
    /**
     * @brief CBM state
     */
    enum State
    {
        R_RA,//!< Running Receiving Allowed
        R_RF //!< Running Receiving Forbidden
    };

  protected:
    /**
     * Signal that is emitted every time the credit is recalculated.
     */
    static simsignal_t creditSignal;
    static simsignal_t frameReceivedSignal;

  private:
    /**
     * @brief Current credit of the CBM
     */
    int credit;

    /**
     * @brief Current state of the CBM
     */
    State state;

    unsigned long reservedBandwidth;

    int maxCredit;

    /**
     * @brief The Channel connected to this Port
     */
    cChannel *inChannel;

    /**
     * @brief Time until the credit was previously calculated
     */
    simtime_t lastCalcTime;

    /**
     * @brief Pointer to the SRP Table
     */
    SRPTable *srptable;

    std::vector<IEEE8021QciFilter*> streamFilters;

    /**
     * @brief Max number of frames in a burst
     */
    size_t maxBurst;

    SR_CLASS srClass;

  public:
    /**
     * @brief Handles incoming signals
     *
     * @param source incoming signal source
     * @param signalID id of the incoming signal
     * @param l signal long value
     */
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) override;

  protected:
    /**
     * @brief Initializes the CBM
     */
    virtual void initialize() override;

    /**
     * @brief Handles the incoming and outgoing messages of the CBM
     *
     * @param msg incoming IEE8021QciCtrl for the CBM
     */
    virtual void handleMessage(cMessage *msg) override;

    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname) override;

    /**
     * @brief Components that contain visualization-related code are expected to override refreshDisplay()
     */
    virtual void refreshDisplay() const;

  private:
    /**
     * @brief Calculates the credit with idle slope till current SimTime - delta
     *
     * @param delta SimTime to be subtracted from current SimTime
     */
    void idleSlope(SimTime delta);

    /**
     * @brief Refresh to current credit value of the CBM
     *
     * @param frame The incoming inet EtherFrame
     */
    void sendSlope(inet::EtherFrame *frame);

    /**
     * @brief Refresh the current state of the CBM
     */
    void refreshState();

    /**
     * @brief Meter the message
     *
     * @param msg The incoming cMessage
     */
    void meter(inet::EtherFrame *frame);

    void refreshReservedBandwidthAndMaxCredit();

    SimTime calculateTransmissionDuration(inet::EtherFrame *frame);

    SimTime getCurrentTime();

    void scheduleCreditReachZero();

    void scheduleEvent(SimTime duration, const char* name);
};

} //namespace

#endif
