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

#ifndef __CORE4INET_IEEE8021QTRAFFICSINKAPP_H_
#define __CORE4INET_IEEE8021QTRAFFICSINKAPP_H_

#include <omnetpp.h>

#include "core4inet/applications/trafficsink/base/BGTrafficSinkApp.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class IEEE8021QTrafficSinkApp : public virtual BGTrafficSinkApp
{
private:
        /**
         * Signal that is emitted every time a frame was sent.
         */
        static simsignal_t rxPkQ0Signal;
        static simsignal_t rxPkQ1Signal;
        static simsignal_t rxPkQ2Signal;
        static simsignal_t rxPkQ3Signal;
        static simsignal_t rxPkQ4Signal;
        static simsignal_t rxPkQ5Signal;
        static simsignal_t rxPkQ6Signal;
        static simsignal_t rxPkQ7Signal;

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
