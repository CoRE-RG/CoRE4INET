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

#ifndef __CORE4INET_CREDITBASEDSHAPER_H_
#define __CORE4INET_CREDITBASEDSHAPER_H_

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
 * @brief TODO
 *
 * @author Philipp Meyer
 *
 * @sa IEEE8021QbvSelectionAlgorithm, Timed, cListener
 */
class CreditBasedShaper : public virtual IEEE8021QbvSelectionAlgorithm, Timed, cListener
{
  protected:
    /**
     * Signal that is emitted every time the credit is recalculated.
     */
    static simsignal_t creditSignal;

  private:
    /**
     * @brief Current credit of the CBS
     */
    int credit;
    /**
     * @brief Length the corresponding queue
     */
    unsigned long queueLength;
    /**
     * @brief Stream Reservation Class of the Shaper
     */
    SR_CLASS srClass;
    /**
     * @brief Pointer to SRPTable module
     */
    SRPTable* srpTable;

  public:
    /**
     * @brief Constructor
     */
    CreditBasedShaper();
    /**
     * @brief Destructor
     */
    virtual ~CreditBasedShaper(){}

  protected:
    virtual void initialize();
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname);
    /**
     * @brief TODO
     */
    virtual void handleMessage(cMessage *msg);
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
     * @brief TODO
     *
     * @param duration
     */
    void idleSlope(simtime_t duration);
    /**
     * @brief TODO
     *
     * @param duration
     */
    void sendSlope(simtime_t duration);
};

} //namespace

#endif
