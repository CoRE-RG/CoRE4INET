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

#ifndef __TTETHERNETMODELV2_RCBUFFER_H_
#define __TTETHERNETMODELV2_RCBUFFER_H_

#include <omnetpp.h>
#include "CTBuffer.h"
#include <SchedulerMessageEvents_m.h>
#include <Timed.h>

namespace TTEthernetModel {

/**
 * @brief Base class for a rate-constrained buffer class.
 *
 * The Frame is stored and released immediately when the bag has expired previously.
 * If the bag has not expired yet the frame is stored. The implementation uses a
 * SchedulerTimerEvent that is registered at the TTEScheduler.
 *
 * Use the implementations RCDoubleBuffer, RCQueueBuffer.
 *
 * @sa RCDoubleBuffer, RCQueueBuffer, CTBuffer
 *
 * @ingroup Buffer AS6802
 *
 * @author Till Steinbach
 */
class RCBuffer : public virtual CTBuffer, public Timed
{
    private:
        /**
         * @brief Boolean indicating the bag already expired
         */
        bool bagExpired;

        /**
         * @brief Number of reset messages by the destination Gates.
         *
         * The bag is only reseted when all gates invoked resetBag().
         */
        unsigned int numReset;

    public:
        /**
         * @brief Constructor
         */
        RCBuffer();

        /**
         * @brief Destructor
         */
        virtual ~RCBuffer();

        /**
         * @brief resets the bag for a destination gate.
         *
         * This method must be invoked only once by each destination gate
         * to indicate the message left the interface.
         * The method executes the transmit callbacks and registers a
         * SchedulerTimerEvent that indicates the beginning of a new bag
         */
        virtual void resetBag();

    protected:
        using Timed::initialize;
        /**
         * @brief Initializes the timerMessage
         *
         * @param stage the stages. Module initializes when stage==0
         */
        virtual void initialize(int stage);
        /**
         * @brief Returns the numer of initializaiton stages this module needs.
         *
         * @return always returns 1
         */
        virtual int numInitStages() const;

        /**
         * @brief handles the incoming and outgoing messages of the buffer.
         *
         * If message arrived on in, it is queued by calling
         * Buffer::handleMessage(cMessage *msg). Afterwards the message is directly
         * send when the bag already expired. When the scheduler message arrives (schedulerIn)
         * a pending message is transferred. If there is no message waiting the bagExpired
         * state is saved.
         *
         * @param msg incoming EtherFrame for the Buffer or SchedulerTimerEvent message.
         */
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);
};

} //namespace

#endif
