#ifndef __INET_TTEOUTPUT_H
#define __INET_TTEOUTPUT_H

#include <omnetpp.h>
#include <csimplemodule.h>
#include <INETDefs.h>
#include <TTE4INETDefs.h>
#include <IPassiveQueue.h>
#include <EtherFrame_m.h>
#include <TTBuffer.h>
#include <PCFrame_m.h>

namespace TTEthernetModel {

/**
 * @brief Represents the part of a port that sends messages (TX)
 * @deprecated This module is deprecated and was replaced by the
 * TT_PCF_RC_BE_TrafficConditioner module.
 *
 * @see TT_PCF_RC_BE_TrafficConditioner
 *
 */
class TTEOutput : public cSimpleModule, public IPassiveQueue
{
    public:
        /**
         * @brief Constructor
         */
        TTEOutput();
        /**
         * @brief Destructor
         */
        ~TTEOutput();

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);
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
         * @brief Outgoing Channel used to calculate transmission duration.
         */
        cChannel *outChannel;
        /**
         * @brief Number of frames that were requested from lower layer
         */
        unsigned int framesRequested;

        /**
         * @brief Queue for TT-Messages. Will be only filled when there is TT shuffling
         * configured or there was an error in the configuration.
         */
        cQueue ttQueue;

        /**
         * @brief Dedicated queue for each priority of rate-constrained messages
         */
        cQueue rcQueue[NUM_RC_PRIORITIES];

        /**
         * @brief Queue for best-effort messages
         */
        cQueue beQueue;

        /**
         * @brief Queue for protocol control messages
         */
        cQueue pcfQueue;

        /**
         * @brief Vector of TTBuffers.
         *
         * The vector is ordered by action time
         */
        std::vector < TTBuffer * > ttBuffers;

        /**
         * @brief List of TTBuffers.
         *
         * The vector is ordered by action time
         */
        std::list < IPassiveQueueListener * > listeners;

        /**
         * @brief Current position of the next Buffer (action time) in the ttBuffers vector
         */
        size_t ttBuffersPos;
    protected:
        /**
         * @brief Signal that is emitted when the queue length of time-triggered messages changes.
         */
        static simsignal_t ttQueueLengthSignal;

        /**
         * @brief Signal that is emitted when the queue length of best-effort messages changes.
         */
        static simsignal_t beQueueLengthSignal;
        /**
         * @brief Signal that is emitted when the queue length of protocol control messages changes.
         */
        static simsignal_t pcfQueueLengthSignal;
    private:
        /**
         * @brief Helper function to check whether a Messages is allowed to be transmitted.
         *
         * The function checks whether a message fits in the gap until the next TT-message
         * should be transmitted. It uses the message length to calculate the transmission
         * duration.
         *
         * @param message The message that should be transmitted
         * @returns true if transmission is allowed else false
         */
        virtual bool isTransmissionAllowed(EtherFrame *message);

        /**
         * @brief Sets the transparent clock field in a protocol control frame
         * according to the actual sending time
         *
         * @param pcf the protocol control frame
         */
        virtual void setTransparentClock(PCFrame *pcf);

        /**
         * @brief Registers a time-triggered buffer that feeds the module.
         */
        virtual void registerTTBuffer(TTBuffer *buffer);

        /**
         * @brief check whether a time-triggered buffer is registered.
         *
         * @param ttBuffer the ttBuffer to check for
         * @returns true when registered, else false
         */
        virtual bool isTTBufferRegistered(TTBuffer *ttBuffer);

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

        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
         */
        virtual void requestPacket();

        /**
         * @brief Returns number of requested messages.
         */
        virtual int getNumPendingRequests();

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

        void notifyListeners();
};
}

#endif

