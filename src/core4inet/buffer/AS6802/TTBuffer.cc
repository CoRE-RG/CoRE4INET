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

#include "core4inet/buffer/AS6802/TTBuffer.h"

//Auto-generated Messages
#include "core4inet/buffer/AS6802/TTBufferEmpty_m.h"
#include "core4inet/scheduler/SchedulerMessageEvents_m.h"

//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

using namespace CoRE4INET;

TTBuffer::TTBuffer()
{
    this->parametersInitialized = false;

    this->actionTimeEvent = nullptr;
    this->nextAction = 0;

    this->sendWindowStart = 0;
    this->sendWindowEnd = 0;
}

TTBuffer::~TTBuffer()
{
}

int TTBuffer::numInitStages() const
{
    return 2;
}

void TTBuffer::initialize(int stage)
{
    CTBuffer::initialize(stage);
    if (stage == 0)
    {
        nextAction = par("sendWindowStart");
    }
    if (stage == 1)
    {
        EV_DETAIL << "Initialize TTBuffer" << endl;

        //Register Event
        Scheduled::initialize();

        actionTimeEvent = new SchedulerActionTimeEvent("TTBuffer Scheduler Event", ACTION_TIME_EVENT);
        actionTimeEvent->setAction_time(par("sendWindowStart"));
        actionTimeEvent->setDestinationGate(gate("schedulerIn"));

        if (static_cast<uint32_t>(par("sendWindowStart")) >= getPeriod()->getCycleTicks())
        {
            throw cRuntimeError("The send window (%d ticks) starts outside of the period (%d ticks)",
                    par("sendWindowStart").intValue(), getPeriod()->getCycleTicks());
        }

        nextAction = getPeriod()->registerEvent(actionTimeEvent);
        this->handleParameterChange(nullptr);
        return;
    }
}

void TTBuffer::handleMessage(cMessage *msg)
{
    bool arrivedOnSchedulerIn = msg->arrivedOn("schedulerIn");

    CTBuffer::handleMessage(msg);

    if (arrivedOnSchedulerIn && msg->getKind() == ACTION_TIME_EVENT && destinationGates.size() > 0)
    {
        inet::EtherFrame *outgoingMessage = getFrame();
        //Send Message
        for (std::list<cGate*>::const_iterator destGate = destinationGates.begin(); destGate != destinationGates.end();
                ++destGate)
        {
            if(isEnabled())
            {
                if (outgoingMessage)
                {
                    sendDirect(outgoingMessage->dup(), *destGate);
                }
                else
                {
                    sendDirect(new TTBufferEmpty("TT Buffer Empty"), *destGate);
                }
            }
        }
        if (gate("out")->isConnected())
        {
            if(isEnabled())
            {
                if (outgoingMessage)
                {
                    send(outgoingMessage->dup(), "out");
                }
                else
                {
                    send(new TTBufferEmpty("TT Buffer Empty"), "out");
                }
            }
        }
        if (outgoingMessage)
        {
            recordPacketSent(outgoingMessage);
            delete outgoingMessage;
        }
        //Reregister scheduler
        static_cast<SchedulerActionTimeEvent *>(msg)->setNext_cycle(true);
        nextAction = getPeriod()->registerEvent(static_cast<SchedulerActionTimeEvent *>(msg));
    }
}

void TTBuffer::handleParameterChange(const char* parname)
{
    CTBuffer::handleParameterChange(parname);
    Scheduled::handleParameterChange(parname);

    if (!parname && !parametersInitialized)
    {
        parametersInitialized = true;
    }
    if (!parname || !strcmp(parname, "sendWindowStart"))
    {
        sendWindowStart = static_cast<uint32_t>(parameterULongCheckRange(par("sendWindowStart"), 0,
                getPeriod()->getCycleTicks()));
        if (actionTimeEvent)
        {
            actionTimeEvent->setAction_time(sendWindowStart);
        }
    }
    if (!parname || !strcmp(parname, "sendWindowEnd"))
    {
        sendWindowEnd = static_cast<uint32_t>(parameterULongCheckRange(par("sendWindowEnd"), 0,
                getPeriod()->getCycleTicks()));
    }

}

uint64_t TTBuffer::nextSendWindowStart() const
{
    return nextAction;
}

long TTBuffer::getRequiredBandwidth()
{
    return static_cast<long>(ceil(
            static_cast<double>(getMaxMessageSize() * 8) * (1 / (getPeriod()->getCycleLength().dbl()))));
}

uint32_t TTBuffer::getSendWindowStart()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->sendWindowStart;
}

uint32_t TTBuffer::getSendWindowEnd()
{
    if (!parametersInitialized)
    {
        handleParameterChange(nullptr);
    }
    return this->sendWindowEnd;
}
