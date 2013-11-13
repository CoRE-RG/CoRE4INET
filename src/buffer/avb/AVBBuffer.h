//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __CORE4INET_AVBBUFFER_H_
#define __CORE4INET_AVBBUFFER_H_

#include <omnetpp.h>
#include "Buffer.h"
#include "AVBIncoming.h"
#include "Timed.h"

namespace CoRE4INET {

/**
 * @brief Base class for a audio-video bridging buffer class.
 *
 * The Frame is stored and released in dependency of the Credit of the CBS Algorithm. The Buffer interacts with the Scheduler.
 *
 * Use the implementations AVBDoubleBuffer, AVBQueueBuffer.
 *
 * @author Philipp Meyer
 *
 * @sa AVBDoubleBuffer, AVBQueueBuffer, Buffer
 *
 * @ingroup Buffer
 */
class AVBBuffer : public virtual Buffer, public Timed
{
    public:
        AVBBuffer();
        virtual ~AVBBuffer();

        /**
         * @brief caculates new credit for idleslope time.
         *
         * @param duration since last calculation.
         */
        void idleSlope(SimTime duration);

        /**
         * @brief caculates new credit for the time a AVB are queued but sending is not allowed.
         *
         * @param duration since last calculation.
         */
        void interferenceSlope(SimTime duration);

        /**
         * @brief caculates new credit for the duration an AVB frame is sending.
         *
         * @param AVB frame sending duration.
         */
        void sendSlope(SimTime duration);

        /**
         * @brief refreshs the credit.
         */
        void refresh();

        /**
         * @brief get credit
         *
         * @return returns the credit.
         */
        int getCredit();

        /**
         * @brief resets credit to 0.
         */
        void resetCredit();

        /**
         * @brief get Message count.
         *
         * @return returns number of queued frames.
         */
        int getMsgCount();
    protected:
        int credit;
        int maxCredit;
        int AVBReservation;
        bool inTransmission;
        int msgCnt;
        SimTime newTime;
        SimTime oldTime;
        double Wduration;
        double tick;

        AVBIncoming * avbCTC;

        static simsignal_t creditSignal;

        /**
         * @brief Initializes the Buffer
         *
         * @param stage the stages. In this Case only stage 0.
         */
        virtual void initialize(int stage);

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return returns 1
         */
        virtual int numInitStages() const;

        /**
         * @brief handles the incoming and outgoing messages of the buffer.
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
};

} /* namespace CoRE4INET */
#endif /* __CORE4INET_AVBBUFFER_H_ */
