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

#include <core4inet/linklayer/shaper/IEEE8021Qbv/queueing/IEEE8021QbvQueue.h>

namespace CoRE4INET {

Define_Module(IEEE8021QbvQueue);

void IEEE8021QbvQueue::initialize(int stage)
{
    BGQueueBuffer::initialize(stage);
    if (stage == 0)
    {
        this->ts = dynamic_cast<IEEE8021QbvSelection*>(this->getParentModule()->getSubmodule("transmissionSelection"));
    }
}

void IEEE8021QbvQueue::handleMessage(cMessage *msg)
{
    BGQueueBuffer::handleMessage(msg);
    ts->reportChange();
}

inet::EtherFrame* IEEE8021QbvQueue::dequeue()
{
    Enter_Method("dequeue()");
    inet::EtherFrame* frame = BGQueueBuffer::dequeue();
    this->sendDirect(frame, ts->gate("in"));
    return nullptr;
}

size_t IEEE8021QbvQueue::size() const
{
    Enter_Method("size()");
    return BGQueueBuffer::size();
}

} //namespace
