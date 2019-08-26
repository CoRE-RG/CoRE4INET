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

#ifndef __CORE4INET_IEEE8021QBVGATECONTROLLIST_H_
#define __CORE4INET_IEEE8021QBVGATECONTROLLIST_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/utilities/classes/Scheduled.h"

using namespace omnetpp;
using namespace std;

namespace CoRE4INET {

/**
 * @brief IEEE 802.1Qbv gate control list implementation.
 *
 * Stores control list and propagates its states over time.
 *
 * @ingroup IEEE8021Qbv
 *
 * @author Philipp Meyer
 */
class IEEE8021QbvGateControlList : public virtual Scheduled
{
  private:
    /**
     * @brief Number of gates for control.
     */
    unsigned int numGates;
    /**
     * @brief Vector containing the initial gate states.
     */
    vector<string> initalGateStates;
    /**
     * @brief Data structure containing the complete gate control list.
     */
    vector<pair<vector<string>, double>> gateControlList;
    /**
     * @brief Iterator of control list data structure. Stores a pointer to the current control list element.
     */
    vector<pair<vector<string>, double>>::iterator gateControlElement;
    /**
     * @brief TODO
     */
    unsigned int configNo;
    /**
     * @brief TODO
     */
    string timerEventName;

  public:
    /**
     * @brief Constructor
     */
    IEEE8021QbvGateControlList();

    /**
     * Exchange the current gate control list with a new one.
     * This function calls handle parameter change to perform the changes.
     * @param gcl the new gate control list to set.
     */
    virtual void setGateControlList (string gcl);

  protected:
    /**
     * @brief Initializes the module.
     *
     * @param stage The stages. Module initializes when stage==0
     */
    virtual void initialize(int stage);
    /**
     * @brief Returns the number of initialization stages this module needs.
     *
     * @return returns 2
     */
    virtual int numInitStages() const;
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname);
    /**
     * @brief Receives SchedulerTimerEvent messages from scheduler indicating the expiration of the current control element.
     *
     * Switches to next control element, propagate its gate states and schedule the next SchedulerTimerEvent message.
     *
     * @param msg the incoming message
     */
    virtual void handleMessage(cMessage *msg);

  private:
    /**
     * @brief Schedule the next SchedulerTimerEvent message.
     */
    void scheduleCurrentGateControlElementTime(bool nextCycle);
    /**
     * @brief Propagate the gate states of the current control element.
     */
    void propagteGateControlElement(vector<string> gateStates);
    /**
     * @brief Switch to next control element of the control list.
     */
    void switchToNextGateControlElement();
};

} //namespace

#endif
