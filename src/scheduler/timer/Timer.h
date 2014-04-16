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

#ifndef __TTETHERNETMODEL_TIMER_H_
#define __TTETHERNETMODEL_TIMER_H_

#include <omnetpp.h>

#include <Oscillator.h>
#include <Period.h>

#include <SchedulerMessage_m.h>
#include <SchedulerEvent.h>
#include <SchedulerMessageEvents_m.h>

namespace CoRE4INET {

/**
 * TODO - Generated class
 *
 * @author Till Steinbach
 */
class Timer : public cSimpleModule
{
    private:
        uint64_t ticks;
        Oscillator *oscillator;
        cMessage *selfMessage;

        /**
         * @brief Simulation time when the timer was last recalculated
         */
        simtime_t lastRecalculation;

        /**
         * @brief Simulation time when the timer was last recalculated
         */
        simtime_t recalculationTime;

        /**
         * @brief List of registered SchedulerActionTimeEvent.
         *
         * Used to reregister after clock tick changes.
         */
        std::map<uint64_t, std::list<SchedulerActionTimeEvent*> > registredActionTimeEvents;
        /**
         * @brief List of registered SchedulerActionTimeEvent.
         *
         * Used to reregister after clock tick changes.
         */
        std::map<uint64_t, std::list<SchedulerTimerEvent*> > registredTimerEvents;
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
    private:
        virtual void reschedule();
        virtual uint32_t nextAction();
        virtual void sendOutEvents();
    public:
        Timer();
        ~Timer();
        virtual void recalculate();

        /**
         * Register a new event in the scheduler. May fail if ActionTimeEvent is out of schedule
         *
         * @param event Pointer to the Event to be scheduled.
         * The scheduler will send the event according to the event type
         * @return returns registered event time
         *
         * @sa SchedulerEvent_Base, SchedulerEvent, SchedulerActionTimeEvent,
         * SchedulerTimerEvent
         */
        virtual uint64_t registerEvent(SchedulerActionTimeEvent *event, Period *period);

        virtual uint64_t registerEvent(SchedulerTimerEvent *event);

        /**
         * @brief Returns the absolute number of ticks
         *
         * @return Number of ticks since simulation start
         */
        virtual uint64_t getTotalTicks();

        virtual Oscillator* getOscillator();

        /**
         * @brief Corrects the clock by the number of ticks
         *
         * @param ticks number of ticks the clock must be corrected
         */
        virtual void clockCorrection(int32_t ticks);

    protected:
        /**
         * Signal that is emitted every time the clock is corrected
         */
        static simsignal_t clockCorrectionSignal;
};

} //namespace

#endif
