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

#include <omnetpp.h>

namespace CoRE4INET {

/**
 * Abstract Base For a Module representing an oscillator.
 *
 * @author Till Steinbach
 */
class Oscillator : public virtual cSimpleModule
{
    protected:
        /**
         * Signal that is emitted every time the drift (Difference of configured and actual tick length) changes
         */
        static simsignal_t currentDrift;

    protected:
        virtual void initialize(int stage);
        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return Always returns 1
         */
        virtual int numInitStages() const;

    public:
        /**
         * @brief Returns the current length of a tick
         *
         * @return current length of a tick
         */
        virtual simtime_t getTick();
        /**
         * @brief Returns the precise length of a tick (without drift)
         *
         * @return length of tick without drift
         */
        virtual simtime_t getPreciseTick();
};

} //namespace

#endif
