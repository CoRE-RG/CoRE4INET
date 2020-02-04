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

#ifndef CORE4INET_CREDITBASEDMETER_H_
#define CORE4INET_CREDITBASEDMETER_H_

//INET
#include "inet/linklayer/ethernet/EtherMACFullDuplex.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"
//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/base/avb/AVBDefs.h"
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/filter/IEEE8021QciFilter.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/meter/IEEE8021QciMeter.h"

namespace CoRE4INET {

/**
 * @brief Class representing the experimental Credit Based Meter (CBM) module
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
     * @brief Signal that is emitted every time the credit is recalculated.
     */
    static simsignal_t creditSignal;

  private:
    /**
     * @brief Current credit of the CBM
     */
    int credit;
    /**
     * @brief Current state of the CBM
     */
    State state;
    /**
     * @brief Caches the reserved bandwidth
     */
    unsigned long reservedBandwidth;
    /**
     * @brief Maximum credit value allowed
     */
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
    /**
     * @brief Caches pointers to the stream filters
     */
    std::vector<IEEE8021QciFilter*> streamFilters;
    /**
     * @brief Max number of frames in a burst
     */
    size_t maxBurst;
    /**
     * @brief Caches configured SRClass
     */
    SR_CLASS srClass;
    /**
     * @brief Last time the credit value was emitted
     */
    simtime_t lastEmitCredit;
    /**
     * @brief Is sendslope active
     */
    bool isSendSlopeActive;

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
    void idleSlope(simtime_t delta);
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
     * @param frame the incoming Ethernet frame
     */
    void meter(inet::EtherFrame *frame);
    /**
     * @brief Calculates the reserved bandwidth and maximum credit value
     */
    void refreshReservedBandwidthAndMaxCredit();
    /**
     * @brief Calculates the duration a frame would be transmitted on link
     *
     * @param frame the frame for which the duration should be calculated
     *
     * @return the transmission duration
     */
    simtime_t calculateTransmissionDuration(inet::EtherFrame *frame);
    /**
     * @brief Get current simulation time
     *
     * @return current simulation time
     */
    simtime_t getCurrentTime();
    /**
     * @brief Order to get a schedule message when the credit value reach zero
     */
    void scheduleCreditReachZero();
    /**
     * @brief Order to get a schedule message when the credit value reaches its maximum
     */
    void scheduleCreditReachMax();
    /**
     * @brief Order to get a schedule message in specified simulation time delta
     *
     * @param duration the specified delta
     */
    void scheduleEvent(simtime_t duration);
    /**
     * @brief Order to get a schedule message in specified simulation time delta
     *
     * @param duration the specified delta
     *
     * @param name the name of the schedule message
     */
    void scheduleEvent(simtime_t duration, const char *name);
    /**
     * @brief Emit the credit value
     */
    void emitCredit();
};

} //namespace

#endif
