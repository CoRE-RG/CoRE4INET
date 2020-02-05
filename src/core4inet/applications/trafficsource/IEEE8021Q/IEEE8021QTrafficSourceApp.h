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

#ifndef CORE4INET_IEEE8021QTRAFFICSOURCEAPP_H_
#define CORE4INET_IEEE8021QTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "core4inet/applications/trafficsource/base/TrafficSourceAppBase.h"

//INET
#include "inet/linklayer/common/MACAddress.h"

namespace CoRE4INET {

/**
 * @brief Traffic generator application for traffic with IEEE 802.1q priorities.
 *
 * @sa TrafficSourceAppBase
 * @ingroup Applications
 *
 * @author Till Steinbach, Philipp Meyer
 */
class IEEE8021QTrafficSourceApp : public virtual TrafficSourceAppBase
{
    private:
        /**
         * @brief caches sendInterval parameter
         */
        simtime_t sendInterval;

        /**
         * @brief caches destAddress parameter
         */
        inet::MACAddress destAddress;

        /**
         * @brief caches priority parameter
         */
        uint8_t priority;
        /**
         * @brief caches vid parameter
         */
        uint16_t vid;

        /**
         * @brief Number of priorities.
         */
        unsigned int numPCP;

    public:
        /**
         * @brief Constructor of IEEE8021QTrafficSourceApp
         */
        IEEE8021QTrafficSourceApp();

    protected:
        /**
         * @brief Signals that are emitted when a frame is send.
         */
        std::vector<simsignal_t> txQPcpPkSignals;

        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize() override;

        /**
         * @brief handle self messages to send frames
         *
         *
         * @param msg incoming self messages
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Generates and sends a new Message.
         *
         * The message is sent to the buffer.
         * The size is defined by the payload parameter of the module.
         */
        virtual void sendMessage();

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
};

} //namespace

#endif
