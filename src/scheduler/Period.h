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

#ifndef __TTETHERNETMODEL_PERIOD_H_
#define __TTETHERNETMODEL_PERIOD_H_

#include <omnetpp.h>
#include <SchedulerEvent.h>
#include <SchedulerMessageEvents_m.h>

namespace TTEthernetModel {

class Timer;

/**
 * TODO - Generated class
 */
class Period : public cSimpleModule
{
    private:
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
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  public:
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
    virtual uint64_t registerEvent(SchedulerEvent *event);

    /**
     * @brief Returns the current number of ticks
     *
     * @return Number of ticks since cycle start
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
};

} //namespace

#endif
