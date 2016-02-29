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

#include "core4inet/buffer/base/DoubleBuffer.h"

namespace CoRE4INET {

DoubleBuffer::DoubleBuffer()
{
    frame = nullptr;
}

DoubleBuffer::~DoubleBuffer()
{
    delete frame;
}

void DoubleBuffer::enqueue(inet::EtherFrame *newFrame)
{
    if (frame != nullptr)
        delete frame;
    else
    {
        if (getEnvir()->isGUI())
        {
            //Update displaystring
            if (newFrame != nullptr)
            {
                getDisplayString().setTagArg("i", 0, "buffer/full");
            }
        }
    }
    frame = newFrame;
}

inet::EtherFrame * DoubleBuffer::dequeue()
{
    if (frame)
        return frame->dup();
    else
        return nullptr;
}

size_t DoubleBuffer::size() const
{
    return frame ? 1 : 0;
}

void DoubleBuffer::clear()
{
    delete frame;
    frame = nullptr;
    if (getEnvir()->isGUI())
    {
        //Update displaystring
        getDisplayString().setTagArg("i", 0, "buffer/empty");
    }
}

}
