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
#include "core4inet/buffer/base/Buffer.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selectionAlgorithm/IEEE8021QbvSelectionAlgorithm.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/gate/IEEE8021QbvGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QbvSelection);

IEEE8021QbvSelection::IEEE8021QbvSelection()
{
    this->framesRequested = 0;
    this->numPCP = 0;
}

void IEEE8021QbvSelection::reportChange()
{
    Enter_Method("reportChange()");
    if (this->framesRequested > 0)
    {
        selectFrame();
    }
}

void IEEE8021QbvSelection::initialize(int stage)
{
    if (stage == 0)
    {
        this->handleParameterChange(nullptr);
        for (unsigned int i=0; i<this->numPCP; i++)
        {
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
        }
    }
}

void IEEE8021QbvSelection::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "numPCP"))
    {
        this->numPCP = parameterULongCheckRange(par("numPCP"), 1, std::numeric_limits<unsigned int>::max());
    }
}

void IEEE8021QbvSelection::handleMessage(cMessage* msg)
{
    if (msg->arrivedOn("in"))
    {
        if (inet::EtherFrame* frame = dynamic_cast<inet::EtherFrame*>(msg))
        {
            emit(this->qPcpPkSignals[frame->getSenderModule()->getIndex()], frame);
            emit(this->qPcpPkAgeSignals[frame->getSenderModule()->getIndex()], frame->getArrivalTime() - frame->getCreationTime());
            this->send(frame, "out");
        }
        else
        {
            throw cRuntimeError("Selected frame type is not inet::EtherFrame");
        }
    }
}

void IEEE8021QbvSelection::requestPacket()
{
    Enter_Method("requestPacket()");
    this->framesRequested++;
    selectFrame();
}

void IEEE8021QbvSelection::selectFrame()
{
    for(long i=static_cast<long>(numPCP)-1; i>=0; i--)
    {
        Buffer* queue = dynamic_cast<Buffer*>(this->getParentModule()->getSubmodule("queue", i));
        IEEE8021QbvSelectionAlgorithm* tsa = dynamic_cast<IEEE8021QbvSelectionAlgorithm*>(this->getParentModule()->getSubmodule("transmissionSelectionAlgorithm", i));
        IEEE8021QbvGate* tg = dynamic_cast<IEEE8021QbvGate*>(this->getParentModule()->getSubmodule("transmissionGate", i));
        if (queue && queue->size() > 0 && tsa && tsa->isOpen() && tg && tg->isOpen())
        {
            queue->getFrame();
            this->framesRequested--;
            return;
        }
    }
}

} //namespace
