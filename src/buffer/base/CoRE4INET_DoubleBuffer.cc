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

#include "CoRE4INET_DoubleBuffer.h"

namespace CoRE4INET {

DoubleBuffer::DoubleBuffer()
{
    frame = NULL;
}

DoubleBuffer::~DoubleBuffer()
{
    delete frame;
}

void DoubleBuffer::enqueue(EtherFrame *newFrame)
{
    if (frame != NULL)
        delete frame;
    else
    {
        if (ev.isGUI())
        {
            //Update displaystring
            if (newFrame != NULL)
            {
                getDisplayString().setTagArg("i", 0, "buffer/full");
            }
        }
    }
    frame = newFrame;
}

EtherFrame * DoubleBuffer::dequeue()
{
    if (frame)
        return frame->dup();
    else
        return NULL;
}

unsigned int DoubleBuffer::size()
{
    return frame ? 1 : 0;
}

void DoubleBuffer::clear()
{
    delete frame;
    frame = NULL;
    if (ev.isGUI())
    {
        //Update displaystring
        getDisplayString().setTagArg("i", 0, "buffer/empty");
    }
}

}
