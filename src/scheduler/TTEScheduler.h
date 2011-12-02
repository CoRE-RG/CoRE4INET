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

#ifndef __TTETHERNETMODELV2_TTESCHEDULER_H_
#define __TTETHERNETMODELV2_TTESCHEDULER_H_

#include <omnetpp.h>

#include <SchedulerMessage_m.h>
#include <SchedulerEvent.h>

namespace TTEthernetModel {

/**
 * @brief Scheduler module.
 *
 * Implements a scheduler with a dedicated local clock with
 * adjustable precision that may be synchronized by a synchronization
 * module
 */
class TTEScheduler : public cSimpleModule
{
    private:
        /**
         * @brief Simulation time when the last cycle started
         */
        SimTime lastCycleStart;

        /**
         * @brief Number of ticks since the simulation started
         * when the last cycle started
         */
        unsigned long lastCycleTicks;

        std::list<SchedulerEvent*> registredEvents;

    protected:
        /**
         * @brief Initialization of the module.
         *
         * @todo remove XML parsing, this should be done in a dedicated class.
         */
        virtual void initialize();

        /**
         * @brief Handles all scheduler messages
         *
         * Registers self-messages for events sends messages to trigger events in
         * remote modules.
         *
         * @param msg the incoming message.
         */
        virtual void handleMessage(cMessage *msg);

    public:
        /**
         * @brief Returns the current number of ticks
         *
         * @return Number of ticks since last cycle start
         */
        virtual unsigned int getTicks();

        /**
         * @brief Returns the absolute number of ticks
         *
         * @return Number of ticks since simulation start
         */
        virtual unsigned long getTotalTicks();

        /**
         * @brief Corrects the clock by the number of ticks
         *
         * @param number of ticks the clock must be corrected
         */
        virtual void clockCorrection(int ticks);

        /**
         * Register a new event in the scheduler
         *
         * @param event Pointer to the Event to be scheduled.
         * The scheduler will send the event according to the event type
         *
         * @sa SchedulerEvent_Base, SchedulerEvent, SchedulerActionTimeEvent,
         * SchedulerTimerEvent
         */
        virtual void registerEvent(SchedulerEvent *event);

        virtual void correctEvents();
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
