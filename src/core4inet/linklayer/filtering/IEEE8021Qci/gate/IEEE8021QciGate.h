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

#ifndef CORE4INET_IEEE8021QCIGATE_H_
#define CORE4INET_IEEE8021QCIGATE_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/meter/IEEE8021QciMeter.h"
//Auto-generated Messages
#include "core4inet/linklayer/filtering/IEEE8021Qci/IEEE8021QciCtrl_m.h"

namespace CoRE4INET {

/**
 * @brief Class for a simple IEEE 802.1Qci gate
 *
 * A incoming message is dropped when the gate is closed and forwarded to the configured flow meter if the gate is in state open.
 *
 * @author Philipp Meyer
 */
class IEEE8021QciGate : public virtual cSimpleModule
{
  public:
    /**
     * @brief State of the IEEE8021QciGate
     */
    enum State
    {
        CLOSED = 0,//!< CLOSE
        OPEN = 1  //!< OPEN
    };

  protected:
    /**
     * @brief Variable for counting the number of dropped frames
     */
    unsigned long numFramesDropped = 0;

  private:
    /**
     * @brief Current state of the IEEE8021QciGate.
     */
    State state;
    /**
     * @brief Signal emitted when frame is dropped by the gate
     */
    static simsignal_t frameDroppedSignal;

  public:
    /**
     * @brief Open the gate!
     */
    virtual void open();
    /**
     * @brief Close the gate!
     */
    virtual void close();

  protected:
    /**
     * @brief Initializes the gate
     */
    virtual void initialize();
    /**
     * @brief handles the incoming and outgoing messages of the gate.
     *
     * @param msg incoming inet::EtherFrame for the gate.
     */
    virtual void handleMessage(cMessage *msg);
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char *parname);
    /**
     * @brief Components that contain visualization-related code are expected to override refreshDisplay()
     */
    virtual void refreshDisplay() const;
    /**
     * @brief Records simulation results
     */
    virtual void finish();
};

} //namespace

#endif
