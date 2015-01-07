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

#ifndef __CORE4INET_TTBUFFER_H_
#define __CORE4INET_TTBUFFER_H_

//CoRE4INET
#include "CoRE4INET_CTBuffer.h"
#include "CoRE4INET_Scheduled.h"

namespace CoRE4INET {

/**
 * @brief Base class for a time-triggered buffer class.
 *
 * The Frame is stored and released time-triggered using a previously
 * registered SchedulerActionTimeEvent. The Buffer interacts with the TTEScheduler.
 *
 * Use the implementations TTDoubleBuffer, TTQueueBuffer.
 *
 * @sa TTDoubleBuffer, TTQueueBuffer, CTBuffer
 *
 * @ingroup Buffer AS6802
 *
 * @author Till Steinbach
 */
class TTBuffer : public virtual CTBuffer, public virtual Scheduled
{
    private:
        /**
         * Checks whether the parameters were already initialized
         */
        bool parametersInitialized;

        /**
         * @brief Event indicating the actionTime
         *
         */
        SchedulerActionTimeEvent* actionTimeEvent;

        uint64_t nextAction;

        /**
         * @brief Caches sendWindowStart parameter
         */
        uint32_t sendWindowStart;

        /**
         * @brief Caches sendWindowEnd parameter
         */
        uint32_t sendWindowEnd;

    protected:
        using Scheduled::initialize;
        /**
         * @brief Initializes the SchedulerActionTimeEvent
         *
         * @param stage the stages. Module registers events when stage==1
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the numer of initializaiton stages this module needs.
         *
         * @return returns TTEScheduler::numInitStages()+1 or Buffer::numInitStages()
         * (depending on which is higher)
         */
        virtual int numInitStages() const override;

        /**
         * @brief handles the incoming and outgoing messages of the buffer.
         *
         * If message arrived on in, it is queued by calling
         * Buffer::handleMessage(cMessage *msg).
         * When a SchedulerActionTimeEvent message arrives the previously stored message
         * is released and the callbacks are executed. When there is no message to send
         * a TTBufferEmpty message is transmitted. This allowes the receiving application to
         * use the bandwidth for other messages.
         *
         * @param msg incoming EtherFrame for the Buffer or SchedulerActionTimeEvent message.
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

    public:
        /**
         * @brief Constructor
         */
        TTBuffer();

        /**
         * @brief Destructor
         */
        virtual ~TTBuffer();

        uint64_t nextSendWindowStart() const;

        /**
         * @brief Calculates the bandwidth this module requires for transmission.
         *
         * @return Bandwidth in bps, or -1 is unknown.
         *
         * @sa enqueue();
         */
        virtual long getRequiredBandwidth() override;

        /**
         * @brief Returns the Start of the Send Window in Ticks
         *
         * @return send window start in ticks
         */
        uint32_t getSendWindowStart();

        /**
         * @brief Returns the End of the Send Window in Ticks
         *
         * @return send window end in ticks
         */
        uint32_t getSendWindowEnd();
};
}

#endif
