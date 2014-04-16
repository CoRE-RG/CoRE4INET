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

#include <Oscillator.h>
#include <Timer.h>

namespace CoRE4INET {

/**
 * @brief TODO
 *
 * @author Till Steinbach
 */
class Timed : public virtual cSimpleModule
{
    protected:
        /**
         * TODO
         */
        Oscillator *oscillator;
        /**
         * TODO
         */
        Timer *timer;

    public:
        /**
         * @brief Initialization of the module
         */
        void initialize();
        /**
         * TODO
         */
        Timer* getTimer();

        /**
         * TODO
         */
        Oscillator* getOscillator();
};

}
#endif /* __CORE4INET_TIMED_H_ */
