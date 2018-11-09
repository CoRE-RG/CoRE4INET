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

#ifndef CORE4INET_DOUBLEBUFFER_H_
#define CORE4INET_DOUBLEBUFFER_H_

//CoRE4INET
#include "core4inet/buffer/base/Buffer.h"
//INET
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Base class for a double buffer class.
 *
 * Use the implementations BGDoubleBuffer, TTDoubleBuffer, RCDoubleBuffer.
 *
 * @sa BGDoubleBuffer, TTDoubleBuffer, RCDoubleBuffer, Buffer
 *
 * @ingroup Buffer
 *
 * @author Till Steinbach
 */
class DoubleBuffer : public virtual Buffer
{
    public:
        /**
         * @brief Constructor
         */
        DoubleBuffer();
        /**
         * @brief Destructor
         */
        virtual ~DoubleBuffer() override;

    private:
        /**
         * The inet::EtherFrame pointer is stored here
         */
        inet::EtherFrame *frame;

    protected:
        /**
         * @brief Stores a new frame.
         *
         * The incoming inet::EtherFrame pointer is stored. A previously stored frame is deleted
         * @param newFrame the new inet::EtherFrame to store.
         */
        virtual void enqueue(inet::EtherFrame *newFrame) override;

        /**
         * @brief Returns the frame that is stored in the buffer
         *
         * The stored frame is copied and the copy is being returned. If there is no EtherFrame
         * stored nullptr is returned.
         *
         * @return Pointer to the copied frame or nullptr if no frame is stored.
         */
        virtual inet::EtherFrame* dequeue() override;

        /**
         * @brief Returns the used size of the buffer
         *
         * @return number of messages in the buffer
         *
         */
        virtual size_t size() const override;

        /**
         * @brief Resets the buffer, deletes all messages
         *
         *
         */
        virtual void clear() override;
};
}
#endif
