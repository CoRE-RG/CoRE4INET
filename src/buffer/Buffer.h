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

#ifndef __TTETHERNETMODELV2_BUFFER_H_
#define __TTETHERNETMODELV2_BUFFER_H_

#include <omnetpp.h>
#include <EtherFrame_m.h>
#include <list>

namespace TTEthernetModel {

class TTEApplicationBase;
class TTEAPIPriv;
class Callback;

/**
 * @brief Base class for all buffer classes.
 *
 * Buffer, although packed with buffer-related functionality, does not do
 * anything useful by itself: one has to subclass from it and redefine one
 * or more virtual member functions to make it do useful work. These
 * functions are:
 *
 *    - void enqueue(EtherFrame *newFrame)
 *    - EtherFrame* dequeue()
 *
 * enqueue(EtherFrame *newFrame) is called to queue a message in the buffer.
 * It must be implemented according to the correct buffer behaviour.
 *
 * dequeue() is called to get a frame from the buffer.
 *
 * @ingroup Buffer
 */
class Buffer : public cSimpleModule
{
    public:
        /**
         * @brief Destructor
         */
        ~Buffer();
    protected:
        /**
         * Stores the Gates to that the messages are delivered
         */
        std::list<cGate*> destinationGates;
        /**
         * Stores the callbacks that are executed when a frame is added to the buffer
         */
        std::map<TTEApplicationBase*, Callback*> receiveCallbacks;
        /**
         * Stores the callbacks that are executed when a frame is removed from the buffer
         */
        std::map<TTEApplicationBase*, Callback*> transmitCallbacks;

        /**
         * @brief caches ct_mask parameter
         */
        unsigned long ctMask;
        /**
         * @brief caches ct_marker parameter
         */
        unsigned long ctMarker;
        /**
         * @brief caches ct_id parameter
         */
        unsigned long ctId;

    private:
        /**
         * Initializes the statistics for the module
         */
        void initializeStatistics();

    protected:
        /**
         * Initializes the module
         */
        void initialize();

        /**
         * @brief Is called when a new Frame is received in the buffer.
         *
         * When a frame is received on the in-Gate it is processed. If the destination
         * address is unspecified it is set according to the ct marker of the buffer.
         * Afterwards it is enqueued using the buffer specific enqueue(EtherFrame *newFrame)
         * method. In the end all registered receive callbacks are executed.
         *
         * @param msg The incoming message
         */
        void handleMessage(cMessage *msg);

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);

        /**
         * @brief Is called to store an EtherFrame in the buffer.
         *
         * This method must be implemented according to the buffer strategy.
         *
         * @param newFrame a pointer to the new EtherFrame to be saved in the buffer
         */
        virtual void enqueue(EtherFrame *newFrame);

        /**
         * @brief Is called to get an EtherFrame from the buffer.
         *
         * This method must be implemented according to the buffer strategy.
         *
         * @return a pointer to the next EtherFrame from the buffer. Returns
         * null if there is no EtherFrame in the buffer
         */
        virtual EtherFrame* dequeue();

        /**
         * @brief Emits a statistics signal that a frame was sent from the buffer
         */
        void recordPacketSent();

        /**
         * @brief Sets the status of the Buffer to empty or non-empty.
         *
         * This method changes the GUI according to the buffer status.
         */
        void setIsEmpty(bool empty);

    public:
        /**
         * @brief Wrapper function arround dequeue().
         *
         * @return a pointer to the next EtherFrame from the buffer. Returns
         * null if there is no EtherFrame in the buffer
         *
         * @sa dequeue();
         */
        EtherFrame* getFrame();

        /**
         * @brief Adds a destination gate to the buffer.
         *
         * The destination gate must be loosely coupled
         *
         * @param destinationGate pointer to the destination gate to be added.
         */
        void addDestinationGate(cGate *destinationGate);

        /**
         * @brief Removes a destination gate to the buffer.
         *
         * The destination gate should be previously added.
         *
         * @param destinationGate pointer to the destination gate to be removed.
         */
        void removeDestinationGate(cGate *destinationGate);

        /**
         * @brief Adds a receive callback for an application to the buffer.
         *
         * The callback is registered for a specific application. Each application is
         * allowed to only register one receive callback per buffer. Further calls
         * overwrite the registered callback.
         *
         * @param cb the receive callback to be added.
         * @param the corresponding application that registers the callback
         */
        void addReceiveCallback(Callback *cb, TTEApplicationBase *application);

        /**
         * @brief Returns the currently registered receive callback for an application.
         *
         * @param the corresponding application that registered callbacks
         * @return The callback that is currently registered. Null if there is no
         * receive callback registered
         */
        Callback* getReceiveCallback(TTEApplicationBase *application);

        /**
         * @brief Adds a transmit callback for an application to the buffer.
         *
         * The callback is registered for a specific application. Each application is
         * allowed to only register one transmit callback per buffer. Further calls
         * overwrite the registered callback.
         *
         * @param cb the transmit callback to be added.
         * @param the corresponding application that registers the callback
         */
        void addTransmitCallback(Callback *cb, TTEApplicationBase *application);

        /**
         * @brief Returns the currently registered transmit callback for an application.
         *
         * @param the corresponding application that registered callbacks
         * @return The callback that is currently registered. Null if there is no
         * transmit callback registered
         */
        Callback* getTransmitCallback(TTEApplicationBase *application);

    protected:
        /**
         * Signal that is emitted every time a frame was sent.
         */
        static simsignal_t txPkSignal;

        /**
         * Signal that contains the latency until the frame enters the buffer.
         */
        static simsignal_t latencySignal;

};
}

#endif
