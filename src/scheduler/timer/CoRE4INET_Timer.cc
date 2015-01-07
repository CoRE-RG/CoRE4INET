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

#include "CoRE4INET_Timer.h"

//Std
#include <exception>
//CoRE4INET
#include "CoRE4INET_customWatch.h"
//INET
#include "INETDefs.h"

namespace CoRE4INET {

Define_Module(Timer);

simsignal_t Timer::clockCorrectionSignal = registerSignal("clockCorrection");

Timer::Timer()
{
    ticks = 0;
    selfMessage = new cMessage("Scheduler Message");
    oscillator = nullptr;
}

void Timer::initialize()
{
    oscillator = dynamic_cast<Oscillator*>(gate("oscillator_in")->getPathStartGate()->getOwnerModule());
    ASSERT2(oscillator, "cannot find oscillator!");

    recalculationTime = lastRecalculation = simTime();

    WATCH_PAIRLISTMAP(registredActionTimeEvents);
    WATCH_LISTMAP(registredTimerEvents);
}

Timer::~Timer()
{
    cancelAndDelete(selfMessage);
    for (std::map<uint64_t, std::list<std::pair<SchedulerActionTimeEvent*, Period*> > >::iterator it =
            registredActionTimeEvents.begin(); it != registredActionTimeEvents.end();)
    {
        for (std::list<std::pair<SchedulerActionTimeEvent*, Period*> >::const_iterator it2 = (*it).second.begin();
                it2 != (*it).second.end(); ++it2)
        {
            cancelAndDelete((*it2).first);
        }
        registredActionTimeEvents.erase(it++);
    }
    for (std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it = registredTimerEvents.begin();
            it != registredTimerEvents.end();)
    {
        for (std::list<SchedulerTimerEvent*>::const_iterator it2 = (*it).second.begin(); it2 != (*it).second.end();
                ++it2)
        {
            cancelAndDelete(*it2);
        }
        registredTimerEvents.erase(it++);
    }
}

void Timer::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        sendOutEvents();
    }
}

void Timer::sendOutEvents()
{
    recalculate();
    for (std::map<uint64_t, std::list<std::pair<SchedulerActionTimeEvent*, Period*> > >::iterator it =
            registredActionTimeEvents.begin(); it != registredActionTimeEvents.end() && (*it).first <= ticks;)
    {
        if ((*it).first < ticks)
        {
            EV_WARN << "WARNING: Message(s) (was/were) delayed by the scheduler. The event(s) affected (is/are): ";
            for (std::list<std::pair<SchedulerActionTimeEvent*, Period*> >::const_iterator it2 = (*it).second.begin();
                    it2 != (*it).second.end(); ++it2)
            {
                EV_WARN << (*it2).first->getName() << " by "
                        << (*it2).first->getDestinationGate()->getOwner()->getName() << "; ";
            }
            EV_WARN << "The delay was " << (ticks - (*it).first)
                    << "ticks. This may happen for events in the clock correction interval." << std::endl;
            if (ev.isGUI())
            {
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getDisplayString().setTagArg("tt", 0,
                        "WARNING: ActionTimeEvent was delayed (probably due to clock correction)");
                getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                getParentModule()->getDisplayString().setTagArg("tt", 0, "Problem with Timer");
            }
        }
        for (std::list<std::pair<SchedulerActionTimeEvent*, Period*> >::const_iterator it2 = (*it).second.begin();
                it2 != (*it).second.end(); ++it2)
        {
            sendDirect((*it2).first, (*it2).first->getDestinationGate());
        }
        registredActionTimeEvents.erase(it++);
    }
    for (std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it = registredTimerEvents.begin();
            it != registredTimerEvents.end() && (*it).first <= ticks;)
    {
        if ((ticks - (*it).first) > 1)
        {
            EV_FATAL << "misscheduled: " << (ticks - (*it).first) << std::endl;
            throw cRuntimeError("THIS SHOULD NOT HAPPEN!");
        }
        for (std::list<SchedulerTimerEvent*>::const_iterator it2 = (*it).second.begin(); it2 != (*it).second.end();
                ++it2)
        {
            sendDirect((*it2), (*it2)->getDestinationGate());
        }
        registredTimerEvents.erase(it++);
    }
    reschedule();
}

