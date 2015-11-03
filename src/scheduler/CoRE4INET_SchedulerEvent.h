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

#ifndef CORE4INET_SCHEDULEREVENT_H_
#define CORE4INET_SCHEDULEREVENT_H_

//Auto-generated Messages
#include "scheduler/SchedulerMessage_m.h"

namespace CoRE4INET {

/**
 * @brief Redefines SchedulerEvent_Base and adds destinationGate
 *
 * @author Till Steinbach
 */
class SchedulerEvent : public SchedulerEvent_Base
{
    private:
        /**
         * @brief Target gate for SchedulerEvent
         */
        cGate *destinationGate_var;

    public:
        /**
         * @brief Constructor
         *
         * @param name name of the message
         * @param kind type of the message
         */
        SchedulerEvent(const char *name = nullptr, short kind = 0) :
                SchedulerEvent_Base(name, kind)
        {
            destinationGate_var = nullptr;
        }

        /**
         * @brief Copy constructor
         */
        SchedulerEvent(const SchedulerEvent& other) :
                SchedulerEvent_Base(other.getName())
        {
            operator=(other);
        }

        /**
         * @brief Assignment operator
         */
        SchedulerEvent& operator=(const SchedulerEvent& other)
        {
            SchedulerEvent_Base::operator=(other);
            return *this;
        }

        /**
         * @brief Duplication of SchedulerEvent message
         */
        virtual SchedulerEvent *dup() const
        {
            return new SchedulerEvent(*this);
        }

        // ADD CODE HERE to redefine and implement pure virtual functions from SchedulerEvent_Base

        /**
         * @brief Get target gate for SchedulerEvent
         *
         * @return cGate pointer
         */
        virtual cGate* getDestinationGate() const;

        /*
         * @brief Set target gate for SchedulerEvent
         *
         * @param new_destinationGate_var cGate pointer
         */
        virtual void setDestinationGate(cGate *new_destinationGate_var);
};
}

#endif
