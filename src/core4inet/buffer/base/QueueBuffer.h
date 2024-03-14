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

#ifndef CORE4INET_QUEUEBUFFER_H_
#define CORE4INET_QUEUEBUFFER_H_

//CoRE4INET
#include "core4inet/buffer/base/Buffer.h"
//INET
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Base class for a queuing buffer class.
 *
 * The queue is an endless fifo queue.
 *
 * Use the implementations BGQueueBuffer, TTQueueBuffer, RCQueueBuffer.
 *
 * @sa BGQueueBuffer, TTQueueBuffer, RCQueueBuffer, Buffer
 *
 * @ingroup Buffer
 *
 * @author Till Steinbach
 */
class QueueBuffer : public virtual Buffer
{
    public:
        /**
         * @brief Constructor for the class.
         *
         * executes initializeStatistics()
         *
         * @sa initializeStatistics()
         */
        QueueBuffer();

        /**
         * @brief Destructor for the class.
         */
        virtual ~QueueBuffer() override = 0;

    private:
        /**
         * @brief Queue for the inet::EtherFrames in the Buffer.
         */
        cQueue frames;

        /**
         * @brief Caches the queuesize sum of all bytes of frames
         * increased with incoming frame, decreased with outgoing frame
         */
        size_t queueSize;
    private:
        /**
         * Initializes the statistics for the Queue
         */
        virtual void initializeStatistics();

        /**
         * @brief Sets the status of the Buffer to the given fill level.
         *
         * This method changes the GUI according to the buffers fill level .
         *
         * @param fillLevel the level the buffer is filled in number of frames
         */
        void setFilled(size_t fillLevel);
    protected:
        /**
         * @brief Inserts inet::EtherFrame in the Queue and emits the queue length.
         *
         * @param newFrame a pointer to the inet::EtherFrame to insert in the queue.
         */
        virtual void enqueue(inet::EtherFrame *newFrame) override;

        /**
         * @brief Removes and returns an inet::EtherFrame from the Queue and emits the queue length.
         *
         * @return Aa pointer to the inet::EtherFrame removed from the queue.
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

    protected:
        /**
         * @brief Signal containing the queue length, that is emitted every time a frame
         * was inserted or removed.
         */
        static simsignal_t queueLengthSignal;
        /**
         * @brief Signal containing the queue size in byte, that is emitted every time a frame
         * was inserted or removed.
         */
        static simsignal_t queueSizeSignal;
        /**
         * @brief Signal that is emitted when a frame is dropped.
         *
         * Frames may be dropped when frame arrives at a full buffer.
         */
        static simsignal_t droppedSignal;

        /**
         * @brief Signal containing the time spent in the queue, that is emitted when a frame is dequeued.
         */
        static simsignal_t queueTimeSignal;
};

} //namespace

#endif
