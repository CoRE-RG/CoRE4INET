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

#include "FrameSizeMeter.h"

//INET
#include "inet/linklayer/ethernet/Ethernet.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"
//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(FrameSizeMeter);

void FrameSizeMeter::initialize()
{
    IEEE8021QciMeter::initialize();
    this->handleParameterChange(nullptr);
}

void FrameSizeMeter::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        cPacket *packet = IEEE8021QciMeter::checkAndRemoveCtrlInfo(msg);
        if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(packet))
        {
            this->numFramesReceived++;
            this->numBytesReceived += frame->getByteLength();
            this->emit(frameReceivedSignal, static_cast<long>(frame->getByteLength()));
            if (frame->getByteLength() < this->minFrameSize || frame->getByteLength() > this->maxFrameSize)
            {
                IEEE8021QciMeter::dropMessage(frame);
            }
            else
            {
                IEEE8021QciMeter::sendMessage(frame);
            }
        }
        else
        {
            throw cRuntimeError("Packet type is not EtherFrame");
        }
    }
}

void FrameSizeMeter::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "minFrameSize"))
    {
        this->minFrameSize = parameterULongCheckRange(par("minFrameSize"), MIN_ETHERNET_FRAME_BYTES, MAX_ETHERNET_FRAME_BYTES);
    }
    if (!parname || !strcmp(parname, "maxFrameSize"))
    {
        this->maxFrameSize = parameterULongCheckRange(par("maxFrameSize"), MIN_ETHERNET_FRAME_BYTES, MAX_ETHERNET_FRAME_BYTES);
    }
}

} //namespace
