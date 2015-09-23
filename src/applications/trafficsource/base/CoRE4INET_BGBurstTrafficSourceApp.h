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

#ifndef CORE4INET_BGBURSTTRAFFICSOURCEAPP_H_
#define CORE4INET_BGBURSTTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "CoRE4INET_BGTrafficSourceApp.h"

namespace CoRE4INET {

/**
 * @brief Traffic generator application for best-effor traffic.
 *
 * @sa TrafficSourceAppBase
 * @ingroup Applications
 */
class BGBurstTrafficSourceApp : public virtual BGTrafficSourceApp
{
    private:
        /**
         * @brief caches burstSize parameter
         */
        unsigned long burstSize;

    public:
        /**
         * @brief Constructor of BGTrafficSourceApp
         */
        BGBurstTrafficSourceApp();
    protected:

        /**
         * @brief Generates and sends a new Message.
         *
         * The message is sent to the buffer with the ct_id defined in parameter ct_id of the module.
         * The message kind is defined by the buffer-type (RC/TT) of the buffer the message is sent to.
         * The size is defined by the payload parameter of the module.
         */
        virtual void sendMessage() override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         *         */
        virtual void handleParameterChange(const char* parname) override;

        unsigned long getBurstSize();
};

} //namespace

#endif
