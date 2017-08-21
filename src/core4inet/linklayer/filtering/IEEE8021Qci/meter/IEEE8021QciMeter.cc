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

#include "core4inet/linklayer/filtering/IEEE8021Qci/meter/IEEE8021QciMeter.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciMeter);

simsignal_t IEEE8021QciMeter::framePassedSignal = registerSignal("framePassed");

void IEEE8021QciMeter::initialize()
{
    streamOutput = dynamic_cast<IEEE8021QciOutput*>(getParentModule()->getSubmodule("streamOutput"));
    if (!streamOutput)
    {
        throw cRuntimeError("Cannot find stream output module");
    }
    WATCH(this->numFramesReceived);
    WATCH(this->numFramesSent);
    WATCH(this->numBytesReceived);
    WATCH(this->numBytesSent);
}

void IEEE8021QciMeter::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        this->numFramesSent++;
        if (IEEE8021QciCtrl *ctrl = dynamic_cast<IEEE8021QciCtrl*>(msg))
        {
            cPacket *data = ctrl->decapsulate();
            delete ctrl;
            this->numBytesSent += data->getByteLength();
            emit(framePassedSignal, static_cast<long>(data->getByteLength()));
            sendDirect(data, streamOutput->gate("filterIn"));
        }
        else
        {
            this->numBytesSent += dynamic_cast<cPacket*>(msg)->getByteLength();
            emit(framePassedSignal, static_cast<long>(dynamic_cast<cPacket*>(msg)->getByteLength()));
            sendDirect(msg, streamOutput->gate("filterIn"));
        }
    }
}

void IEEE8021QciMeter::finish()
{
    simtime_t t = simTime();
    if (t > 0)
    {
        if (numFramesReceived > 0)
        {
            recordScalar("frames/sec rcvd", this->numFramesReceived / t);
            recordScalar("bits/sec rcvd", (8.0 * this->numBytesReceived) / t);
        }
        recordScalar("frames/sec passed", this->numFramesSent / t);
        recordScalar("bits/sec passed", (8.0 * this->numBytesSent) / t);
    }
}

} //namespace
