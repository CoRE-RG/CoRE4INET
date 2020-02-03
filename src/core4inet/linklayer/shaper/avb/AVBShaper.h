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

#ifndef CORE4INET_AVBSHAPER_H_
#define CORE4INET_AVBSHAPER_H_

//CoRE4INET
#include "core4inet/base/avb/AVBDefs_m.h"
#include "core4inet/buffer/avb/AVBBuffer.h"
//Auto-generated messages
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"

namespace CoRE4INET {

/**
 * @brief A Shaper for AVB SR-Class A and B Messages.
 *
 * The TTShaper only allows lower priorities to transmit when the credit is <= 0.
 *
 * @author Philipp Meyer
 */
template<SR_CLASS SRCLASS, class TC>
class AVBShaper : public TC, public virtual cListener
{
    public:
        enum ShaperState
        {
            TRANSMITTING_STATE = 1, IDLE_STATE, BLOCKED_STATE,
        };
    public:
        using TC::receiveSignal;

        /**
         * @brief Constructor
         */
        AVBShaper();

        /**
         * @brief Destructor
         */
        virtual ~AVBShaper() override;

        /**
         * @brief receives signals from mac for CBS calculations and state
         */
        void receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) override;

    private:
        /**
         * @brief Queue for AVB-Messages. Will be only filled when there AVB bursts possible.
         */
        cQueue avbQueue;
        /**
         * @brief caches queue size in bytes
         */
        size_t avbQueueSize;

        /**
         * @brief Pointer to AVBBuffer
         */
        AVBBuffer *avbBuffer;

        /**
         * @brief Name of the avbQueueLengthSignal
         */
        std::string avbQueueLengthSignalName;
        /**
         * @brief Name of the avbQueueSizeSignal
         */
        std::string avbQueueSizeSignalName;

        /**
         * @brief Name of the avbBuffer
         */
        std::string avbBufferName;

        /**
         * @brief Name of the avbIn
         */
        std::string avbInName;

        /**
         * @brief current state of the shaper;
         */
        ShaperState state;

    protected:
        /**
         * @brief Signal that is emitted when the queue length of AVB messages changes.
         */
        static simsignal_t avbQueueLengthSignal;
        /**
         * @brief Signal that is emitted when the queue size (in bytes) of AVB messages changes.
         */
        static simsignal_t avbQueueSizeSignal;