void Timer::recalculate()
{
    if (simTime() != recalculationTime)
    { //simTime()!=lastRecalculation has no effect due to rounding avoidance
        if (!oscillator)
        {
            throw std::runtime_error("Timer was not yet initialized");
        }
        simtime_t current_tick = oscillator->getCurrentTick();
        uint64_t elapsed_ticks = static_cast<uint64_t>(floor((simTime() - lastRecalculation) / current_tick));
        ticks += elapsed_ticks;
        //this is required to avoid rounding errors
        lastRecalculation += static_cast<double>(elapsed_ticks) * current_tick;
        recalculationTime = simTime();
    }
}

void Timer::reschedule()
{
    if (!oscillator)
    {
        throw std::runtime_error("Timer was not yet initialized");
    }
    cancelEvent(selfMessage);
    recalculate();
    try
    {
        uint64_t next_action_ticks = nextAction();
        uint64_t total_ticks = getTotalTicks();
        if (total_ticks > next_action_ticks)
        {
            throw cRuntimeError("There must have been an overflow in the timer module");
        }
        simtime_t next_action = static_cast<double>(next_action_ticks - total_ticks) * oscillator->getCurrentTick();
        scheduleAt(simTime() + next_action, selfMessage);
    }
    catch (__attribute__((unused))   const std::range_error& re)
    {
        //No message should be scheduled as there are no messages registered
    }
    catch (const cRuntimeError& re)
    {
        throw cRuntimeError("%s: nextAction() %d getTotalTicks() %llu oscillator->getCurrentTick() %s",
                re.getFormattedMessage().c_str(), nextAction(), getTotalTicks(),
                oscillator->getCurrentTick().str().c_str());
        //No message should be scheduled as there are no messages registered
    }
}

uint64_t Timer::nextAction() const
{
    if (registredActionTimeEvents.empty() && registredTimerEvents.empty())
    {
        throw std::range_error("no events registered");
    }
    else if (registredTimerEvents.empty()
            || (!registredActionTimeEvents.empty()
                    && registredActionTimeEvents.begin()->first < registredTimerEvents.begin()->first))
    {
        return registredActionTimeEvents.begin()->first;
    }
    else
    {
        return registredTimerEvents.begin()->first;
    }
}

uint64_t Timer::registerEvent(SchedulerTimerEvent *event)
{
#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerTimerEvent %s)",event->getName());
#else
    Enter_Method_Silent
    ();
#endif
    if (event->getTimer() > (SimTime::getMaxTime() / oscillator->getCurrentTick()))
    {
        std::ostringstream oss;
        oss << "Cannot register timer event that is more than ";
        oss << (SimTime::getMaxTime() / oscillator->getCurrentTick());
        oss << "ticks from now. Your timer registered for ";
        oss << event->getTimer() << " ticks. Is your timer negative?";
        throw std::invalid_argument(oss.str());
    }
    take(event);
    //We do not have to schedule anything if the point is now!
    if (event->getTimer() == 0)
    {
        sendDirect(event, event->getDestinationGate());
        return getTotalTicks();
    }
    else
    {
        uint64_t actionpoint = getTotalTicks() + event->getTimer();
        try
        {
            uint64_t old_actionpoint = nextAction();
            registredTimerEvents[actionpoint].push_back(event);
            if (!selfMessage->isScheduled() || actionpoint < old_actionpoint)
            {
                reschedule();
            }
        }
        catch (__attribute((unused))             const std::range_error& re)
        {
            registredTimerEvents[actionpoint].push_back(event);
            reschedule();
        }
        return actionpoint;
    }
}

