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

#ifndef CORE4INET_SYNCBASE_H_
#define CORE4INET_SYNCBASE_H_

//CoRE4INET
#include "core4inet/utilities/classes/Scheduled.h"
//Auto-generated Messages
#include "core4inet/synchronisation/base/SyncNotification_m.h"

namespace CoRE4INET {

/**
 * @brief Base for sync modules.
 *
 * @author Till Steinbach
 */
class SyncBase : public virtual Scheduled
{
    protected:
        using Scheduled::initialize;

        /**
         * @brief Initializes the module
         *
         * @param stage The stages. Module initializes when stage==0
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return Always returns 1
         */
        virtual int numInitStages() const override;

        /**
         * @brief Helper function to notify attached listeners about status change
         *
         * @param kind kind of status change
         */
        void notify(SyncNotificationKind kind);

        /**
         * Signal that is emitted every time a frame was sent.
         */
        static simsignal_t statusSignal;
};
}

#endif
