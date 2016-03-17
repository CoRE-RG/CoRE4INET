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

#ifndef CORE4INET_BGQUEUEBUFFER_H_
#define CORE4INET_BGQUEUEBUFFER_H_

//CoRE4INET
#include "core4inet/buffer/base/BGBuffer.h"
#include "core4inet/buffer/base/QueueBuffer.h"

namespace CoRE4INET {

/**
 * @brief Class for a queuing background (best-effort) buffer class.
 *
 * @sa BGBuffer, QueueBuffer, Buffer
 *
 * @ingroup Buffer
 *
 * @author Till Steinbach
 */
class BGQueueBuffer : public virtual BGBuffer, public virtual QueueBuffer
{
    public:
        virtual ~BGQueueBuffer();
};
}
#endif
