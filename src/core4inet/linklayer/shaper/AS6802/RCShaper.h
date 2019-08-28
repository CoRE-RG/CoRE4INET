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

#ifndef CORE4INET_RCSHAPER_H
#define CORE4INET_RCSHAPER_H

//CoRE4INET
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"
#include "core4inet/utilities/HelperFunctions.h"
//Auto-generated Messages
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"

//INET
#include "inet/linklayer/ethernet/EtherMACFullDuplex.h"

//Std
#include <unordered_map>

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
        using TC::receiveSignal;

        /**
         * @brief Constructor
         */
        RCShaper();

        /**
         * @brief Destructor
         */
        virtual ~RCShaper() override;

        /**
         * @brief receives signal from mac module and resets bag on rxPk signal from mac
         *
         * Checks if there is a buffer registered for this messages and if there is one resets the bag
         *
         * @param source source of the signal
         * @param signalID id of the signal
         * @param obj ptr to the object. In this case an EtherFrame currently under transmission
         */
        virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

    private:
        /**
         * @brief Dedicated queue for each priority of rate-constrained messages
         */
        std::vector<cQueue> rcQueue;
        /**
         * @brief caches queue size in bytes
         */
        std::vector<size_t> rcQueueSize;

        /**
         * @brief caches numRCpriority parameter for faster execution
         */
        size_t numRcPriority;

        /**
         * @brief map to store a pointer of a buffer to reset for a specific frame
         */
        std::unordered_map<cMessage *, RCBuffer*> resetPtrMap;

    protected:
        /**
         * @brief Signal that is emitted when the queue length of rate-constrained messages changes.
         */
        std::vector<simsignal_t> rcQueueLengthSignals;
        /**
         * @brief Signal that is emitted when the queue size of rate-constrained messages changes.
         */
        std::vector<simsignal_t> rcQueueSizeSignals;

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
};

template<class TC>
RCShaper<TC>::RCShaper()
{
}

template<class TC>
RCShaper<TC>::~RCShaper()
{
    resetPtrMap.clear();
}

template<class TC>
void RCShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        Timed::initialize();

        /*inet::EtherMACFullDuplex* mac =
         dynamic_cast<inet::EtherMACFullDuplex*>(gate("out")->getPathEndGate()->getOwner());
         mac->subscribe("txPk", this);*/

        numRcPriority = static_cast<size_t>(par("numRCpriority"));
        for (unsigned int i = 0; i < numRcPriority; i++)
        {
            cQueue queue;
            queue.setName(("RC Priority " + std::to_string(i) + " Messages").c_str());
            rcQueue.push_back(queue);
            rcQueueSize.push_back(0);

            simsignal_t signal = registerSignal(("rc" + std::to_string(i) + "QueueLength").c_str());

            cProperty *statisticTemplate = getProperties()->get("statisticTemplate", "rcQueueLength");
            getEnvir()->addResultRecorders(this, signal, ("rc" + std::to_string(i) + "QueueLength").c_str(), statisticTemplate);

            rcQueueLengthSignals.push_back(signal);
            //Send initial signal to create statistic
            cComponent::emit(signal, static_cast<unsigned long>(queue.getLength()));

            signal = registerSignal(("rc" + std::to_string(i) + "QueueSize").c_str());

            statisticTemplate = getProperties()->get("statisticTemplate", "rcQueueSize");
            getEnvir()->addResultRecorders(this, signal, ("rc" + std::to_string(i) + "QueueSize").c_str(), statisticTemplate);

            rcQueueSizeSignals.push_back(signal);
            //Send initial signal to create statistic
            cComponent::emit(signal, static_cast<unsigned long>(0));
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
            {
                resetPtrMap[msg] = rcBuffer;
            }
            rcBuffer->resetBag();
            //Set Transparent clock when frame is PCF
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
void RCShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn("RCin"))
    {
        long priority = msg->getSenderModule()->par("priority");
        if (priority >= 0 && static_cast<size_t>(priority) < numRcPriority)
        {
            rcQueue[static_cast<size_t>(priority)].insert(msg);
            if (simTime() > getSimulation()->getWarmupPeriod())
            {
                cComponent::emit(rcQueueLengthSignals[static_cast<size_t>(priority)],
                        static_cast<unsigned long>(rcQueue[static_cast<size_t>(priority)].getLength()));
            }
            rcQueueSize[static_cast<size_t>(priority)] +=
                    static_cast<size_t>(check_and_cast<inet::EtherFrame*>(msg)->getByteLength());
            if (simTime() > getSimulation()->getWarmupPeriod())
            {
                cComponent::emit(rcQueueSizeSignals[static_cast<size_t>(priority)],
                        static_cast<unsigned long>(rcQueueSize[static_cast<size_t>(priority)]));
            }

            TC::notifyListeners();
        }
        else
        {
            rcQueue[0].insert(msg);
            TC::notifyListeners();
            EV_WARN << "Priority of message " << msg->getFullName()
                    << " missing or not within range, using default priority 0!" << endl;
        }
        EV_TRACE << "Interface not idle queuing RC frame" << endl;
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void RCShaper<TC>::requestPacket()
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
cMessage* RCShaper<TC>::pop()
{
    Enter_Method("pop()");
    //RCFrames
    for (unsigned int i = 0; i < numRcPriority; i++)
    {
        if (!rcQueue[i].isEmpty())
        {
            inet::EtherFrame *message = static_cast<inet::EtherFrame*>(rcQueue[i].pop());
            if (simTime() > getSimulation()->getWarmupPeriod())
            {
                cComponent::emit(rcQueueLengthSignals[i], static_cast<unsigned long>(rcQueue[i].getLength()));
            }
            rcQueueSize[i]-=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(message)->getByteLength());
            if (simTime() > getSimulation()->getWarmupPeriod())
            {
                cComponent::emit(rcQueueSizeSignals[i], static_cast<unsigned long>(rcQueueSize[i]));

            }
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
            if (rcBuffer)
            {
                resetPtrMap[message] = rcBuffer;
            }
            rcBuffer->resetBag();

            PCFrame *pcf = dynamic_cast<PCFrame*>(message);
            if (pcf)
            {
                setTransparentClock(pcf, cModule::getParentModule()->par("static_tx_delay").doubleValue(), getTimer());
            }
            return message;
        }
    }
    return TC::pop();
}

template<class TC>
cMessage* RCShaper<TC>::front()
{
    Enter_Method("front()");
    //RCFrames
    for (unsigned int i = 0; i < numRcPriority; i++)
    {
        if (!rcQueue[i].isEmpty())
        {
            inet::EtherFrame *message = static_cast<inet::EtherFrame*>(rcQueue[i].front());
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

template<class TC>
void RCShaper<TC>::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
    /*if(strncmp(getSignalName(signalID), "txPk", 5)==0){
     std::unordered_map<cMessage *, RCBuffer* >::const_iterator result = resetPtrMap.find(check_and_cast<cMessage*>(obj));
     if(result != resetPtrMap.end()){
     (*result).second->resetBag();
     resetPtrMap.erase(result);
     }
     }*/
    TC::receiveSignal(source, signalID, obj, details);
}

}

#endif

