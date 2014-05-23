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

#ifndef __CoRE4INET_RCSHAPER_H
#define __CoRE4INET_RCSHAPER_H

#include "ModuleAccess.h"
#include "CoRE4INET_RCBuffer.h"
#include "PCFrame_m.h"
#include "CoRE4INET_HelperFunctions.h"
#include "CoRE4INET_Timed.h"

namespace CoRE4INET {

/**
 * @brief A Shaper for RCMessages.
 *
 * The RCShaper only allows lower priorities to transmit when there are no
 * RC messages queued.
 *
 * @ingroup AS6802
 *
 * @author Till Steinbach
 */
template<class TC>
class RCShaper : public TC, public virtual Timed
{
        using Timed::initialize;
    public:
        /**
         * @brief Constructor
         */
        RCShaper();
        /**
         * @brief Destructor
         */
        ~RCShaper();

    private:
        /**
         * @brief Dedicated queue for each priority of rate-constrained messages
         */
        std::vector<cQueue> rcQueue;

        /**
         * @brief caches numRCpriority parameter for faster execution
         */
        size_t numRcPriority;
    protected:
        /**
         * @brief Signal that is emitted when the queue length of time-triggered messages changes.
         */
        std::vector<simsignal_t> rcQueueLengthSignals;
    protected:
        /**
         * Initializes the module
         *
         * @param stage The stages. Module initializes when stage==0
         */
        virtual void initialize(int stage);

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return returns 1 or more depending on inheritance
         */
        virtual int numInitStages() const;

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
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Queues messages in the correct queue
         *
         * Rate-constrained messages are queued in this module, other messages are forwarded to the
         * template classes enqueueMessage method
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
         *
         * @param msg the message to be queued
         */
        virtual void requestPacket();

        /**
         * @brief Returns true when there are no pending messages.
         *
         * @return true if all queues are empty.
         */
        virtual bool isEmpty();

        /**
         * @brief Clears all queued packets and stored requests.
         */
        virtual void clear();

        /**
         * @brief Returns a frame directly from the queues, bypassing the primary,
         * send-on-request mechanism. Returns NULL if the queue is empty.
         *
         * @return the message with the highest priority from any queue. NULL if the
         * queues are empty or cannot send due to the traffic policies.
         */
        virtual cMessage *pop();

        /**
         * @brief Returns a pointer to a frame directly from the queues.
         *
         * front must return a pointer to the same message pop() would return.
         *
         * @return pointer to the message with the highest priority from any queue. NULL if the
         * queues are empty
         */
        virtual cMessage *front();
};

template<class TC>
RCShaper<TC>::RCShaper()
{
}

template<class TC>
RCShaper<TC>::~RCShaper()
{
}

template<class TC>
void RCShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        Timed::initialize();

        numRcPriority = par("numRCpriority").longValue();
        for (unsigned int i = 0; i < numRcPriority; i++)
        {
            char strBuf[32];
            cQueue queue;
            snprintf(strBuf, 32, "RC Priority %d Messages", i);
            queue.setName(strBuf);
            rcQueue.push_back(queue);

            snprintf(strBuf, 32, "rc%dQueueLength", i);
            simsignal_t signal = registerSignal(strBuf);

            cProperty *statisticTemplate = getProperties()->get("statisticTemplate", "rcQueueLength");
            ev.addResultRecorders(this, signal, strBuf, statisticTemplate);

            rcQueueLengthSignals.push_back(signal);
            //Send initial signal to create statistic
            cComponent::emit(signal, (unsigned long) queue.length());
        }
    }
}

template<class TC>
int RCShaper<TC>::numInitStages() const
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
void RCShaper<TC>::handleMessage(cMessage *msg)
{
    //Frames arrived on in are rate-constreind frames
    if (msg->arrivedOn("RCin"))
    {
        if (TC::getNumPendingRequests())
        {
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(msg->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();
            //Set Transparent clock when frame is PCF
            PCFrame *pcf = dynamic_cast<PCFrame*>(msg);
            if (pcf)
            {
                setTransparentClock(pcf, cModule::getParentModule()->par("static_tx_delay").doubleValue(), timer);
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
void RCShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn("RCin"))
    {
        int priority = msg->getSenderModule()->par("priority").longValue();
        if (priority > 0 && (unsigned int) priority < numRcPriority)
        {
            rcQueue[priority].insert(msg);
            cComponent::emit(rcQueueLengthSignals[priority], (unsigned long) rcQueue[priority].length());
            TC::notifyListeners();
        }
        else
        {
            rcQueue[0].insert(msg);
            TC::notifyListeners();
            ev << "Priority missing!" << endl;
        }
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void RCShaper<TC>::requestPacket()
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
cMessage* RCShaper<TC>::pop()
{
    Enter_Method
    ("pop()");
    //RCFrames
    for (unsigned int i = 0; i < numRcPriority; i++)
    {
        if (!rcQueue[i].isEmpty())
        {
            EtherFrame *message = (EtherFrame*) rcQueue[i].pop();
            cComponent::emit(rcQueueLengthSignals[i], (unsigned long) rcQueue[i].length());
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();

            PCFrame *pcf = dynamic_cast<PCFrame*>(message);
            if (pcf)
            {
                setTransparentClock(pcf, cModule::getParentModule()->par("static_tx_delay").doubleValue(), timer);
            }
            return message;
        }
    }
    return TC::pop();
}

template<class TC>
cMessage* RCShaper<TC>::front()
{
    Enter_Method
    ("front()");
    //RCFrames
    for (unsigned int i = 0; i < numRcPriority; i++)
    {
        if (!rcQueue[i].isEmpty())
        {
            EtherFrame *message = (EtherFrame*) rcQueue[i].front();
            return message;
        }
    }
    return TC::front();
}

template<class TC>
bool RCShaper<TC>::isEmpty()
{
    bool empty = true;
    for (unsigned int i = 0; i < numRcPriority; i++)
    {
        empty &= rcQueue[i].isEmpty();
    }
    empty &= TC::isEmpty();
    return empty;
}

template<class TC>
void RCShaper<TC>::clear()
{
    TC::clear();
    for (unsigned int i = 0; i < numRcPriority; i++)
    {
        rcQueue[i].clear();
    }
}

}

#endif

