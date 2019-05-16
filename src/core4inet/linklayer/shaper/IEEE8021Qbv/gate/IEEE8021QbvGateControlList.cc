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

#include "IEEE8021QbvGateControlList.h"

//std
#include <limits>
//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/linklayer/shaper/IEEE8021Qbv/gate/IEEE8021QbvGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QbvGateControlList);

void IEEE8021QbvGateControlList::initialize(int stage)
{
    if (stage == 1)
    {
        Timed::initialize();
        this->tick = getOscillator()->getPreciseTick();
        this->handleParameterChange(nullptr);
        this->controlElement = this->controlList.begin();
        this->propagteCurrentControlElement();
        this->scheduleCurrentControlElementTime();
    }
}

int IEEE8021QbvGateControlList::numInitStages() const
{
    return 2;
}

void IEEE8021QbvGateControlList::handleParameterChange(const char* parname)
{
    Timed::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "numGates"))
    {
        this->numGates = parameterULongCheckRange(par("numGates"), 1, std::numeric_limits<unsigned int>::max());
    }
    if (!parname || !strcmp(parname, "controlList"))
    {
        vector<string> controlRows = cStringTokenizer(par("controlList"), ";").asVector();
        for (vector<string>::const_iterator controlRow = controlRows.begin(); controlRow != controlRows.end(); ++controlRow)
        {
            vector<string> controlRowTupel = cStringTokenizer((*controlRow).c_str(), ":").asVector();
            vector<string> controlRowGates = cStringTokenizer(controlRowTupel[0].c_str(), ",").asVector();
            if (controlRowGates.size() != this->numGates)
            {
                throw cRuntimeError("controlList row size is not %d", this->numGates);
            }
            double controlRowTime = stod(controlRowTupel[1]);
            controlList.push_back(make_pair(controlRowGates, controlRowTime));
        }
    }
}

void IEEE8021QbvGateControlList::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("schedulerIn"))
    {
        this->switchToNextControlElement();
        this->propagteCurrentControlElement();
        this->scheduleCurrentControlElementTime();
    }
}

void IEEE8021QbvGateControlList::scheduleCurrentControlElementTime()
{
    SchedulerTimerEvent* event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
    event->setTimer(static_cast<uint64_t>(ceil((*(this->controlElement)).second / this->tick)));
    event->setDestinationGate(this->gate("schedulerIn"));
    getTimer()->registerEvent(event);
}

void IEEE8021QbvGateControlList::propagteCurrentControlElement()
{
    for (unsigned int i=0; i<numGates; i++)
    {
        IEEE8021QbvGate* tg = dynamic_cast<IEEE8021QbvGate*>(this->getParentModule()->getSubmodule("transmissionGate", i));
        if ( !strcmp((*(this->controlElement)).first[i].c_str(), "o"))
        {
            tg->open();
        }
        if ( !strcmp((*(this->controlElement)).first[i].c_str(), "C"))
        {
            tg->close();
        }
    }
}

void IEEE8021QbvGateControlList::switchToNextControlElement()
{
    ++(this->controlElement);
    if (this->controlElement == this->controlList.end())
    {
        this->controlElement = this->controlList.begin();
    }
}


} //namespace
