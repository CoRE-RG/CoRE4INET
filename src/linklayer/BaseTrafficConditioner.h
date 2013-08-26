#ifndef __TTE4INET_BASETRAFFICCONDITIONER_H
#define __TTE4INET_BASETRAFFICCONDITIONER_H

#include <omnetpp.h>
#include <csimplemodule.h>
#include <INETDefs.h>
#include <TTE4INETDefs.h>
#include <IPassiveQueue.h>
#include <EtherFrame_m.h>

namespace TTEthernetModel {

/**
 * @brief Represents the part of a port that sends messages (TX)
 *
 */
class BaseTrafficConditioner : public cSimpleModule, public IPassiveQueue
{
    public:
        /**
         * @brief Constructor
         */
        BaseTrafficConditioner(){framesRequested = 0;}

        /**
         * Implementation of IPassiveQueue::addListener().
         */
        virtual void addListener(IPassiveQueueListener *listener);

        /**
         * Implementation of IPassiveQueue::removeListener().
         */
        virtual void removeListener(IPassiveQueueListener *listener);
    private:
        /**
         * @brief List of TTBuffers.
         *
         * The vector is ordered by action time
         */
        std::list < IPassiveQueueListener * > listeners;


    protected:
        /**
         * @brief Number of frames that were requested from lower layer
         */
        unsigned int framesRequested;
        /**
         * @brief Outgoing Channel used to calculate transmission duration.
         */
        cChannel *outChannel;
        /**
         * @brief Signal that is emitted when the queue length of best-effort messages changes.
         */
        static simsignal_t beQueueLengthSignal;


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

        virtual void enqueueMessage(cMessage *msg){}

        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
         */
        virtual void requestPacket(){};

        /**
         * @brief Returns number of requested messages.
         */
        virtual int getNumPendingRequests(){return framesRequested;}

        /**
         * @brief Returns true when there are no pending messages.
         *
         * @return true if all queues are empty.
         */
        virtual bool isEmpty(){return true;}

        /**
         * @brief Clears all queued packets and stored requests.
         */
        virtual void clear(){}
        /**
         * Returns a packet directly from the queue, bypassing the primary,
         * send-on-request mechanism. Returns NULL if the queue is empty.
         */
        virtual cMessage *pop(){return NULL;}

        virtual cMessage *front(){return NULL;}

        void notifyListeners();
};
}

#endif

