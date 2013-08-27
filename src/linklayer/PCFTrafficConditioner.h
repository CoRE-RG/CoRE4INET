#ifndef __TTE4INET_PCFTRAFFICCONDITIONER_H
#define __TTE4INET_PCFTRAFFICCONDITIONER_H

#include <ModuleAccess.h>
#include <RCBuffer.h>
#include <PCFrame_m.h>
#include <TTEScheduler.h>
#include <HelperFunctions.h>

namespace TTEthernetModel {

/**
 * @brief Represents the part of a port that sends messages (TX)
 *
 */
template <class TC>
class PCFTrafficConditioner : public TC
{
    public:
        /**
         * @brief Constructor
         */
        PCFTrafficConditioner();
        /**
         * @brief Destructor
         */
        ~PCFTrafficConditioner();

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

    private:
        /**
         * @brief Sets the transparent clock field in a protocol control frame
         * according to the actual sending time
         *
         * @param pcf the protocol control frame
         */
        virtual void setTransparentClock(PCFrame *pcf);
};

template <class TC>
simsignal_t PCFTrafficConditioner<TC>::pcfQueueLengthSignal = SIMSIGNAL_NULL;

template <class TC>
PCFTrafficConditioner<TC>::PCFTrafficConditioner(){
    pcfQueue.setName("PCF Messages");
}

template <class TC>
PCFTrafficConditioner<TC>::~PCFTrafficConditioner(){
}

template <class TC>
void PCFTrafficConditioner<TC>::initialize()
{
    TC::initialize();
    pcfQueueLengthSignal = cComponent::registerSignal("pcfQueueLength");
}

template <class TC>
void PCFTrafficConditioner<TC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("PCFin"))
    {
        if (TC::getNumPendingRequests())
        {
            PCFrame *pcf = dynamic_cast<PCFrame*>(msg);
            if(pcf){
                setTransparentClock(pcf);
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
void PCFTrafficConditioner<TC>::enqueueMessage(cMessage *msg){
    if(msg->arrivedOn("PCFin")){
        pcfQueue.insert(msg);
        TC::notifyListeners();
    }
    else{
        TC::enqueueMessage(msg);
    }
}

template <class TC>
void PCFTrafficConditioner<TC>::requestPacket()
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
cMessage* PCFTrafficConditioner<TC>::pop()
{
    Enter_Method("pop()");
    //RCFrames
    if (!pcfQueue.isEmpty())
    {
        cMessage *msg = (cMessage*) pcfQueue.pop();
        cComponent::emit(pcfQueueLengthSignal, pcfQueue.length());

        return msg;
    }
    return TC::pop();
}

template <class TC>
cMessage* PCFTrafficConditioner<TC>::front()
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
bool PCFTrafficConditioner<TC>::isEmpty()
{
       return pcfQueue.isEmpty() && TC::isEmpty();
}

template <class TC>
void PCFTrafficConditioner<TC>::clear()
{
    TC::clear();
    pcfQueue.clear();
}

template <class TC>
void PCFTrafficConditioner<TC>::setTransparentClock(PCFrame *pcf){
    uint64_t transparentClock = pcf->getTransparent_clock();

    //Add static delay for this port
    transparentClock+=secondsToTransparentClock(cModule::getParentModule()->par("static_tx_delay").doubleValue());

    //Add dynamic delay for the device
    cArray parlist = pcf->getParList();
    long start = -1;
    for(int i=0;i<parlist.size();i++){
        cMsgPar *parameter = dynamic_cast<cMsgPar*>(parlist.get(i));
        if(parameter){
            if(strncmp(parameter->getName(),"received_total",15)==0 || strncmp(parameter->getName(),"created_total",15)==0){
                start = parameter->longValue();
            }
        }
    }
    if(start >= 0){
        TTEScheduler* scheduler = ((TTEScheduler*)cModule::getParentModule()->getParentModule()->getSubmodule("tteScheduler"));
        transparentClock+=ticksToTransparentClock((scheduler->getTotalTicks()-start),scheduler->par("tick").doubleValue());
    }

    //Set new transparent clock
    pcf->setTransparent_clock(transparentClock);
}

}

#endif

