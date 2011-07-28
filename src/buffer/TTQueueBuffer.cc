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

#include "TTQueueBuffer.h"

namespace TTEthernetModel {

Define_Module( TTQueueBuffer);

simsignal_t TTQueueBuffer::queueLengthSignal = SIMSIGNAL_NULL;

TTQueueBuffer::TTQueueBuffer()
{
}

TTQueueBuffer::~TTQueueBuffer()
{
}
void TTQueueBuffer::initialize()
{
    TTBuffer::initialize();
    ev << "Initialize TTQueueBuffer" << endl;
    setIsEmpty(frames.length() == 0);
    initializeStatistics();
}

void TTQueueBuffer::initializeStatistics()
{
    queueLengthSignal = registerSignal("queueLength");
}

void TTQueueBuffer::enqueue(EtherFrame *newFrame)
{
    frames.insert(newFrame);
    setIsEmpty(frames.length() == 0);
    emit(queueLengthSignal, frames.length());
}

EtherFrame * TTQueueBuffer::dequeue()
{
    if (frames.length() > 0)
    {
        setIsEmpty(frames.length() - 1 == 0);
        emit(queueLengthSignal, frames.length() - 1);
        return (EtherFrame*) frames.pop();
    }
    else
        return NULL;
}

} //namespace
