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

#ifndef __CORE4INET_TIMED_H_
#define __CORE4INET_TIMED_H_

//CoRE4INET
#include "CoRE4INET_Oscillator.h"
#include "CoRE4INET_Timer.h"

namespace CoRE4INET {

/**
 * @brief Base class for a module that uses a scheduler to set timers
 *
 * @author Till Steinbach
 */
class Timed : public virtual cSimpleModule
{
    private:
        /**
         * Checks whether the parameters were already initialized
         */
        bool parametersInitialized;

        /**
         * The oscillator module related to the this module
         */
        Oscillator *oscillator;

        /**
         * The timer module related to the this module
         */
        Timer *timer;

    public:
        /**
         * Default Constructor for Timed
         */
        Timed();

        /**
         * returns pointer to the configured timer
         */
        Timer* getTimer();

        /**
         * returns pointer to the configured oscillator
         */
        Oscillator* getOscillator();

    protected:
        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
};

}
#endif /* __CORE4INET_TIMED_H_ */
