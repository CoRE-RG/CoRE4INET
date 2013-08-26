#ifndef __TTE4INET_RCTRAFFICCONDITIONER_H
#define __TTE4INET_RCTRAFFICCONDITIONER_H

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
class RCTrafficConditioner : public TC
{
    public:
        /**
         * @brief Constructor
         */
        RCTrafficConditioner();
        /**
         * @brief Destructor
         */
        ~RCTrafficConditioner();

    private:
        /**
         * @brief Dedicated queue for each priority of rate-constrained messages
         */
        cQueue rcQueue[NUM_RC_PRIORITIES];
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
RCTrafficConditioner<TC>::RCTrafficConditioner(){
    for (unsigned int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        char strBuf[64];
        snprintf(strBuf,64,"RC Priority %d Messages", i);
        rcQueue[i].setName(strBuf);
    }
}

template <class TC>
RCTrafficConditioner<TC>::~RCTrafficConditioner(){
}

template <class TC>
void RCTrafficConditioner<TC>::initialize()
{
    TC::initialize();
}

template <class TC>
void RCTrafficConditioner<TC>::handleMessage(cMessage *msg)
{
    //Frames arrived on in are rate-constreind frames
    if (msg->arrivedOn("RCin"))
    {
        if (TC::getNumPendingRequests())
        {
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*> (msg->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();
            //Set Transparent clock when frame is PCF
            PCFrame *pcf = dynamic_cast<PCFrame*> (msg);
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
void RCTrafficConditioner<TC>::enqueueMessage(cMessage *msg){
    if(msg->arrivedOn("RCin")){
        int priority = msg->getSenderModule()->par("priority").longValue();
       if (priority > 0 && priority < NUM_RC_PRIORITIES)
       {
           rcQueue[priority].insert(msg);
           TC::notifyListeners();
       }
       else
       {
           rcQueue[0].insert(msg);
           TC::notifyListeners();
           ev << "Priority missing!" << endl;
       }
    }
    else{
        TC::enqueueMessage(msg);
    }
}

template <class TC>
void RCTrafficConditioner<TC>::requestPacket()
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
cMessage* RCTrafficConditioner<TC>::pop()
{
    Enter_Method("pop()");
    //RCFrames
    for (unsigned int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        if (!rcQueue[i].isEmpty())
        {
            EtherFrame *message = (EtherFrame*) rcQueue[i].pop();
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*> (message->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();

            PCFrame *pcf = dynamic_cast<PCFrame*> (message);
            if(pcf){
                setTransparentClock(pcf);
            }
            return message;
        }
    }
    return TC::pop();
}

template <class TC>
cMessage* RCTrafficConditioner<TC>::front()
{
    Enter_Method("front()");
    //RCFrames
    for (unsigned int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        if (!rcQueue[i].isEmpty())
        {
            EtherFrame *message = (EtherFrame*) rcQueue[i].front();
            return message;
        }
    }
    return TC::front();
}

template <class TC>
bool RCTrafficConditioner<TC>::isEmpty()
{
    bool empty = true;
    for (unsigned int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        empty &= rcQueue[i].isEmpty();
    }
    empty &= TC::isEmpty();
    return empty;
}

template <class TC>
void RCTrafficConditioner<TC>::clear()
{
    TC::clear();
    for (unsigned int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        rcQueue[i].clear();
    }
}

template <class TC>
void RCTrafficConditioner<TC>::setTransparentClock(PCFrame *pcf){
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

