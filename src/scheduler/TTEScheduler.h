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

#ifndef __CORE4INET_TTESCHEDULER_H_
#define __CORE4INET_TTESCHEDULER_H_

#include "omnetpp.h"

#include <SchedulerMessage_m.h>
#include <SchedulerEvent.h>
#include <SchedulerMessageEvents_m.h>

namespace CoRE4INET {

/**
 * @brief Scheduler module.
 *
 * @warning DEPRICATED MODULE, Please use Scheduler Module instead!
 * @sa Scheduler
 *
 * Implements a scheduler with a dedicated local clock with
 * adjustable precision that may be synchronized by a synchronization
 * module
 */
class TTEScheduler : public cSimpleModule
{
    protected:
        /**
         * @brief Simulation time when the last cycle started
         */
        simtime_t lastCycleStart;
        /**
         * @brief Simulation time when the last newcycle message was seen
         */
        simtime_t lastNewCycleMessage;

        /**
         * @brief Number of ticks since the simulation started
         * when the last cycle started
         */
        uint64_t lastCycleTicks;

        /**
         * @brief List of registered SchedulerEvents.
         *
         * Used to reregister after clock tick changes.
         */
        std::list<SchedulerEvent*> registredEvents;

        cMessage* newCyclemsg;

        /**
         * @brief caches max_drift parameter
         */
        simtime_t maxDrift;

        /**
         * @brief caches current_tick parameter
         */
        simtime_t currentTick;
        /**
         * @brief caches tick parameter
         */
        simtime_t tick;
        /**
         * @brief caches cycle_ticks parameter
         */
        uint32_t cycleTicks;

        /**
         * @brief Number of cycles since the simulation started
         */
        uint32_t cycles;

    public:
        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return 1
         */
        virtual int numInitStages() const;
    protected:
        /**
         * @brief Initialization of the module.
         *
         * @param stage the stages. Module initializes when stage==1
         */
        virtual void initialize(int stage);

        /**
         * @brief Handles all scheduler messages
         *
         * Registers self-messages for events sends messages to trigger events in
         * remote modules.
         *
         * @param msg the incoming message.
         */
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);

    public:
        /**
         * @brief Destructor
         */
        ~TTEScheduler();
        /**
         * @brief Returns the current number of ticks
         *
         * @return Number of ticks since last cycle start
         */
        virtual uint32_t getTicks();

        /**
         * @brief Returns the absolute number of ticks
         *
         * @return Number of ticks since simulation start
         */
        virtual uint64_t getTotalTicks();

        /**
         * @brief Returns the current number of cycles
         *
         * @return Number of cycles since simulation start
         */
        virtual uint32_t getCycles();

        /**
         * @brief Corrects the clock by the number of ticks
         *
         * @param ticks number of ticks the clock must be corrected
         */
        virtual void clockCorrection(int32_t ticks);

        /**
         * Register a new event in the scheduler. May fail if ActionTimeEvent is out of schedule
         *
         * @param event Pointer to the Event to be scheduled.
         * The scheduler will send the event according to the event type
         * @return returns true on success, else false
         *
         * @sa SchedulerEvent_Base, SchedulerEvent, SchedulerActionTimeEvent,
         * SchedulerTimerEvent
         */
        virtual bool registerEvent(SchedulerEvent *event);

        /**
         * Register a new event in the scheduler. May fail if ActionTimeEvent is out of schedule
         *
         * @param actionTimeEvent Pointer to the Event to be scheduled.
         * The scheduler will send the event according to the event type
         * @param forceNextCycle should the event be forced in the next
         * cycle even if it could be executed in this cycle
         * @return returns true on success, else false
         *
         * @sa SchedulerEvent_Base, SchedulerEvent, SchedulerActionTimeEvent,
         * SchedulerTimerEvent
         */
        virtual bool registerEvent(SchedulerActionTimeEvent *actionTimeEvent, bool forceNextCycle);

        /**
         * Unregister an event that was previously registered in the scheduler.
         * You must delete the event afterwards manually!
         *
         * @param event Pointer to the Event to be unregistered.
         * The scheduler will not send the event anymore
         *
         * @sa SchedulerEvent_Base, SchedulerEvent, SchedulerActionTimeEvent,
         * SchedulerTimerEvent
         */
        virtual void unregisterEvent(SchedulerEvent *event);

        /**
         * @brief Helper function to correct Events after tick length changes
         */
        virtual void correctEvents();

        /**
         * @brief Helper function to change the drift
         *
         * Can be overwritten to implement special clock drift behavior.
         */
        virtual void changeDrift();
    protected:
        /**
         * Signal that is emitted every time the drift (Difference of configured and actual tick length) changes
         */
        static simsignal_t currentDrift;

        /**
         * Signal that is emitted at the beginning of a new cycle
         */
        static simsignal_t newCycle;
};

} //namespace

#endif
