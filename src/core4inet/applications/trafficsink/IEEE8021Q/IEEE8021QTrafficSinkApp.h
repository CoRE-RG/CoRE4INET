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
 * @brief Traffic sink application used for statistics collection of traffic with q-priorities.
 *
 *
 * @sa BGTrafficSinkApp
 * @ingroup Applications
 *
 * @author Sandra Reider, Mohammad Fazel Soltani
 */
class IEEE8021QTrafficSinkApp : public virtual BGTrafficSinkApp
{
    private:
        /**
         * @brief vlan id.
         */
        uint16_t vid;
        /**
         * @brief Number of priorities.
         */
        unsigned int numPCP;

    protected:
        /**
         * @brief Signals that are emitted when a frame is received.
         */
        std::vector<simsignal_t> rxQPcpPkSignals;

        /**
         * @brief Signals that are emitted when a frame is received.
         */
        std::vector<simsignal_t> rxQPcpPkAgeSignals;

        /**
         * @brief Signals that are emitted when a frame is received.
         */
        std::vector<simsignal_t> rxQPcpPkAgeInnerSignals;

        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize() override;

        /**
         * @brief collects incoming message and writes statistics.
         *
         * @param msg incoming frame
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
};

} //namespace

#endif
