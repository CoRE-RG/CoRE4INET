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

#ifndef __CORE4INET_PERIOD_H_
#define __CORE4INET_PERIOD_H_

//OMNeT++
#include "csimplemodule.h"
//CoRE4INET
#include "CoRE4INET_SchedulerEvent.h"
//Auto-generated Messages
#include "scheduler/SchedulerMessageEvents_m.h"

namespace CoRE4INET {

class Timer;

/**
 * Period Module: Periods define the cycles for events
 *
 * @author Till Steinbach
 */
class Period : public virtual cSimpleModule
{
    private:
        /**
         * @brief True if parameters were initialized
         */
        bool parametersInitialized;

        /**
         * @brief Connected timer module
         */
        Timer *timer;
        /**
         * @brief Event indicating a new cycle start
         *
         */
        SchedulerActionTimeEvent* newCycleEvent;

        /**
         * @brief Number of cycles since the simulation started
         */
        uint32_t cycles;

        /**
         * @brief Caches cycle_ticks parameter
         */
        uint32_t cycle_ticks;

        /**
         * @brief Caches offset_ticks parameter
         */
        uint32_t offset_ticks;

    protected:
        /**
         * Signal that is emitted at the beginning of a new cycle
         */
        static simsignal_t newCycle;

    protected:
        /**
         * Initialization of module, schedules new cycle message at timer
         */
        virtual void initialize() override;
        /**
         * Received new cycle message to count cycles
         * @param msg incoming new cycle message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
    public:
        /**
         * Constructor, Initialization of members
         */
        Period();
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
        uint64_t registerEvent(SchedulerEvent *event);

        /**
         * @brief Returns the current number of ticks
         *
         * @return Number of ticks since cycle start
         */
        uint32_t getTicks();
        /**
         * @brief Returns the absolute number of ticks
         *
         * @return Number of ticks since simulation start
         */
        uint64_t getTotalTicks();
        /**
         * @brief Returns the current number of cycles
         *
         * @return Number of cycles since simulation start
         */
        uint32_t getCycles() const;

        /**
         * @brief Returns a pointer to the Timer module driving this period
         *
         * @return Timer driving the period
         */
        Timer* getTimer();

        /**
         * @brief Returns the cycle length of this period
         *
         * @return Number of ticks of one cycle
         */
        uint32_t getCycleTicks();

        /**
         * @brief Returns the cycle length of this period
         *
         * @return Length of one cycle in simtime
         */
        simtime_t getCycleLength();

        /**
         * @brief Returns the offset of this period
         *
         * @return Offset of the period in number of ticks
         */
        uint32_t getOffsetTicks();
};

} //namespace

#endif
