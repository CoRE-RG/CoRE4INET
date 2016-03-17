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

#ifndef CORE4INET_TTDOUBLEBUFFER_H_
#define CORE4INET_TTDOUBLEBUFFER_H_

//CoRE4INET
#include "core4inet/buffer/AS6802/RCBuffer.h"
#include "core4inet/buffer/base/QueueBuffer.h"

namespace CoRE4INET {

/**
 * @brief Rate-constrained queue buffer class.
 *
 * The Frame is stored and released immediately when the bag has expired previously.
 * If the bag has not expired yet the frame is stored. The implementation uses a
 * SchedulerTimerEvent that is registered at the TTEScheduler.
 *
 * The queue is an endless fifo queue
 *
 * @sa RCBuffer, RCQueueBuffer, CTBuffer
 *
 * @ingroup Buffer AS6802
 *
 * @author Till Steinbach
 */
class RCQueueBuffer : public virtual RCBuffer, public virtual QueueBuffer
{
    public:
        virtual ~RCQueueBuffer();
};
}
#endif
