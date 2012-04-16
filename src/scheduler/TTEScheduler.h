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

        /**
         * @brief List of registered SchedulerEvents.
         *
         * Used to reregister after clock tick changes.
         */
        std::list<SchedulerEvent*> registredEvents;

        cMessage* newCyclemsg;

        /**
         * @brief caches max_drift_change parameter
         */
        double maxDriftChange;
        /**
         * @brief caches max_drift parameter
         */
        double maxDrift;

        /**
         * @brief caches current_tick parameter
         */
        double currentTick;
        /**
         * @brief caches tick parameter
         */
        double tick;
        /**
         * @brief caches cycle_ticks parameter
         */
        long cycleTicks;

        /**
         * @brief Number of cycles since the simulation started
         */
        unsigned long cycles;

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
         * @brief Returns the current number of cycles
         *
         * @return Number of cycles since simulation start
         */
        virtual unsigned int getCycles();

        /**
         * @brief Corrects the clock by the number of ticks
         *
         * @param number of ticks the clock must be corrected
         */
        virtual void clockCorrection(int ticks);

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
