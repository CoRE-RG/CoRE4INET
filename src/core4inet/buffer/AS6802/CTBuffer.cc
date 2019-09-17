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

#include "core4inet/buffer/AS6802/CTBuffer.h"

//CoRE4INET
#include "core4inet/linklayer/ethernet/AS6802/CTFrame.h"
#include "core4inet/base/AS6802/AS6802Defs.h"
#include "core4inet/utilities/ConfigFunctions.h"

using namespace CoRE4INET;

//Define_Module(CTBuffer);

CTBuffer::CTBuffer()
{
    this->parametersInitialized = false;
    this->ctMask = 0;
    this->ctMarker = 0;
    this->ctId = 0;
    this->priority = 0;
}

CTBuffer::~CTBuffer()
{
}

void CTBuffer::putFrame(inet::EtherFrame* frame)
{
    if (frame && priority >= 0)
    {
        frame->setSchedulingPriority(priority);
    }
    enqueue(frame);
}

void CTBuffer::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
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
    Buffer::handleParameterChange(parname);

    if (!parname && !parametersInitialized)
    {
        parametersInitialized = true;
    }

    if (!parname || !strcmp(parname, "ct_id"))
    {
        this->ctId = static_cast<uint16_t>(parameterULongCheckRange(par("ct_id"), 0, MAX_CT_ID));
    }
    if (!parname || !strcmp(parname, "ct_mask"))
    {
        this->ctMask = par("ct_mask");
    }
    if (!parname || !strcmp(parname, "ct_marker"))
    {
        this->ctMarker = par("ct_marker");
    }
    if (!parname || !strcmp(parname, "priority"))
    {
        this->priority = static_cast<short>(parameterLongCheckRange(par("priority"), -1, MAX_PRIORITY));
    }
}

uint16_t CTBuffer::getCTID()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->ctId;
}
