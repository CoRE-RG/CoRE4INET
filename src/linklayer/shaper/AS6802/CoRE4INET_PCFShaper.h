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

#ifndef __CoRE4INET_PCFSHAPER_H
#define __CoRE4INET_PCFSHAPER_H

//CoRE4INET
#include "CoRE4INET_Timed.h"
#include "CoRE4INET_HelperFunctions.h"
//Auto-generated Messages
#include "PCFrame_m.h"

namespace CoRE4INET {

/**
 * @brief A Shaper for PCFMessages.
 *
 * The PCFShaper only allows lower priorities to transmit when there are no
 * PCF messages queued.
 *
 * @ingroup AS6802
 *
 * @author Till Steinbach
 */
template<class TC>
class PCFShaper : public TC, public virtual Timed
{
        using Timed::initialize;
    public:
        /**
         * @brief Constructor
         */
        PCFShaper();
        /**
         * @brief Destructor
         */
        virtual ~PCFShaper();

    private:
        /**
         * @brief Queue for protocol control messages
         */
        cQueue pcfQueue;
    protected:
        /**
         * @brief Signal that is emitted when the queue length of time-triggered messages changes.
         */
        static simsignal_t pcfQueueLengthSignal;
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
         * according to the specification for PCFMessages.
         *
         * Protocol control frames are send immediately, lower priority frames are queued
         * as long as there are pcf messages waiting.
         * If the mac layer is idle, messages are picked from the queues according
         * to the priorities, using the template class.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Queues messages in the correct queue
         *
         * Protocol control frames are queued in this module, other messages are forwarded to the
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
simsignal_t PCFShaper<TC>::pcfQueueLengthSignal = cComponent::registerSignal("pcfQueueLength");

template<class TC>
PCFShaper<TC>::PCFShaper()
{
    pcfQueue.setName("PCF Messages");
}

template<class TC>
PCFShaper<TC>::~PCFShaper()
{
}

template<class TC>
void PCFShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        Timed::initialize();
        //Send initial signal to create statistic
        cComponent::emit(pcfQueueLengthSignal, static_cast<unsigned long>(pcfQueue.length()));
    }
}

template<class TC>
int PCFShaper<TC>::numInitStages() const
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
void PCFShaper<TC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("PCFin"))
    {
        if (TC::getNumPendingRequests())
        {
            PCFrame *pcf = dynamic_cast<PCFrame*>(msg);
            if (pcf)
            {
                setTransparentClock(pcf, cModule::getParentModule()->par("static_tx_delay").doubleValue(), getTimer());
            }
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
void PCFShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn("PCFin"))
    {
        pcfQueue.insert(msg);
        TC::notifyListeners();
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void PCFShaper<TC>::requestPacket()
{
    Enter_Method
    ("requestPacket()");
    //Feed the MAC layer with the next frame
    TC::framesRequested++;

    if (cMessage *msg = pop())
    {
        TC::framesRequested--;
        cSimpleModule::send(msg, cModule::gateBaseId("out"));
    }
}

template<class TC>
cMessage* PCFShaper<TC>::pop()
{
    Enter_Method
    ("pop()");
    //RCFrames
    if (!pcfQueue.isEmpty())
    {
        cMessage *msg = static_cast<cMessage*>(pcfQueue.pop());
        cComponent::emit(pcfQueueLengthSignal, static_cast<unsigned long>(pcfQueue.length()));

        PCFrame *pcf = dynamic_cast<PCFrame*>(msg);
        if (pcf)
        {
            setTransparentClock(pcf, cModule::getParentModule()->par("static_tx_delay").doubleValue(), getTimer());
        }
        return msg;
    }
    return TC::pop();
}

template<class TC>
cMessage* PCFShaper<TC>::front()
{
    Enter_Method
    ("front()");
    //RCFrames
    if (!pcfQueue.isEmpty())
    {
        cMessage *msg = static_cast<cMessage*>(pcfQueue.front());
        return msg;
    }
    return TC::front();
}

template<class TC>
bool PCFShaper<TC>::isEmpty()
{
    return pcfQueue.isEmpty() && TC::isEmpty();
}

template<class TC>
void PCFShaper<TC>::clear()
{
    TC::clear();
    pcfQueue.clear();
}

}

#endif

