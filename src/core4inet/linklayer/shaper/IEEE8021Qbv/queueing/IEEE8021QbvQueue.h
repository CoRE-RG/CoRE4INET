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

#ifndef __CORE4INET_IEEE8021QBCQUEUE_H_
#define __CORE4INET_IEEE8021QBCQUEUE_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/buffer/base/BGQueueBuffer.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selection/IEEE8021QbvSelection.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @brief A queue buffer for IEEE 802.1Qbv transmission selection with gates.
 *
 * @ingroup IEEE8021Qbv
 *
 * @author Philipp Meyer
 */
class IEEE8021QbvQueue : public virtual BGQueueBuffer
{
  private:
    /**
     * @brief Pointer to IEEE 802.1Qbv transmission selection module.
     */
    IEEE8021QbvSelection* ts;

  protected:
    /**
     * @brief Initializes the module.
     *
     * @param stage The stages. Module initializes when stage==0
     */
    virtual void initialize(int stage) override;
    /**
     * @brief Is called when a new Frame is received in the buffer.
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg) override;
    /**
     * @brief Is called to get an inet::EtherFrame from the buffer.
     *
     * Sends the inet::EtherFrame to the transmission selection module.
     *
     * @return nullptr
     */
    virtual inet::EtherFrame* dequeue() override;
    /**
     * @brief Returns the used size of the buffer.
     *
     * @return number of messages in the buffer
     */
    virtual size_t size() const override;
    /**
     * @brief Components that contain visualization-related code are expected to override refreshDisplay().
     */
    virtual void refreshDisplay() const  override;

};

} //namespace

#endif
