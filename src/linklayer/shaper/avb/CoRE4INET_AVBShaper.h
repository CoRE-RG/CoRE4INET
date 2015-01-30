/*
 * CoRE4INET_AVBShaper.h
 *
 *  Created on: 30.01.2015
 *      Author: Philipp
 */

#ifndef CORE4INET_AVBSHAPER_H_
#define CORE4INET_AVBSHAPER_H_

//CoRE4INET
#include "CoRE4INET_AVBBuffer.h"

using namespace std;

namespace CoRE4INET {

/**
 * @brief A Shaper for AVB SR-Class A and B Messages.
 *
 * The TTShaper only allows lower priorities to transmit when the credit is <= 0.
 *
 * @author Philipp Meyer
 */
template<class TC>
class AVBShaper : public TC
{
    public:
        /**
         * @brief Constructor
         */
        AVBShaper(string srClass);
        /**
         * @brief Destructor
         */
        ~AVBShaper();

    private:
        /**
         * @brief Queue for AVB-Messages. Will be only filled when there AVB bursts possible.
         */
        cQueue avbQueue;

        AVBBuffer *avbBuffer;

        string avbQueueLengthSignalName;
        string avbBufferName;
        string avbInName;

    protected:
        /**
         * @brief Signal that is emitted when the queue length of time-triggered messages changes.
         */
        static simsignal_t avbQueueLengthSignal;

    protected:
        /**
         * @brief Initialization of the module
         *
         * @param stage The stages. Module initializes when stage==0
         */
        virtual void initialize(int stage);

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
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Queues messages in the correct queue
         *
         * AVB messages are queued in this module, other messages are forwarded to the
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
         * send-on-request mechanism. Returns nullptr if the queue is empty.
         *
         * @return the message with the highest priority from any queue. nullptr if the
         * queues are empty or cannot send due to the traffic policies.
         */
        virtual cMessage *pop();

        /**
         * @brief Returns a pointer to a frame directly from the queues.
         *
         * front must return a pointer to the same message pop() would return.
         *
         * @return pointer to the message with the highest priority from any queue. nullptr if the
         * queues are empty
         */
        virtual cMessage *front();
};

template<class TC>
AVBShaper<TC>::AVBShaper(string srClass)
{
    avbQueue.setName("AVB Messages");
    if(srClass.compare("A") == 0){
        avbQueueLengthSignalName = "avbAQueueLength";
        avbBufferName = "avbABuffer";
        avbInName = "AVBAin";
    }
    if(srClass.compare("B") == 0){
        avbQueueLengthSignalName = "avbBQueueLength";
        avbBufferName = "avbBBuffer";
        avbInName = "AVBBin";
    }
    avbQueueLengthSignal = cComponent::registerSignal(avbQueueLengthSignalName.c_str());
}

template<class TC>
AVBShaper<TC>::~AVBShaper()
{
    avbQueue.clear();
}

template<class TC>
void AVBShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        int portIndex = cModule::getParentModule()->getIndex();
        avbBuffer = dynamic_cast<AVBBuffer*>(cModule::getParentModule()->getParentModule()->getSubmodule(avbBufferName.c_str(),
                portIndex));
    }
}

template<class TC>
void AVBShaper<TC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn(avbInName.c_str()))
    {
        if (TC::getNumPendingRequests() && avbBuffer->getCredit() >= 0)
        {
            TC::framesRequested--;
            cSimpleModule::send(msg, cModule::gateBaseId("out"));
            SimTime duration = TC::outChannel->calculateDuration(msg);
            //duration += (INTERFRAME_GAP_BITS + ((PREAMBLE_BYTES + SFD_BYTES) * 8)) / TC::outChannel->getNominalDatarate();
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

template<class TC>
void AVBShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn(avbInName.c_str()))
    {
        avbQueue.insert(msg);
        cComponent::emit(avbQueueLengthSignal, avbQueue.length());
        TC::notifyListeners();
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void AVBShaper<TC>::requestPacket()
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
cMessage* AVBShaper<TC>::pop()
{
    Enter_Method
    ("pop()");
    //AVBFrames
    if (avbBuffer->initialized())
        avbBuffer->refresh();
    if (!avbQueue.isEmpty() && avbBuffer->getCredit() >= 0)
    {
        cMessage *msg = static_cast<cMessage*>(avbQueue.pop());
        cComponent::emit(avbQueueLengthSignal, avbQueue.length());
        SimTime duration = TC::outChannel->calculateDuration(msg);
        avbBuffer->sendSlope(duration);
        return msg;
    }
    else if (avbBuffer->getCredit() <= 0)
    {
        return TC::pop();
    }
    return nullptr;
}

template<class TC>
cMessage* AVBShaper<TC>::front()
{
    Enter_Method
    ("front()");
    //AVBFrames
    if (!avbQueue.isEmpty())
    {
        cMessage *msg = static_cast<cMessage*>(avbQueue.front());
        return msg;
    }
    return TC::front();
}

template<class TC>
bool AVBShaper<TC>::isEmpty()
{
    return avbQueue.isEmpty() && TC::isEmpty();
}

template<class TC>
void AVBShaper<TC>::clear()
{
    TC::clear();
    avbQueue.clear();
}

}

#endif /* CORE4INET_AVBSHAPER_H_ */
