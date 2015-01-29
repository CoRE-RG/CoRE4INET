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

#ifndef __CORE4INET_BGBUFFER_H_
#define __CORE4INET_BGBUFFER_H_

//CoRE4INET
#include "CoRE4INET_Buffer.h"

namespace CoRE4INET {

/**
 * @brief Base class for a background (best-effort) buffer class.
 *
 * Use the implementation BGQueueBuffer.
 *
 * @sa BGQueueBuffer, Buffer
 *
 * @ingroup Buffer
 *
 * @author Till Steinbach
 */
class BGBuffer : public virtual Buffer
{
    protected:
        /**
         * Initializes the module
         */
        virtual void initialize(int stage) override;
        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return returns 1 or if higher the number of stages the Buffer module requires
         */
        virtual int numInitStages() const override;

        /**
         * @brief Is called when a new Frame is received in the buffer.
         *
         * Extends the handleMessage(cMessage *msg) method in Buffer class.
         * An incoming frame is directly dequeued. No buffering!
         *
         * @param msg The incoming message
         */
        virtual void handleMessage(cMessage *msg) override;
};

} //namespace

#endif
