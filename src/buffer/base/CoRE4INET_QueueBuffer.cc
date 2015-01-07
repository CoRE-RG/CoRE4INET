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

#include "CoRE4INET_QueueBuffer.h"

namespace CoRE4INET {

simsignal_t QueueBuffer::queueLengthSignal = registerSignal("queueLength");
simsignal_t QueueBuffer::droppedSignal = registerSignal("dropped");

QueueBuffer::QueueBuffer()
{
    initializeStatistics();
}

QueueBuffer::~QueueBuffer()
{
    frames.clear();
}

void QueueBuffer::initializeStatistics()
{
    frames.setName("frames");
}

void QueueBuffer::enqueue(EtherFrame *newFrame)
{
    int max_size = static_cast<int>(par("size").longValue());
    if (max_size >= 0 && frames.length() >= max_size)
    {
        emit(droppedSignal, newFrame);
        if (ev.isGUI())
        {
            bubble("buffer overflow - dropping frame");
            getDisplayString().setTagArg("i2", 0, "status/excl3");
            getDisplayString().setTagArg("tt", 0, "WARNING: buffer overflow");
            getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
            getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: buffer overflow");
        }
        if (par("drop_new").boolValue())
        {
            delete newFrame;
            return;
        }
        else
        {
            delete frames.pop();
        }
    }
    frames.insert(newFrame);
    setFilled(static_cast<size_t>(frames.length()));
    emit(queueLengthSignal, static_cast<unsigned long>(frames.length()));
}

EtherFrame * QueueBuffer::dequeue()
{
    if (frames.length() > 0)
    {
        setFilled(static_cast<size_t>(frames.length() - 1));
        emit(queueLengthSignal, static_cast<unsigned long>(frames.length() - 1));
        return static_cast<EtherFrame*>(frames.pop());
    }
    else
        return nullptr;
}

void QueueBuffer::setFilled(size_t fillLevel)
{
    if (ev.isGUI())
    {
        switch (fillLevel)
        {
            case 0:
                getDisplayString().setTagArg("i", 0, "buffer/empty");
                break;
            case 1:
                getDisplayString().setTagArg("i", 0, "buffer/buffer1");
                break;
            case 2:
                getDisplayString().setTagArg("i", 0, "buffer/buffer2");
                break;
            case 3:
                getDisplayString().setTagArg("i", 0, "buffer/buffer3");
                break;
            default:
                getDisplayString().setTagArg("i", 0, "buffer/buffer3plus");
        }
    }
}

size_t QueueBuffer::size() const
{
    return static_cast<size_t>(frames.length());
}

void QueueBuffer::clear(){
    frames.clear();
    setFilled(0);
}

} //namespace
