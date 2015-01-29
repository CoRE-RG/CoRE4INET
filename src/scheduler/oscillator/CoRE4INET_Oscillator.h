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

#ifndef __CORE4INET_OSCILLATOR_H_
#define __CORE4INET_OSCILLATOR_H_

//OMNeT++
#include "csimplemodule.h"

namespace CoRE4INET {

/**
 * Abstract Base For a Module representing an oscillator.
 *
 * @author Till Steinbach
 */
class Oscillator : public virtual cSimpleModule
{
    private:
        /**
         * @brief True if parameters were initialized
         */
        bool parametersInitialized;

        /**
         * @brief Caches tick parameter
         */
        simtime_t tick;

        /**
         * @brief Caches current_tick parameter
         */
        simtime_t current_tick;

    protected:
        /**
         * Signal that is emitted every time the drift (Difference of configured and actual tick length) changes
         */
        static simsignal_t currentDrift;

    protected:
        virtual void initialize(int stage) override;
        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return Always returns 1
         */
        virtual int numInitStages() const override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

    public:
        /**
         * @brief Constructor of Oscillator
         */
        Oscillator();
        /**
         * @brief Returns the current length of a tick
         *
         * @return current length of a tick
         */
        simtime_t getCurrentTick() const;

        /**
         * @brief Sets the current length of a tick
         *
         * @param tick_length new length of a tick
         */
        void setCurrentTick(simtime_t tick_length);
        /**
         * @brief Returns the precise length of a tick (without drift)
         *
         * @return length of tick without drift
         */
        simtime_t getPreciseTick();
};

} //namespace

#endif
