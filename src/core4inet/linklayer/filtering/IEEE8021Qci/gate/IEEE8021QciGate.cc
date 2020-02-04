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

#include "core4inet/linklayer/filtering/IEEE8021Qci/gate/IEEE8021QciGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciGate);

simsignal_t IEEE8021QciGate::frameDroppedSignal = registerSignal("frameDropped");

void IEEE8021QciGate::open()
{
    Enter_Method("open()");
    this->state = this->State::OPEN;
}

void IEEE8021QciGate::close()
{
    Enter_Method("close()");
    this->state = this->State::CLOSED;
}

void IEEE8021QciGate::initialize()
{
    this->handleParameterChange(nullptr);
    WATCH(this->state);
    WATCH(this->numFramesDropped);
}

void IEEE8021QciGate::handleMessage(cMessage *msg)
{
    if (IEEE8021QciCtrl *ctrl = dynamic_cast<IEEE8021QciCtrl*>(msg))
    {
        if (this->state == this->State::OPEN)
        {
            IEEE8021QciMeter *meter = dynamic_cast<IEEE8021QciMeter*>(getParentModule()->getSubmodule("flowMeter", ctrl->getMeterID()));
            if (!meter)
            {
                throw cRuntimeError("Cannot find meter %d!", ctrl->getMeterID());
            }
            sendDirect(msg, meter->gate("in"));
        }
        else if (this->state == this->State::CLOSED)
        {
            this->bubble("Frame dropped!");
            this->emit(frameDroppedSignal, static_cast<unsigned long>(ctrl->getEncapsulatedPacket()->getByteLength()));
            delete ctrl;
            this->numFramesDropped++;
        }
    }
    else
    {
        throw cRuntimeError("No filtering ctrl header");
    }
}

void IEEE8021QciGate::handleParameterChange(const char *parname)
{
    if (!parname || !strcmp(parname, "state"))
    {
        if (!strcmp(par("state").stringValue(), "o"))
        {
            this->state = this->State::OPEN;
        }
        else if (!strcmp(par("state").stringValue(), "C"))
        {
            this->state = this->State::CLOSED;
        }
        else
        {
            throw cRuntimeError("Parameter state of %s is %s and is only allowed to be o or C", getFullPath().c_str(), par("state").stringValue());
        }
    }
}

void IEEE8021QciGate::refreshDisplay() const
{
    if (this->state == this->State::OPEN)
    {
        this->getDisplayString().setTagArg("b",3,"green");
    }
    else if (this->state == this->State::CLOSED)
    {
        this->getDisplayString().setTagArg("b",3,"red");
    }
}

void IEEE8021QciGate::finish()
{
    recordScalar("frames dropped", this->numFramesDropped);
    simtime_t t = simTime();
    if (t > 0)
    {
        if (this->numFramesDropped > 0)
        {
            recordScalar("frames/sec dropped", this->numFramesDropped / t);
        }
    }
}

} //namespace
