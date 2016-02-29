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

#ifndef CORE4INET_MULTITRAFFICSINKAPP_H_
#define CORE4INET_MULTITRAFFICSINKAPP_H_

//Std
#include <unordered_map>

//CoRE4INET
#include "core4inet/applications/base/ApplicationBase.h"

namespace CoRE4INET {

/**
 * @brief Traffic sink application used for statistics collection of multiple different virtual links.
 *
 *
 * @sa ApplicationBase
 * @ingroup Applications
 *
 * @author Till Steinbach
 */
class MultiTrafficSinkApp : public virtual ApplicationBase
{
    private:
        /**
         * Map of Signals that are emitted every time a frame with a specific CT-ID was sent.
         */
        static std::unordered_map<uint16_t, simsignal_t> rxPkSignal;

    protected:
        /**
         * @brief collects incoming message and writes statistics.
         *
         * @param msg incoming frame
         */
        virtual void handleMessage(cMessage *msg) override;
};

} //namespace

#endif
