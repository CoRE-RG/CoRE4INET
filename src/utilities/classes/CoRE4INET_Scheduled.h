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

#ifndef __CORE4INET_SCHEDULED_H_
#define __CORE4INET_SCHEDULED_H_

//CoRE4INET
#include "CoRE4INET_Timed.h"
#include "CoRE4INET_Period.h"

namespace CoRE4INET {

/**
 * @brief Base class for a module that uses a scheduler to schedule actions at action points
 *
 * @sa Timed
 *
 * @author Till Steinbach
 */
class Scheduled : public Timed
{
    private:
        /**
         * Checks whether the parameters were already initialized
         */
        bool parametersInitialized;

        /**
         * The period related to the actions of this module default is period[0]
         */
        Period *period;

    protected:
        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
    public:
        /**
         * @brief Constructor of Scheduled
         */
        Scheduled();

        /**
         * returns pointer to the configured period
         */
        Period* getPeriod();
};

}
#endif /* __CORE4INET_SCHEDULED_H_ */