    protected:
        /**
         * @brief Initialization of the module
         *
         * @param stage The stages. Module initializes when stage==0
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Forwards the messages from the different buffers and LLC
         * according to the specification for AVB Class Messages.
         *
         * AVB messages are send immediately, lower priority frames are delayed
         * if the credit is positive.
         * If the mac layer is idle, messages are picked from the queues according
         * to the priorities, using the template class.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Queues messages in the correct queue
         *
         * AVB messages are queued in this module, other messages are forwarded to the
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

template<SR_CLASS SRCLASS, class TC>
simsignal_t AVBShaper<SRCLASS, TC>::avbQueueLengthSignal;
template<SR_CLASS SRCLASS, class TC>
simsignal_t AVBShaper<SRCLASS, TC>::avbQueueSizeSignal;

template<SR_CLASS SRCLASS, class TC>
AVBShaper<SRCLASS, TC>::AVBShaper()
{
    state = IDLE_STATE;

    if (SRCLASS == SR_CLASS::A)
    {
        avbQueue.setName("AVBA Messages");
        avbQueueLengthSignalName = "avbAQueueLength";
        avbQueueSizeSignalName = "avbAQueueSize";
        avbBufferName = "avbABuffer";
        avbInName = "AVBAin";
    }
    else if (SRCLASS == SR_CLASS::B)
    {
        avbQueue.setName("AVBB Messages");
        avbQueueLengthSignalName = "avbBQueueLength";
        avbQueueSizeSignalName = "avbBQueueSize";
        avbBufferName = "avbBBuffer";
        avbInName = "AVBBin";
    }
    else{
        throw cRuntimeError("No valid SR-Class specified for shaper");
    }
    avbQueueLengthSignal = cComponent::registerSignal(avbQueueLengthSignalName.c_str());
    avbQueueSizeSignal = cComponent::registerSignal(avbQueueSizeSignalName.c_str());
}

template<SR_CLASS SRCLASS, class TC>
AVBShaper<SRCLASS, TC>::~AVBShaper()
{
    avbQueue.clear();
}

template<SR_CLASS SRCLASS, class TC>
void AVBShaper<SRCLASS, TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        int portIndex = cModule::getParentModule()->getIndex();
        avbBuffer = dynamic_cast<AVBBuffer*>(cModule::getParentModule()->getParentModule()->getSubmodule(
                avbBufferName.c_str(), portIndex));
        if (inet::EtherMACFullDuplex* mac =
                dynamic_cast<inet::EtherMACFullDuplex*>(TC::gate("out")->getPathEndGate()->getOwner()))
        {
            if (!mac->isSubscribed("transmitState", this))
            {
                mac->subscribe("transmitState", this);
            }
        }
    }
}

template<SR_CLASS SRCLASS, class TC>
void AVBShaper<SRCLASS, TC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn(avbInName.c_str()))
    {
        if (TC::getNumPendingRequests() && avbBuffer->getCredit() >= 0)
        {
            TC::framesRequested--;
            AVBFrame* sizeMsg = dynamic_cast<AVBFrame*>(msg->dup());
            sizeMsg->setByteLength(sizeMsg->getByteLength() + PREAMBLE_BYTES + SFD_BYTES + (INTERFRAME_GAP_BITS / 8));
            cSimpleModule::send(msg, cModule::gateBaseId("out"));
            ASSERT(state == IDLE_STATE);
            state = BLOCKED_STATE;
            SimTime duration = TC::outChannel->calculateDuration(sizeMsg);
            delete sizeMsg;
            avbBuffer->sendSlope(duration);
        }
        else
        {
            enqueueMessage(msg);
        }
    }
    else
    {
        if (avbBuffer->getCredit() <= 0)
        {
            TC::handleMessage(msg);
        }
        else
        {
            TC::enqueueMessage(msg);
        }
    }
}

template<SR_CLASS SRCLASS, class TC>
void AVBShaper<SRCLASS, TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn(avbInName.c_str()))
    {
        avbQueue.insert(msg);
        cComponent::emit(avbQueueLengthSignal, static_cast<unsigned long>(avbQueue.getLength()));
        avbQueueSize+=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(msg)->getByteLength());
        cComponent::emit(avbQueueSizeSignal, static_cast<unsigned long>(avbQueueSize));
        TC::notifyListeners();
        EV_TRACE << "Interface not idle queuing AVB frame" << endl;
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<SR_CLASS SRCLASS, class TC>
void AVBShaper<SRCLASS, TC>::requestPacket()
{
    Enter_Method("requestPacket()");
    //Feed the MAC layer with the next frame
    TC::framesRequested++;

    if (cMessage *msg = pop())
    {
        TC::framesRequested--;
        cSimpleModule::send(msg, cModule::gateBaseId("out"));
        ASSERT(state == IDLE_STATE);
        state = BLOCKED_STATE;
    }
}

template<SR_CLASS SRCLASS, class TC>
cMessage* AVBShaper<SRCLASS, TC>::pop()
{
    Enter_Method("pop()");
    //AVBFrames
    if (avbBuffer->initialized())
    avbBuffer->refresh();
    if (!avbQueue.isEmpty() && avbBuffer->getCredit() >= 0)
    {
        cMessage *msg = static_cast<cMessage*>(avbQueue.pop());
        cComponent::emit(avbQueueLengthSignal, static_cast<unsigned long>(avbQueue.getLength()));
        avbQueueSize-=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(msg)->getByteLength());
        cComponent::emit(avbQueueSizeSignal, static_cast<unsigned long>(avbQueueSize));
        AVBFrame* sizeMsg = dynamic_cast<AVBFrame*>(msg->dup());
        sizeMsg->setByteLength(sizeMsg->getByteLength() + PREAMBLE_BYTES + SFD_BYTES + (INTERFRAME_GAP_BITS / 8));
        SimTime duration = TC::outChannel->calculateDuration(sizeMsg);
        delete sizeMsg;
        avbBuffer->sendSlope(duration);
        return msg;
    }
    else if (avbBuffer->getCredit() <= 0)
    {
        return TC::pop();
    }
    return nullptr;
}

template<SR_CLASS SRCLASS, class TC>
cMessage* AVBShaper<SRCLASS, TC>::front()
{
    Enter_Method("front()");
    //AVBFrames
    if (!avbQueue.isEmpty())
    {
        cMessage *msg = static_cast<cMessage*>(avbQueue.front());
        return msg;
    }
    return TC::front();
}

template<SR_CLASS SRCLASS, class TC>
bool AVBShaper<SRCLASS, TC>::isEmpty()
{
    return avbQueue.isEmpty() && TC::isEmpty();
}

template<SR_CLASS SRCLASS, class TC>
void AVBShaper<SRCLASS, TC>::clear()
{
    TC::clear();
    avbQueue.clear();
}

template<SR_CLASS SRCLASS, class TC>
void AVBShaper<SRCLASS, TC>::receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details)
{
    if (strncmp(TC::getSignalName(signalID), "transmitState", 14) == 0)
    {
        inet::EtherMACBase::MACTransmitState macTransmitState = static_cast<inet::EtherMACBase::MACTransmitState>(l);
        if (state == BLOCKED_STATE && macTransmitState == inet::EtherMACBase::MACTransmitState::TRANSMITTING_STATE)
        {
            state = TRANSMITTING_STATE;
        }
        else if (state == TRANSMITTING_STATE
                && (macTransmitState == inet::EtherMACBase::MACTransmitState::TX_IDLE_STATE
                        || macTransmitState == inet::EtherMACBase::MACTransmitState::WAIT_IFG_STATE))
        {
            state = IDLE_STATE;
        }
    }
    TC::receiveSignal(source, signalID, l, details);
}

}

#endif /* CORE4INET_AVBSHAPER_H_ */
