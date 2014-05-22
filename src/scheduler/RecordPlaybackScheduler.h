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

#ifndef __CORE4INET_RECORDPLAYBACKSCHEDULER_H_
#define __CORE4INET_RECORDPLAYBACKSCHEDULER_H_

#include "omnetpp.h"

#include "TTEScheduler.h"

namespace CoRE4INET {

/**
 * @brief Extended Scheduler module with record and playback feature.
 *
 * Extended Scheduler module. The module allows to record the oscillator behaviour
 * when the read variable is set to true. The same behaviour can then be replayed
 * when setting write to true. This can speed up the simulation significantly as the
 * it makes it unnecessary to simulate complex modules such as synchronisation or
 * oscillator behaviour more than once.
 */
class RecordPlaybackScheduler : public TTEScheduler
{
    private:
        FILE *fp;
        unsigned int counter;
        std::vector<double> *values;
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

    public:
        /**
         * @brief Destructor
         */
        ~RecordPlaybackScheduler();

        /**
         * @brief Helper function to change the drift
         *
         * This function uses the recorded values. Do not overwrite it!
         */
        virtual void changeDrift();
};

} //namespace

#endif
