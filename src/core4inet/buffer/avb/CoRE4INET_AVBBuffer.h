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

#ifndef CORE4INET_AVBBUFFER_H_
#define CORE4INET_AVBBUFFER_H_

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
 * @sa AVBQueueBuffer, Buffer, Timed, cListener
 *
 * @ingroup Buffer
 */
class AVBBuffer : public virtual Buffer, public virtual Timed, cListener
{
        using Timed::initialize;
    public:
        /**
         * @brief Constructor
         */
        AVBBuffer();

        /**
         * @brief Destructor
         */
        virtual ~AVBBuffer();

        /**
         * @brief Handles incoming signals
         *
         * @param source incoming signal source
         * @param signalID id of the incoming signal
         * @param l signal long value
         */
        virtual void receiveSignal(cComponent *source, simsignal_t signalID, long l) override;
    public:
        /**
         * @brief calculates new credit for idleslope time.
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

    private:
        /**
         * @brief Stream Reservation Class of the AVB Buffer
         */
        SR_CLASS srClass;

        /**
         * @brief Current credit of the CBS
         */
        int credit;

        /**
         * @brief Maximum credit (can be observed in the GUI)
         */
        int maxCredit;
        
        /**
         * @brief Last emit time of the credit signal
         */
        simtime_t lastCreditEmitTime;

        /**
         * @brief Is true when frame is currently in transmission
         */
        bool inTransmission;

        /**
         * @brief Time when credit is being calculated
         */
        simtime_t newTime;

        /**
         * @brief Time until the credit was previously calculated
         */
        simtime_t oldTime;

        /**
         * @brief Time until credit is zero
         */
        simtime_t wDuration;

        /**
         * @brief Length of one tick
         */
        simtime_t tick;

        /**
         * @brief Pointer to the SRP Table
         */
        SRPTable *srptable;

        /**
         * @brief Bandwidth of the port where the buffer is attached
         */
        unsigned int portBandwith;
    protected:

        /**
         * Signal that is emitted every time the credit is recalculated.
         */
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
         * @param msg incoming inet::EtherFrame for the Buffer or SchedulerActionTimeEvent message.
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

    private:
        /**
         * @brief Get current Time of the Node
         *
         * @return returns current Time
         */
        simtime_t getCurrentTime();

        /**
         * @brief Emit credit signal
         */
        void emitCredit();
};

} /* namespace CoRE4INET */
#endif /* CORE4INET_AVBBUFFER_H_ */
