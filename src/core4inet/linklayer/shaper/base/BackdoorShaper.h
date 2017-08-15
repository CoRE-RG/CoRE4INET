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

#ifndef CORE4INET_LINKLAYER_SHAPER_BASE_BACKDOORSHAPER_H_
#define CORE4INET_LINKLAYER_SHAPER_BASE_BACKDOORSHAPER_H_

#include <algorithm>    // std::sort

//CoRE4INET
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/utilities/HelperFunctions.h"
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/base/CoRE4INET_Defs.h"
//Auto-generated Messages
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"

namespace CoRE4INET {

/**
 * @brief A Shaper for IEEE802.1Q-tagged Messages.
 *
 * @ingroup IEEE8021Q
 *
 * @author Till Steinbach, Philipp Meyer
 */
template<class TC>
class BackdoorShaper : public TC, public virtual Timed
{
        using Timed::initialize;

    public:
        /**
         * @brief Constructor
         */
        BackdoorShaper();

        /**
         * @brief Destructor
         */
        virtual ~BackdoorShaper();

    private:
        /**
         * @brief Dedicated queue for each priority of Q-tagged messages
         */
        cQueue bQueue;
        /**
         * @brief caches queue size in bytes
         */
        size_t bQueueSize;
    protected:
        /**
         * @brief Signal that is emitted when the queue length of Q-tagged messages changes.
         */
        static simsignal_t bQueueLengthSignal;
        /**
         * @brief Signal that is emitted when the queue size of rate-constrained messages changes.
         */
        static simsignal_t bQueueSizeSignal;

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
         * according to the specification for RCMessages.
         *
         * Rate-constrained messages are send immediately, lower priority frames are queued
         * as long as there are rate-constrained messages waiting.
         * If the mac layer is idle, messages are picked from the queues according
         * to the priorities, using the template class.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Queues messages in the correct queue
         *
         * Rate-constrained messages are queued in this module, other messages are forwarded to the
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

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
};

template<class TC>
simsignal_t BackdoorShaper<TC>::bQueueLengthSignal = cComponent::registerSignal("BackdoorQueueLength");
template<class TC>
simsignal_t BackdoorShaper<TC>::bQueueSizeSignal = cComponent::registerSignal("BackdoorQueueSize");

template<class TC>
BackdoorShaper<TC>::BackdoorShaper()
{
    bQueue.setName("Backdoor Messages");
    bQueueSize = 0;
    WATCH(bQueueSize);
}

template<class TC>
BackdoorShaper<TC>::~BackdoorShaper()
{
}

template<class TC>
void BackdoorShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        Timed::initialize();
        //Send initial signal to create statistic
        cComponent::emit(bQueueLengthSignal, static_cast<unsigned long>(bQueue.getLength()));
        //Send initial signal to create statistic
        cComponent::emit(bQueueSizeSignal, static_cast<unsigned long>(0));
    }
}

template<class TC>
int BackdoorShaper<TC>::numInitStages() const
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
void BackdoorShaper<TC>::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("Backdoorin"))
    {
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
    else
    {
        if (TC::getNumPendingRequests())
        {
            TC::handleMessage(msg);
        }
        else
        {
            TC::enqueueMessage(msg);
        }
    }
}

template<class TC>
void BackdoorShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn("Backdoorin"))
    {
        bQueue.insert(msg);
        cComponent::emit(bQueueLengthSignal, static_cast<unsigned long>(bQueue.getLength()));
        bQueueSize+=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(msg)->getByteLength());
        cComponent::emit(bQueueSizeSignal, static_cast<unsigned long>(bQueueSize));
        TC::notifyListeners();
        EV_TRACE << "Interface not idle queuing Ethernet frame" << endl;
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void BackdoorShaper<TC>::requestPacket()
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
cMessage* BackdoorShaper<TC>::pop()
{
    Enter_Method("pop()");
    if (!bQueue.isEmpty())
    {
        cMessage* message = static_cast<cMessage*>(bQueue.pop());
        cComponent::emit(bQueueLengthSignal, static_cast<unsigned long>(bQueue.getLength()));
        bQueueSize-=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(message)->getByteLength());
        cComponent::emit(bQueueSizeSignal, static_cast<unsigned long>(bQueueSize));
        return message;
    }
    return TC::pop();
}

template<class TC>
cMessage* BackdoorShaper<TC>::front()
{
    Enter_Method("front()");
    if (!bQueue.isEmpty())
    {
        cMessage* message = static_cast<cMessage*>(bQueue.front());
        return message;
    }
    return TC::front();
}

template<class TC>
bool BackdoorShaper<TC>::isEmpty()
{
    return bQueue.isEmpty() && TC::isEmpty();
}

template<class TC>
void BackdoorShaper<TC>::clear()
{
    TC::clear();
    bQueue.clear();
}

template<class TC>
void BackdoorShaper<TC>::handleParameterChange(const char* parname)
{
    TC::handleParameterChange(parname);
}

}

#endif /* CORE4INET_LINKLAYER_SHAPER_BASE_BACKDOORSHAPER_H_ */
