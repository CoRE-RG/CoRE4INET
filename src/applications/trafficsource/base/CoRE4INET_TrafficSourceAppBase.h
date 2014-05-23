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

#ifndef __CORE4INET_TRAFFICSOURCEAPPBASE_H_
#define __CORE4INET_TRAFFICSOURCEAPPBASE_H_

#include "CoRE4INET_ApplicationBase.h"

namespace CoRE4INET {

#define START_MSG_NAME "Start Message"

/**
 * @brief Base class for a traffic generator application.
 *
 * @sa ApplicationBase
 * @ingroup Applications
 */
class TrafficSourceAppBase : public virtual ApplicationBase
{
    protected:
        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize();

};

} //namespace

#endif
