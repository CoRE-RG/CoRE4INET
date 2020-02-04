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

#ifndef CORE4INET_IEEE8021QCIMETER_H_
#define CORE4INET_IEEE8021QCIMETER_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/IEEE8021QciOutput.h"
//Auto-generated Messages
#include "core4inet/linklayer/filtering/IEEE8021Qci/IEEE8021QciCtrl_m.h"

namespace CoRE4INET {

/**
 * @brief Class representing the IEEE 802.1Qci base meter
 *
 * @author Philipp Meyer
 */
class IEEE8021QciMeter : public virtual cSimpleModule
{
  protected:
    /**
     * @brief Variable for counting the number of received frames
     */
    unsigned long numFramesReceived = 0;
    /**
     * @brief Variable for counting the number of sent frames
     */
    unsigned long numFramesSent = 0;
    /**
     * @brief Variable for counting the number of received bytes
     */
    unsigned long numBytesReceived = 0;
    /**
     * @brief Variable for counting the number of sent bytes
     */
    unsigned long numBytesSent = 0;
    /**
     * @brief Signal emitted when frame passes the meter
     */
    static simsignal_t framePassedSignal;

  private:
    IEEE8021QciOutput *streamOutput;

  protected:
    /**
     * @brief Initializes the module
     */
    virtual void initialize();
    /**
     * @brief Meters the message
     *
     * @param msg the incoming message
     */
    virtual void handleMessage(cMessage *msg);
    /**
     * @brief Records simulation results
     */
    virtual void finish();
};

} //namespace

#endif
