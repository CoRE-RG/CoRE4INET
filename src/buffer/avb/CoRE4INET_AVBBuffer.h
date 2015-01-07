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

//CoRE4INET
#include "CoRE4INET_Buffer.h"
#include "CoRE4INET_Timed.h"
#include "AVBDefs_m.h"
#include "CoRE4INET_SRPTable.h"

namespace CoRE4INET {

/**
 * @brief Base class for a audio-video bridging buffer class.
 *
 * The Frame is stored and released in dependency of the Credit of the CBS Algorithm. The Buffer interacts with the Scheduler.
 *
 * Use the implementations AVBQueueBuffer.
 *
 * @author Philipp Meyer
 *
 * @sa AVBQueueBuffer, Buffer
 *
 * @ingroup Buffer
 */
class AVBBuffer : public virtual Buffer, public virtual Timed
{
        using Timed::initialize;
    public:
        AVBBuffer();
        virtual ~AVBBuffer();

    public:
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
         * @param duration AVB frame sending duration.
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
        int getCredit() const;

        /**
         * @brief resets credit to 0.
         */
        void resetCredit();

    protected:
        SR_CLASS srClass;
        int credit;
        int maxCredit;
        bool inTransmission;
        //int msgCnt;
        simtime_t newTime;
        simtime_t oldTime;
        simtime_t Wduration;
        simtime_t tick;
        SRPTable *srptable;
        unsigned int portBandwith;

        static simsignal_t creditSignal;

        /**
         * @brief Initializes the Buffer
         *
         * @param stage the stages. In this Case only stage 0.
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return returns 1
         */
        virtual int numInitStages() const override;

        /**
         * @brief handles the incoming and outgoing messages of the buffer.
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
};

} /* namespace CoRE4INET */
#endif /* __CORE4INET_AVBBUFFER_H_ */
