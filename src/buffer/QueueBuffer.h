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

#ifndef __TTETHERNETMODELV2_QUEUEBUFFER_H_
#define __TTETHERNETMODELV2_QUEUEBUFFER_H_

#include <omnetpp.h>
#include <TTBuffer.h>

namespace TTEthernetModel {

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
        ~QueueBuffer();

    private:
        /**
         * @brief Queue for the EtherFrames in the Buffer.
         */
        cQueue frames;

    private:
        /**
         * Initializes the statistics for the Queue
         */
        virtual void initializeStatistics();
    protected:
        /**
         * @brief Inserts EtherFrame in the Queue and emits the queue length.
         *
         * @param newFrame a pointer to the EtherFrame to insert in the queue.
         */
        virtual void enqueue(EtherFrame *newFrame);

        /**
         * @brief Removes and returns an EtherFrame from the Queue and emits the queue length.
         *
         * @return Aa pointer to the EtherFrame removed from the queue.
         */
        virtual EtherFrame* dequeue();

    protected:
        /**
         * @brief Signal containing the queue length, that is emitted every time a frame
         * was inserted or removed.
         */
        static simsignal_t queueLengthSignal;
};

} //namespace

#endif
