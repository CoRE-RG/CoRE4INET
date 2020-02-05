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

#ifndef CORE4INET_IEEE8021QBURSTTRAFFICAPP_H_
#define CORE4INET_IEEE8021QBURSTTRAFFICAPP_H_

//CoRE4INET
#include "core4inet/applications/trafficsource/base/BGBurstTrafficSourceApp.h"

namespace CoRE4INET {

/**
 * @brief Traffic generator application for traffic with IEEE 802.1q priorities.
 *
 * @sa BGBurstTrafficSourceApp
 * @ingroup Applications
 *
 * @author Philipp Meyer
 */
class IEEE8021QBurstTrafficSourceApp: public virtual BGBurstTrafficSourceApp
{
    private:
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
         * @brief Constructor of IEEE8021QBurstTrafficSourceApp
         */
        IEEE8021QBurstTrafficSourceApp();

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
         * @brief Generates and sends a new Message.
         *
         * The message is sent to the bgbuffer.
         * The size is defined by the payload parameter of the module.
         */
        virtual void sendMessage() override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_IEEE8021QBURSTTRAFFICAPP_H_ */
