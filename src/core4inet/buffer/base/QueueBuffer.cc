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

#include "core4inet/buffer/base/QueueBuffer.h"

namespace CoRE4INET {

simsignal_t QueueBuffer::queueLengthSignal = registerSignal("length");
simsignal_t QueueBuffer::queueSizeSignal = registerSignal("size");
simsignal_t QueueBuffer::droppedSignal = registerSignal("dropped");

QueueBuffer::QueueBuffer()
{
    initializeStatistics();
    queueSize = 0;
    WATCH(queueSize);
}

QueueBuffer::~QueueBuffer()
{
    frames.clear();
}

void QueueBuffer::initializeStatistics()
{
    frames.setName("frames");
}

void QueueBuffer::enqueue(inet::EtherFrame *newFrame)
{
    int max_size = par("size");
    if (max_size >= 0 && frames.getLength() >= max_size)
    {
        emit(droppedSignal, newFrame);
        if (getEnvir()->isGUI())
        {
            bubble("buffer overflow - dropping frame");
            getDisplayString().setTagArg("i2", 0, "status/excl3");
            getDisplayString().setTagArg("tt", 0, "WARNING: buffer overflow");
            getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
            getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: buffer overflow");
        }
        if (par("dropNew").boolValue())
        {
            delete newFrame;
            return;
        }
        else
        {
            inet::EtherFrame *popFrame = static_cast<inet::EtherFrame*>(frames.pop());
            queueSize-=static_cast<size_t>(popFrame->getByteLength());
            delete popFrame;
        }
    }
    frames.insert(newFrame);
    setFilled(static_cast<size_t>(frames.getLength()));
    emit(queueLengthSignal, static_cast<unsigned long>(frames.getLength()));
    queueSize+=static_cast<size_t>(newFrame->getByteLength());
    emit(queueSizeSignal, static_cast<unsigned long>(queueSize));
}

inet::EtherFrame * QueueBuffer::dequeue()
{
    if (frames.getLength() > 0)
    {
        setFilled(static_cast<size_t>(frames.getLength() - 1));
        emit(queueLengthSignal, static_cast<unsigned long>(frames.getLength() - 1));

        inet::EtherFrame* dequeueFrame = static_cast<inet::EtherFrame*>(frames.pop());

        ASSERT2(queueSize>=static_cast<size_t>(dequeueFrame->getByteLength()),"queueSize would become negative");
        queueSize-=static_cast<size_t>(dequeueFrame->getByteLength());
        emit(queueSizeSignal, static_cast<unsigned long>(queueSize));
        return dequeueFrame;
    }
    else
        return nullptr;
}

void QueueBuffer::setFilled(size_t fillLevel)
{
    if (getEnvir()->isGUI())
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
    return static_cast<size_t>(frames.getLength());
}

void QueueBuffer::clear(){
    frames.clear();
    setFilled(0);
}

} //namespace
