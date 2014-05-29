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

#include "CoRE4INET_CTBuffer.h"

//CoRE4INET
#include "CoRE4INET_CTFrame.h"

using namespace CoRE4INET;

//Define_Module(CTBuffer);

CTBuffer::~CTBuffer()
{
}

void CTBuffer::putFrame(EtherFrame* frame)
{
    short priority = (short) par("priority").longValue();
    if (frame && priority >= 0)
    {
        frame->setSchedulingPriority(priority);
    }
    enqueue(frame);
}

void CTBuffer::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        //Try to correct destination mac
        if (CTFrame *ctframe = dynamic_cast<CTFrame *>(msg))
        {
            if (ctframe->getDest().isUnspecified())
            {
                ctframe->setCtID(ctId);
                ctframe->setCtMarker(ctMarker & ctMask);
            }
            else if (ctframe->getCtMarker() == 0)
            {
                ctframe->setCtMarker(ctMarker & ctMask);
            }
        }
        Buffer::handleMessage(msg);
    }
}

void CTBuffer::handleParameterChange(const char* parname)
{
    ctMask = (uint32_t) par("ct_mask").longValue();
    ctMarker = (uint32_t) par("ct_marker").longValue();
    ctId = (uint16_t) par("ct_id").longValue();

    Buffer::handleParameterChange(parname);
}
