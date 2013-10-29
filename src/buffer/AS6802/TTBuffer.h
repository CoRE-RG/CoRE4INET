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

#ifndef __TTETHERNETMODELV2_TTBUFFER_H_
#define __TTETHERNETMODELV2_TTBUFFER_H_

#include <omnetpp.h>
#include <CTBuffer.h>
#include <SchedulerMessageEvents_m.h>
#include <Scheduled.h>

namespace TTEthernetModel {

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
class TTBuffer : public virtual CTBuffer, public Scheduled
{
    private:
        /**
         * @brief Event indicating the actionTime
         *
         */
        SchedulerActionTimeEvent* actionTimeEvent;

        uint64_t nextAction;

    protected:
        using Scheduled::initialize;
        /**
         * @brief Initializes the SchedulerActionTimeEvent
         *
         * @param stage the stages. Module registers events when stage==1
         */
        virtual void initialize(int stage);

        /**
         * @brief Returns the numer of initializaiton stages this module needs.
         *
         * @return returns TTEScheduler::numInitStages()+1 or Buffer::numInitStages()
         * (depending on which is higher)
         */
        virtual int numInitStages() const;

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
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);

    public:
        /**
         * @brief Constructor
         */
        TTBuffer();

        /**
         * @brief Destructor
         */
        ~TTBuffer();

        uint64_t nextSendWindowStart();
};
}

#endif
