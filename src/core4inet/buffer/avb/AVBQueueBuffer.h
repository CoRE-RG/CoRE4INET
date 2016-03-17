//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CORE4INET_AVBQUEUEBUFFER_H_
#define CORE4INET_AVBQUEUEBUFFER_H_

//CoRE4INET
#include "core4inet/buffer/avb/AVBBuffer.h"
#include "core4inet/buffer/base/QueueBuffer.h"

namespace CoRE4INET {

class AVBQueueBuffer : public virtual AVBBuffer, public virtual QueueBuffer
{
    public:
        virtual ~AVBQueueBuffer();
};

} /* namespace CoRE4INET */
#endif /* CORE4INET_AVBQUEUEBUFFER_H_ */