uint64_t Timer::registerEvent(SchedulerActionTimeEvent *actionTimeEvent, Period *period)
{
    if (!period)
    {
        throw cRuntimeError("Period not set in Timer");
    }

#ifdef DEBUG
    Enter_Method("registerEvent(SchedulerActionTimeEvent %s, %s)",actionTimeEvent->getName(), period->getName());
#else
    Enter_Method_Silent
    ();
#endif

    take(actionTimeEvent);

    uint64_t actionpoint = 0;

    //Check whether event is in cycle
    if (actionTimeEvent->getAction_time() > period->getCycleTicks())
    {
        bubble("Schedule contains out of cycle events!");
        return false;
    }
    int32_t distance = static_cast<int32_t>(static_cast<int64_t>(actionTimeEvent->getAction_time())
            - static_cast<int64_t>(period->getTicks()));
    if (distance < 0 || (distance == 0 && actionTimeEvent->getNext_cycle()))
    {
        actionpoint = static_cast<uint64_t>(static_cast<int64_t>(getTotalTicks())
                + (static_cast<int64_t>(period->getCycleTicks()) + distance));
    }
    else
    {
        actionpoint = static_cast<uint64_t>(static_cast<int64_t>(getTotalTicks()) + distance);
    }

    //We do not have to schedule anything if the point is now!
    if (actionpoint == getTotalTicks())
    {
        sendDirect(actionTimeEvent, actionTimeEvent->getDestinationGate());
    }
    else
    {
        ASSERT2(actionpoint > getTotalTicks(), "Cannot schedule past or present Events");
        try
        {
            uint64_t old_actionpoint = nextAction();
            registredActionTimeEvents[actionpoint].push_back(
                    std::pair<SchedulerActionTimeEvent*, Period*>(actionTimeEvent, period));
            if (!selfMessage->isScheduled() || actionpoint < old_actionpoint)
            {
                reschedule();
            }
        }
        catch (__attribute((unused))             const std::range_error& re)
        {
            registredActionTimeEvents[actionpoint].push_back(
                    std::pair<SchedulerActionTimeEvent*, Period*>(actionTimeEvent, period));
            reschedule();
        }

    }
    return actionpoint;
}

uint64_t Timer::getTotalTicks()
{
    recalculate();
    return ticks;
}

Oscillator* Timer::getOscillator() const
{
    if (!oscillator)
    {
        throw std::runtime_error("Timer was not yet initialized");
    }
    return oscillator;
}

void Timer::clockCorrection(int32_t correction_ticks)
{
    Enter_Method
    ("clock correction %d ticks", correction_ticks);
    emit(clockCorrectionSignal, correction_ticks);
    this->ticks = static_cast<uint64_t>(static_cast<int64_t>(this->ticks) + correction_ticks);
    //Now correct the timer events that must be independent of clockCorrection
    std::map<uint64_t, std::list<SchedulerTimerEvent*> > correctedTimerEvents;
    std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it = correctedTimerEvents.begin();
    for (std::map<uint64_t, std::list<SchedulerTimerEvent*> >::iterator it2 = registredTimerEvents.begin();
            it2 != registredTimerEvents.end(); ++it2)
    {
        if (correctedTimerEvents.empty())
        {
            correctedTimerEvents[static_cast<uint64_t>(static_cast<int64_t>((*it2).first) + correction_ticks)] = (*it2).second;
            it = correctedTimerEvents.begin();
        }
        else
        {
            //Better version with hint?
            it = correctedTimerEvents.insert(it,
                    std::pair<uint64_t, std::list<SchedulerTimerEvent*> >(
                            (static_cast<uint64_t>(static_cast<int64_t>((*it2).first) + correction_ticks)), (*it2).second));
        }
    }
    registredTimerEvents = correctedTimerEvents;

    //Now correct the actiontime events that must be recalculated after clock correction
    std::map<uint64_t, std::list<std::pair<SchedulerActionTimeEvent*, Period*> > > correctedActionTimeEvents;
    for (std::map<uint64_t, std::list<std::pair<SchedulerActionTimeEvent*, Period*> > >::const_iterator it2 =
            registredActionTimeEvents.begin(); it2 != registredActionTimeEvents.end(); ++it2)
    {

        for (std::list<std::pair<SchedulerActionTimeEvent*, Period*> >::const_iterator it4 = (*it2).second.begin();
                it4 != (*it2).second.end(); ++it4)
        {
            if ((*it2).first < this->ticks)
            {
                uint64_t corrected_tick = (*it2).first;
                while (corrected_tick < this->ticks)
                {
                    corrected_tick += (*it4).second->getCycleTicks();
                }
                correctedActionTimeEvents[corrected_tick].push_back(*it4);
            }
            else
            {
                correctedActionTimeEvents[(*it2).first].push_back(*it4);
            }
        }
    }
    registredActionTimeEvents = correctedActionTimeEvents;
    reschedule();
    //TODO normal: is this necessary?
    sendOutEvents();
}

} //namespace
