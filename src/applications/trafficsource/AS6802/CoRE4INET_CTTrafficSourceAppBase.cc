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

#include "CoRE4INET_CTTrafficSourceAppBase.h"

//CoRE4INET
#include "CoRE4INET_AS6802Defs.h"
#include "CoRE4INET_CTFrame.h"
#include "CoRE4INET_TTBuffer.h"
#include "CoRE4INET_RCBuffer.h"
#include "CoRE4INET_Incoming.h"
#include "CoRE4INET_ConfigFunctions.h"
//Auto-generated Messages
#include "TTFrame_m.h"
#include "RCFrame_m.h"

namespace CoRE4INET {

Define_Module(CTTrafficSourceAppBase);

CTTrafficSourceAppBase::CTTrafficSourceAppBase()
{
    this->ct_id = -1;
}

void CTTrafficSourceAppBase::initialize()
{
    TrafficSourceAppBase::initialize();
    CTApplicationBase::initialize();
}

void CTTrafficSourceAppBase::sendMessage()
{

    std::list<CTBuffer*> buffer;
    if (this->ct_id >= 0)
    {
        buffer = ctbuffers[static_cast<uint16_t>(this->ct_id)];
    }
    else
    {
        for (std::unordered_map<uint16_t, std::list<CTBuffer*> >::iterator bufmap = ctbuffers.begin();
                bufmap != ctbuffers.end(); ++bufmap)
        {
            buffer.merge(bufmap->second);
        }
    }
    if (buffer.empty())
    {
        ev.printf("No buffer with such CT \n");
        bubble("No buffer with such CT");
        getDisplayString().setTagArg("i2", 0, "status/excl3");
        getDisplayString().setTagArg("tt", 0, "WARNING: No buffer with such CT");
        getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
        getParentModule()->getDisplayString().setTagArg("tt", 0, "No buffer with such CT");
    }
    else
    {
        for (std::list<CTBuffer*>::const_iterator buf = buffer.begin(); buf != buffer.end(); ++buf)
        {
            CTFrame *frame;
            if (dynamic_cast<TTBuffer*>(*buf))
            {
                frame = new TTFrame("");
            }
            else if (dynamic_cast<RCBuffer*>(*buf))
            {
                frame = new RCFrame("");
            }
            else
            {
                continue;
            }
            frame->setTimestamp();
            cPacket *payload_packet = new cPacket;
            payload_packet->setTimestamp();
            payload_packet->setByteLength(static_cast<int64_t>(getPayloadBytes()));
            frame->encapsulate(payload_packet);
            //Padding
            if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
            {
                frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
            }
            if (this->ct_id > 0)
            {
                frame->setCtID(static_cast<uint16_t>(this->ct_id));
            }
            //TODO Minor: Better name for Frame
            frame->setName((*buf)->getName());
            if ((*buf)->gate("in")->getPathStartGate())
            {
                Incoming* in = dynamic_cast<Incoming *>((*buf)->gate("in")->getPathStartGate()->getOwner());
                if (in)
                {
                    sendDirect(frame, in->gate("in"));
                }
                else
                {
                    throw cRuntimeError(
                            "You can only connect an Incoming module to a Buffer (Buffer:%s, Attached Module:%s)",
                            (*buf)->getFullPath().c_str(),
                            (*buf)->gate("in")->getPathStartGate()->getOwner()->getFullPath().c_str());
                }
            }
            else //It is ok to directly send a frame to a buffer if no incoming is attached!
            {
                sendDirect(frame, (*buf)->gate("in"));
            }
        }
    }

}

void CTTrafficSourceAppBase::handleParameterChange(const char* parname)
{
    TrafficSourceAppBase::handleParameterChange(parname);
    CTApplicationBase::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "ct_id"))
    {
        this->ct_id = static_cast<int>(parameterLongCheckRange(par("ct_id"), -1, MAX_CT_ID));
    }
}

} //namespace
