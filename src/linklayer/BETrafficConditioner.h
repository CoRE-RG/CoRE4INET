#ifndef __TTE4INET_BETRAFFICCONDITIONER_H
#define __TTE4INET_BETRAFFICCONDITIONER_H

#include <ModuleAccess.h>

namespace TTEthernetModel {

/**
 * @brief Represents the part of a port that sends messages (TX)
 *
 */
template <class TC>
class BETrafficConditioner : public TC
{
    public:
        /**
         * @brief Constructor
         */
        BETrafficConditioner();
        /**
         * @brief Destructor
         */
        ~BETrafficConditioner();
    protected:
            /**
             * @brief Signal that is emitted when the queue length of best-effort messages changes.
             */
            static simsignal_t beQueueLengthSignal;
    private:
            /**
             * @brief Queue for best-effort messages
             */
            cQueue beQueue;
    protected:
        /**
         * @brief Initialization of the module
         */
        virtual void initialize();


        /**
         * @brief Forwards the messages from the different buffers and LLC
         * according to the TTEthernet specification.
         *
         * Time-triggered messages are send immediately, rate-constrained and best-effort
         * messages are delayed if they do not fit in the gap until the next time-triggered
         * message. If the lower layer is idle messages are picked from the queues according
         * to the priorities.
         * Time-triggered buffers can free the bandwidth reservation mechanism by sending
         * a TTBufferEmpty message.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg);

        virtual void enqueueMessage(cMessage *msg);

        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
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
         * Returns a packet directly from the queue, bypassing the primary,
         * send-on-request mechanism. Returns NULL if the queue is empty.
         */
        virtual cMessage *pop();

        virtual cMessage *front();
};


template <class TC>
simsignal_t BETrafficConditioner<TC>::beQueueLengthSignal = SIMSIGNAL_NULL;

template <class TC>
BETrafficConditioner<TC>::BETrafficConditioner(){
    beQueue.setName("BE Messages");
}

template <class TC>
BETrafficConditioner<TC>::~BETrafficConditioner(){
    beQueue.clear();
}

template <class TC>
void BETrafficConditioner<TC>::initialize()
{
    TC::initialize();
    beQueueLengthSignal = cComponent::registerSignal("beQueueLength");
}

template <class TC>
void BETrafficConditioner<TC>::handleMessage(cMessage *msg)
{
    //Frames arrived on in are best-effort frames
    if (msg->arrivedOn("in"))
    {
        // If there are framesRequested the MAC layer is currently idle
        if(TC::getNumPendingRequests())
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

template <class TC>
void BETrafficConditioner<TC>::enqueueMessage(cMessage *msg){
    if(msg->arrivedOn("in")){
        beQueue.insert(msg);
        cComponent::emit(beQueueLengthSignal, beQueue.length());
        TC::notifyListeners();
    }
    else{
        TC::enqueueMessage(msg);
    }
}

template <class TC>
void BETrafficConditioner<TC>::requestPacket()
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

template <class TC>
cMessage* BETrafficConditioner<TC>::pop()
{
    Enter_Method("pop()");
    //BEFrames
    if (!beQueue.isEmpty())
    {
        cMessage* message = (cMessage*) beQueue.pop();
        cComponent::emit(beQueueLengthSignal, beQueue.length());
        return message;
    }
    return TC::pop();
}

template <class TC>
cMessage* BETrafficConditioner<TC>::front()
{
    Enter_Method("front()");
    //BEFrames
    if (!beQueue.isEmpty())
    {
        cMessage* message = (cMessage*) beQueue.front();
        return message;
    }
    return TC::front();
}

template <class TC>
bool BETrafficConditioner<TC>::isEmpty()
{
    return beQueue.isEmpty() && TC::isEmpty();
}

template <class TC>
void BETrafficConditioner<TC>::clear()
{
    TC::clear();
    beQueue.clear();
}


}

#endif

