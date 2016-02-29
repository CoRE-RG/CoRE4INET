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

#ifndef CORE4INET_NOSYNC_H_
#define CORE4INET_NOSYNC_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
//Auto-generated Messages
#include "core4inet/synchronisation/base/SyncNotification_m.h"

namespace CoRE4INET {

using namespace omnetpp;

/**
 * @brief No sync module.
 *
 * This module does not correct the clock
 *
 * @author Till Steinbach
 */
class NoSync : public virtual cSimpleModule
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
