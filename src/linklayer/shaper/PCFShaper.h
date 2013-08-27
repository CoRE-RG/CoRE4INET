#ifndef __TTE4INET_PCFSHAPER_H
#define __TTE4INET_PCFSHAPER_H

#include <ModuleAccess.h>
#include <RCBuffer.h>
#include <PCFrame_m.h>
#include <TTEScheduler.h>
#include <HelperFunctions.h>

namespace TTEthernetModel {

/**
 * @brief A Shaper for PCFMessages.
 *
 * The PCFShaper only allows lower priorities to transmit when there are no
 * PCF messages queued.
 *
 */
template <class TC>
class PCFShaper : public TC
{
    public:
        /**
         * @brief Constructor
         */
        PCFShaper();
        /**
         * @brief Destructor
         */
        ~PCFShaper();

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
         * @brief Initialization of the module
         */
        virtual void initialize();


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
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Queues messages in the correct queue
         *
         * Protocol control frames are queued in this module, other messages are forwarded to the
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

template <class TC>
simsignal_t PCFShaper<TC>::pcfQueueLengthSignal = SIMSIGNAL_NULL;

template <class TC>
PCFShaper<TC>::PCFShaper(){
    pcfQueue.setName("PCF Messages");
}

template <class TC>
PCFShaper<TC>::~PCFShaper(){
}

template <class TC>
void PCFShaper<TC>::initialize()
{
    TC::initialize();
    pcfQueueLengthSignal = cComponent::registerSignal("pcfQueueLength");
}

template <class TC>
void PCFShaper<TC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("PCFin"))
    {
        if (TC::getNumPendingRequests())
        {
            PCFrame *pcf = dynamic_cast<PCFrame*>(msg);
            if(pcf){
                setTransparentClock(pcf, cModule::getParentModule()->par("static_tx_delay").doubleValue(), (TTEScheduler*)cModule::getParentModule()->getParentModule()->getSubmodule("tteScheduler"));
            }
            TC::framesRequested--;
            cSimpleModule::send(msg, cModule::gateBaseId("out"));
        }
        else
        {
            enqueueMessage(msg);
        }
    }
    else{
        if(TC::getNumPendingRequests()){
            TC::handleMessage(msg);
        }
        else{
            TC::enqueueMessage(msg);
        }
    }
}

template <class TC>
void PCFShaper<TC>::enqueueMessage(cMessage *msg){
    if(msg->arrivedOn("PCFin")){
        pcfQueue.insert(msg);
        TC::notifyListeners();
    }
    else{
        TC::enqueueMessage(msg);
    }
}

template <class TC>
void PCFShaper<TC>::requestPacket()
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
cMessage* PCFShaper<TC>::pop()
{
    Enter_Method("pop()");
    //RCFrames
    if (!pcfQueue.isEmpty())
    {
        cMessage *msg = (cMessage*) pcfQueue.pop();
        cComponent::emit(pcfQueueLengthSignal, pcfQueue.length());

        PCFrame *pcf = dynamic_cast<PCFrame*> (msg);
        if(pcf){
            setTransparentClock(pcf, cModule::getParentModule()->par("static_tx_delay").doubleValue(), (TTEScheduler*)cModule::getParentModule()->getParentModule()->getSubmodule("tteScheduler"));
        }
        return msg;
    }
    return TC::pop();
}

template <class TC>
cMessage* PCFShaper<TC>::front()
{
    Enter_Method("front()");
    //RCFrames
    if (!pcfQueue.isEmpty())
    {
        cMessage *msg = (cMessage*) pcfQueue.front();
        return msg;
    }
    return TC::front();
}

template <class TC>
bool PCFShaper<TC>::isEmpty()
{
       return pcfQueue.isEmpty() && TC::isEmpty();
}

template <class TC>
void PCFShaper<TC>::clear()
{
    TC::clear();
    pcfQueue.clear();
}

}

#endif

