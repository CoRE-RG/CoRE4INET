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

#ifndef CORE4INET_BASESHAPER_H
#define CORE4INET_BASESHAPER_H

//CoRE4IENT
#include "core4inet/base/CoRE4INET_Defs.h"

//INET
#include "inet/common/queue/IPassiveQueue.h"

namespace CoRE4INET {

/**
 * @brief An abstract base Shaper.
 *
 * Should be used as template class in other Traffic conditioners. Provides
 * base infrastructure for the Shapers
 *
 * @author Till Steinbach
 */
class BaseShaper : public virtual cSimpleModule, public virtual inet::IPassiveQueue, public virtual cListener
{
    public:
        /**
         * @brief Constructor
         */
        BaseShaper()
        {
            this->framesRequested = 0;
            this->outChannel = nullptr;
        }

        /**
         * Implementation of IPassiveQueue::addListener().
         */
        virtual void addListener(inet::IPassiveQueueListener *listener) override;

        /**
         * Implementation of IPassiveQueue::removeListener().
         */
        virtual void removeListener(inet::IPassiveQueueListener *listener) override;

        virtual void receiveSignal(__attribute__((unused))  cComponent *source, __attribute__((unused))  simsignal_t signalID,
                __attribute__((unused)) bool b, __attribute__((unused)) cObject *details) override
        {
        }
        virtual void receiveSignal(__attribute__((unused))  cComponent *source, __attribute__((unused))  simsignal_t signalID,
                __attribute__((unused)) long l, __attribute__((unused)) cObject *details) override
        {
        }
        virtual void receiveSignal(__attribute__((unused))  cComponent *source, __attribute__((unused))  simsignal_t signalID,
                __attribute__((unused)) unsigned long l, __attribute__((unused)) cObject *details) override
        {
        }
        virtual void receiveSignal(__attribute__((unused))  cComponent *source, __attribute__((unused))  simsignal_t signalID,
                __attribute__((unused)) double d, __attribute__((unused)) cObject *details) override
        {
        }
        virtual void receiveSignal(__attribute__((unused))  cComponent *source, __attribute__((unused))  simsignal_t signalID,
                __attribute__((unused))  const SimTime& t, __attribute__((unused)) cObject *details) override
        {
        }
        virtual void receiveSignal(__attribute__((unused))  cComponent *source, __attribute__((unused))  simsignal_t signalID,
                __attribute__((unused)) const char *s, __attribute__((unused)) cObject *details) override
        {
        }
        virtual void receiveSignal(__attribute__((unused))  cComponent *source, __attribute__((unused))  simsignal_t signalID,
                __attribute__((unused))  cObject *obj, __attribute__((unused)) cObject *details) override
        {
        }
    private:
        /**
         * @brief List of TTBuffers.
         *
         * The vector is ordered by action time
         */
        std::list<inet::IPassiveQueueListener *> listeners;

    protected:
        /**
         * @brief Number of frames that were requested from lower layer
         */
        size_t framesRequested;

        /**
         * @brief Outgoing Channel used to calculate transmission duration.
         */
        cChannel *outChannel;

        /**
         * @brief Signal that is emitted when the queue length of best-effort messages changes.
         */
        static simsignal_t beQueueLengthSignal;

    protected:
        /**
         * Initializes the module
         *
         * @param stage The stages. Module initializes when stage==0
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return Always returns 1
         */
        virtual int numInitStages() const override;

        /**
         * @brief Deletes the incoming message
         *
         * Should be overwritten by template classes. and called when there are no other
         * traffic conditioners responsible
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Deletes the incoming message
         *
         * Should be overwritten by template classes. and called when there are no other
         * traffic conditioners responsible
         *
         * @param msg the incoming message
         */
        virtual void enqueueMessage(cMessage *msg);

        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
         */
        virtual void requestPacket() override
        {
        }

        /**
         * @brief Returns number of requested messages.
         */
        virtual int getNumPendingRequests() override
        {
            return static_cast<int>(framesRequested);
        }

        /**
         * @brief Returns true when there are no pending messages.
         *
         * @return true if all queues are empty.
         */
        virtual bool isEmpty() override
        {
            return true;
        }

        /**
         * @brief Clears all queued packets and stored requests.
         */
        virtual void clear() override
        {
        }

        /**
         * @brief Returns a frame directly from the queues, bypassing the primary,
         * send-on-request mechanism. Returns nullptr if the queue is empty.
         *
         * @return the message with the highest priority from any queue. nullptr if the
         * queues are empty or cannot send due to the traffic policies.
         */
        virtual cMessage *pop() override
        {
            return nullptr;
        }

        /**
         * @brief Returns a pointer to a frame directly from the queues.
         *
         * front must return a pointer to the same message pop() would return.
         *
         * @return pointer to the message with the highest priority from any queue. nullptr if the
         * queues are empty
         */
        virtual cMessage *front()
        {
            return nullptr;
        }

        /**
         * @brief Notifies registered listeners about changes.
         */
        void notifyListeners();
};
}

#endif

