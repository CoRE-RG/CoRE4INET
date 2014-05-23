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

#ifndef __CORE4INET_AVBTRAFFICSINK_H_
#define __CORE4INET_AVBTRAFFICSINK_H_

#include "CoRE4INET_TrafficSinkApp.h"
#include "clistener.h"

namespace CoRE4INET {

/**
 * @brief Traffic sink application used for statistics collection.
 *
 *
 * @sa ApplicationBase
 * @ingroup Applications
 *
 * @author Till Steinbach
 */
class AVBTrafficSinkApp : public TrafficSinkApp, public cListener
{
    protected:
        /**
         * @brief Initialization of the module.
         */
        virtual void initialize();

        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
        /**
         * @brief handles self message for srp registration updates
         *
         * @param msg incoming message
         */
        virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif