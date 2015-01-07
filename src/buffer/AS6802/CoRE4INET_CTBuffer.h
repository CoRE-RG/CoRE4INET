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

#ifndef __CORE4INET_CTBUFFER_H_
#define __CORE4INET_CTBUFFER_H_

//CoRE4INET
#include "CoRE4INET_Buffer.h"
//INET
#include "EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Base class for all critical traffic buffer classes.
 *
 * CTBuffer, although packed with buffer-related functionality, does not do
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
 * @ingroup Buffer AS6802
 *
 * @author Till Steinbach
 */
class CTBuffer : public virtual Buffer
{
    private:
        /**
         * @brief True if parameters were initialized
         */
        bool parametersInitialized;
    public:
        /**
         * @brief Consstructor
         */
        CTBuffer();

        /**
         * @brief Destructor
         */
        ~CTBuffer();

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);

    protected:
        /**
         * @brief caches ct_mask parameter
         */
        uint32_t ctMask;
        /**
         * @brief caches ct_marker parameter
         */
        uint32_t ctMarker;
        /**
         * @brief caches ct_id parameter
         */
        uint16_t ctId;
        /**
         * @brief caches priority parameter
         */
        short priority;

    protected:
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

    public:
        /**
         * @brief Wrapper function arround enqueue().
         *
         * @param frame the EtherFrame to put in the buffer.
         *
         * @sa enqueue();
         */
        void putFrame(EtherFrame* frame);

        uint16_t getCTID();

};
}

#endif
