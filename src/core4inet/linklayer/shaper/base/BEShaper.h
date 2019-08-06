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

#ifndef CORE4INET_BESHAPER_H
#define CORE4INET_BESHAPER_H

//INET
#include "inet/linklayer/ethernet/EtherFrame.h"

namespace CoRE4INET {

/**
 * @brief A Shaper for BEMessages.
 *
 * The BEShaper only allows lower priorities to transmit when there are no
 * BE messages queued. This class is usually used with BaseShaper as template
 * class, as there are usually no lower priority messages than BE messages.
 *
 * @see BaseShaper
 *
 * @author Till Steinbach
 */
template<class TC>
class BEShaper : public TC
{
    public:
        /**
         * @brief Constructor
         */
        BEShaper();

        /**
         * @brief Destructor
         */
        virtual ~BEShaper() override;

    protected:
        /**
         * @brief Signal that is emitted when the queue length of best-effort messages changes.
         */
        static simsignal_t beQueueLengthSignal;
        /**
         * @brief Signal that is emitted when the queue size (in bytes) of best-effort messages changes.
         */
        static simsignal_t beQueueSizeSignal;

    private:
        /**
         * @brief Queue for best-effort messages
         */
        cQueue beQueue;

        /**
         * @brief caches queue size in bytes
         */
        size_t beQueueSize;

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
         * @return returns 1 or more depending on inheritance
         */
        virtual int numInitStages() const override;

        /**
         * @brief Forwards the messages from the different buffers and LLC
         * according to the specification for BEMessages.
         *
         * Best-effort messages are send immediately, lower priority frames are queued
         * as long as there are best-effort messages waiting.
         * If the mac layer is idle, messages are picked from the queues according
         * to the priorities, using the template class.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Queues messages in the correct queue
         *
         * Best-effort messages are queued in this module, other messages are forwarded to the
         * template classes enqueueMessage method
         *
         * @param msg the incoming message
         */
        virtual void enqueueMessage(cMessage *msg) override;

        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
         *
         */
        virtual void requestPacket() override;

        /**
         * @brief Returns true when there are no pending messages.
         *
         * @return true if all queues are empty.
         */
        virtual bool isEmpty() override;

        /**
         * @brief Clears all queued packets and stored requests.
         */
        virtual void clear() override;

        /**
         * @brief Returns a frame directly from the queues, bypassing the primary,
         * send-on-request mechanism. Returns nullptr if the queue is empty.
         *
         * @return the message with the highest priority from any queue. nullptr if the
         * queues are empty or cannot send due to the traffic policies.
         */
        virtual cMessage *pop() override;

        /**
         * @brief Returns a pointer to a frame directly from the queues.
         *
         * front must return a pointer to the same message pop() would return.
         *
         * @return pointer to the message with the highest priority from any queue. nullptr if the
         * queues are empty
         */
        virtual cMessage *front() override;
};

template<class TC>
simsignal_t BEShaper<TC>::beQueueLengthSignal = cComponent::registerSignal("beQueueLength");
template<class TC>
simsignal_t BEShaper<TC>::beQueueSizeSignal = cComponent::registerSignal("beQueueSize");

template<class TC>
BEShaper<TC>::BEShaper()
{
    beQueue.setName("BE Messages");
    beQueueSize = 0;
    WATCH(beQueueSize);
}

template<class TC>
BEShaper<TC>::~BEShaper()
{
    beQueue.clear();
}

template<class TC>
void BEShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        //Send initial signal to create statistic
        cComponent::emit(beQueueLengthSignal, static_cast<unsigned long>(beQueue.getLength()));
        //Send initial signal to create statistic
        cComponent::emit(beQueueSizeSignal, static_cast<unsigned long>(0));
    }
}

template<class TC>
int BEShaper<TC>::numInitStages() const
{
    if (TC::numInitStages() > 1)
    {
        return TC::numInitStages();
    }
    else
    {
        return 1;
    }
}

template<class TC>
void BEShaper<TC>::handleMessage(cMessage *msg)
{
    //Frames arrived on in are best-effort frames
    if (msg->arrivedOn("in"))
    {
        // If there are framesRequested the MAC layer is currently idle
        if (TC::getNumPendingRequests())
        {
            TC::framesRequested--;
            cSimpleModule::send(msg, cModule::gateBaseId("out"));
        }
        else
        {
            enqueueMessage(msg);
        }
    }
}

template<class TC>
void BEShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        beQueue.insert(msg);
        cComponent::emit(beQueueLengthSignal, static_cast<unsigned long>(beQueue.getLength()));
        beQueueSize+=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(msg)->getByteLength());
        cComponent::emit(beQueueSizeSignal, static_cast<unsigned long>(beQueueSize));
        TC::notifyListeners();
        EV_TRACE << "Interface not idle queuing BE frame" << endl;
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void BEShaper<TC>::requestPacket()
{
    Enter_Method("requestPacket()");
    //Feed the MAC layer with the next frame
    TC::framesRequested++;

    if (cMessage *msg = pop())
    {
        TC::framesRequested--;
        cSimpleModule::send(msg, cModule::gateBaseId("out"));
    }
}

template<class TC>
cMessage* BEShaper<TC>::pop()
{
    Enter_Method("pop()");
    //BEFrames
    if (!beQueue.isEmpty())
    {
        cMessage* message = static_cast<cMessage*>(beQueue.pop());
        cComponent::emit(beQueueLengthSignal, static_cast<unsigned long>(beQueue.getLength()));

        beQueueSize-=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(message)->getByteLength());
        cComponent::emit(beQueueSizeSignal, static_cast<unsigned long>(beQueueSize));
        return message;
    }
    return TC::pop();
}

template<class TC>
cMessage* BEShaper<TC>::front()
{
    Enter_Method("front()");
    //BEFrames
    if (!beQueue.isEmpty())
    {
        cMessage* message = static_cast<cMessage*>(beQueue.front());
        return message;
    }
    return TC::front();
}

template<class TC>
bool BEShaper<TC>::isEmpty()
{
    return beQueue.isEmpty() && TC::isEmpty();
}

template<class TC>
void BEShaper<TC>::clear()
{
    TC::clear();
    beQueue.clear();
}

}

#endif

