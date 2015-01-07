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

#ifndef __CORE4INET_SIMPLEOSCILLATOR_H_
#define __CORE4INET_SIMPLEOSCILLATOR_H_

//CoRE4INET
#include "CoRE4INET_Oscillator.h"
#include "CoRE4INET_Scheduled.h"

namespace CoRE4INET {

/**
 * Module representing an oscillator with a simple clock drift behavior.
 *
 * The module schedules a message for every cycle at action_point 0 and then changes the drift by using the drift_change
 * parameter.
 *
 * @author Till Steinbach
 */
class SimpleOscillator : public Oscillator, Scheduled
{
    private:
        /**
         * @brief True if parameters were initialized
         */
        bool parametersInitialized;

        /**
         * @brief Caches max_drift parameter in simtime;
         */
        simtime_t max_drift;

        /**
         * Simulation time when the oscillator was recalculated the last time
         */
        simtime_t lastCorrection;
    protected:
        /**
         * @brief Initializes the module and registers the event for the recalculation of the drift
         */
        virtual void initialize(int stage);
        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return Always returns 2
         */
        virtual int numInitStages() const;

        /**
         * @brief On incoming scheduler messages the drift is recalculated
         */
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);
    public:
        /**
         * @brief constructor for SimpleOscillator
         */
        SimpleOscillator();
};

} //namespace

#endif
