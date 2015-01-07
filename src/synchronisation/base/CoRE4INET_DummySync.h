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

#ifndef __CORE4INET_DUMMYSYNC_H_
#define __CORE4INET_DUMMYSYNC_H_

//CoRE4INET
#include "CoRE4INET_SyncBase.h"

namespace CoRE4INET {

/**
 * @brief Dummy sync module.
 *
 * This module corrects the time of a node by using the simulation time
 *
 * @author Till Steinbach
 */
class DummySync : public virtual SyncBase
{
    protected:
        /**
         * @brief Initializes the dummy synchronization module.
         *
         * registers an event in the scheduler to trigger the synchronization
         *
         * @param stage the stages. Module registers events when stage==1
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return always returns 2
         */
        virtual int numInitStages() const override;

        /**
         * @brief dummy synchronization function.
         *
         * @param msg Event of the scheduler that triggers the synchronization
         */
        virtual void handleMessage(cMessage *msg) override;
};
}

#endif
