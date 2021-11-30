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

#include "IEEE8021QbvSelection.h"

//std
#include <limits>
//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/base/NotifierConsts.h"
#include "core4inet/buffer/base/Buffer.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selectionAlgorithm/IEEE8021QbvSelectionAlgorithm.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/gate/IEEE8021QbvGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QbvSelection);

IEEE8021QbvSelection::IEEE8021QbvSelection()
{
    this->numPCP = 0;
}

void IEEE8021QbvSelection::initialize(int stage)
{
    BaseShaper::initialize(stage);
    if (stage == 0)
    {
        this->handleParameterChange(nullptr);
        for (unsigned int i=0; i<this->numPCP; i++)
        {
            this->getParentModule()->getSubmodule("queue", i)->subscribe(NF_QBV_STATE_CHANGED, this);
            this->getParentModule()->getSubmodule("transmissionSelectionAlgorithm", i)->subscribe(NF_QBV_STATE_CHANGED, this);
            this->getParentModule()->getSubmodule("transmissionGate", i)->subscribe(NF_QBV_STATE_CHANGED, this);
            simsignal_t signalPk = registerSignal(("qPcp" + std::to_string(i) + "Pk").c_str());
            cProperty* statisticTemplate = getProperties()->get("statisticTemplate", "qPcpPk");
            getEnvir()->addResultRecorders(this, signalPk, ("qPcp" + std::to_string(i) + "Pk").c_str(), statisticTemplate);
            statisticTemplate = getProperties()->get("statisticTemplate", "qPcpBytes");
            getEnvir()->addResultRecorders(this, signalPk, ("qPcp" + std::to_string(i) + "Bytes").c_str(), statisticTemplate);
            simsignal_t signalPkAge = registerSignal(("qPcp" + std::to_string(i) + "PkAge").c_str());
            statisticTemplate = getProperties()->get("statisticTemplate", "qPcpLatency");
            getEnvir()->addResultRecorders(this, signalPkAge, ("qPcp" + std::to_string(i) + "Latency").c_str(), statisticTemplate);
            this->qPcpPkSignals.push_back(signalPk);
            this->qPcpPkAgeSignals.push_back(signalPkAge);
            //Send initial signal to create statistic
            inet::EtherFrame* initFrame = new inet::EtherFrame();
            initFrame->setByteLength(0);
            emit(signalPk, initFrame);
            emit(signalPkAge, initFrame->getArrivalTime() - initFrame->getCreationTime());
            delete initFrame;
            this->numFrames.push_back(0);
            this->numBytes.push_back(0);
        }
    }
}

void IEEE8021QbvSelection::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "numPCP"))
    {
        this->numPCP = static_cast<unsigned int>(parameterULongCheckRange(par("numPCP"), 1, std::numeric_limits<int>::max()));
    }
}

void IEEE8021QbvSelection::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage())
    {
        this->selectFrame();
        delete msg;
    }
    else if (msg->arrivedOn("in"))
    {
        if (inet::EtherFrame* frame = dynamic_cast<inet::EtherFrame*>(msg))
        {
            int pcp = frame->getSenderModule()->getIndex();
            emit(this->qPcpPkSignals[pcp], frame);
            emit(this->qPcpPkAgeSignals[pcp], frame->getArrivalTime() - frame->getCreationTime());
            this->numFrames[pcp] = this->numFrames[pcp] + 1;
            this->numBytes[pcp] = this->numBytes[pcp] + static_cast<unsigned long>(frame->getByteLength());
            this->send(frame, "out");
        }
        else
        {
            throw cRuntimeError("Selected frame type is not inet::EtherFrame");
        }
    }
}

void IEEE8021QbvSelection::receiveSignal(cComponent *src, simsignal_t id, long l, __attribute__((unused)) cObject *details)
{
    Enter_Method_Silent();
    if (id == NF_QBV_STATE_CHANGED && l > 0)
    {
        this->bubble("State changed.");
        cMessage* msg = new cMessage();
        scheduleAt(simTime(), msg);
    }
}

void IEEE8021QbvSelection::requestPacket()
{
    Enter_Method("requestPacket()");
    this->framesRequested++;
    if (this->framesRequested > 1)
    {
        throw cRuntimeError("Frames requested counter is higher than 1.");
    }
    this->selectFrame();
}

void IEEE8021QbvSelection::finish()
{
    simtime_t t = simTime();
    if (t > 0)
    {
        for (unsigned int i=0; i<this->numPCP; i++)
        {
            recordScalar(("qPcp" + std::to_string(i) + " frames/sec").c_str(), this->numFrames[i] / t);
            recordScalar(("qPcp" + std::to_string(i) + " bits/sec").c_str(), (8.0 * this->numBytes[i]) / t);
        }
    }
}

void IEEE8021QbvSelection::selectFrame()
{
    if (this->framesRequested > 0)
    {
        for(int i=this->numPCP-1; i>=0; i--)
        {
            Buffer* queue = dynamic_cast<Buffer*>(this->getParentModule()->getSubmodule("queue", i));
            IEEE8021QbvSelectionAlgorithm* tsa = dynamic_cast<IEEE8021QbvSelectionAlgorithm*>(this->getParentModule()->getSubmodule("transmissionSelectionAlgorithm", i));
            IEEE8021QbvGate* tg = dynamic_cast<IEEE8021QbvGate*>(this->getParentModule()->getSubmodule("transmissionGate", i));
            if (queue && queue->size() > 0 && tsa && tsa->isOpen() && tg && tg->isOpen())
            {
                this->framesRequested--;
                if (this->framesRequested > 1)
                {
                    throw cRuntimeError("Frames requested counter is higher than 1.");
                }
                queue->getFrame();
                return;
            }
        }
    }
}

} //namespace
