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

#ifndef __CORE4INET_BUFFER_H_
#define __CORE4INET_BUFFER_H_

//Std
#include <list>
//OMNeT++
#include "csimplemodule.h"
//INET Auto-generated Messages
#include "EtherFrame_m.h"

namespace CoRE4INET {

class ApplicationBase;
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
 *
 * @author Till Steinbach
 */
class Buffer : public virtual cSimpleModule
{
    public:
        /**
         * @brief Constructor
         */
        Buffer();
        /**
         * @brief Destructor
         */
        virtual ~Buffer();

    protected:
        /**
         * Stores the Gates to that the messages are delivered
         */
        std::list<cGate*> destinationGates;

        /**
         * Caches the maximum message size
         */
        size_t maxMessageSize;

    protected:
        /**
         * @brief Initializes the module
         *
         * @param stage The stages. Module initializes when stage==0
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return Always returns 1
         */
        virtual int numInitStages() const override;

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
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

        /**
         * @brief Is called to store an EtherFrame in the buffer.
         *
         * This method must be implemented according to the buffer strategy.
         *
         * @param newFrame A pointer to the new EtherFrame to be saved in the buffer
         */
        virtual void enqueue(EtherFrame *newFrame);

        /**
         * @brief Is called to get an EtherFrame from the buffer.
         *
         * This method must be implemented according to the buffer strategy.
         *
         * @return A pointer to the next EtherFrame from the buffer. Returns
         * nullptr if there is no EtherFrame in the buffer
         */
        virtual EtherFrame* dequeue();

        /**
         * @brief Emits a statistics signal that a frame was sent from the buffer
         *
         * @param frame the frame that was sent
         */
        void recordPacketSent(EtherFrame *frame);

        /**
         * @brief Emits a statistics signal that a frame was received in the buffer
         *
         * @param frame the frame that was received
         */
        void recordPacketReceived(EtherFrame *frame);

    public:
        /**
         * @brief Wrapper function arround dequeue().
         *
         * @return A pointer to the next EtherFrame from the buffer. Returns
         * nullptr if there is no EtherFrame in the buffer
         *
         * @sa dequeue();
         */
        EtherFrame* getFrame();

        /**
         * @brief Wrapper function arround enqueue().
         *
         * @param frame The EtherFrame to put in the buffer.
         *
         * @sa enqueue();
         */
        void putFrame(EtherFrame* frame);

        /**
         * @brief Calculates the bandwidth this module requires for transmission.
         *
         * @return Bandwidth in bps, or -1 is unknown.
         *
         */
        virtual long getRequiredBandwidth();

        /**
         * @brief Returns the used size of the buffer
         *
         * @return number of messages in the buffer
         *
         */
        virtual size_t size() const = 0;

        /**
         * @brief Resets the buffer, deletes all messages
         *
         *
         */
        virtual void clear() = 0;

        /**
         * @brief Returns the maximum message size allowed in the buffer
         *
         * @return Maximum message size allowed in the buffer
         */
        virtual size_t getMaxMessageSize();

    protected:
        /**
         * Signal that is emitted every time a frame was sent.
         */
        static simsignal_t txPkSignal;
        /**
         * Signal that is emitted every time a frame was received.
         */
        static simsignal_t rxPkSignal;

};
}

#endif
