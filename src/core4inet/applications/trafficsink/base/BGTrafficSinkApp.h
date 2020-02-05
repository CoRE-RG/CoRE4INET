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

#ifndef CORE4INET_BGTRAFFICSINKAPP_H_
#define CORE4INET_BGTRAFFICSINKAPP_H_

//CoRE4INET
#include "core4inet/applications/trafficsink/base/TrafficSinkApp.h"
//INET
#include "inet/linklayer/common/MACAddress.h"

namespace CoRE4INET {

/**
 * @brief Traffic sink application used for statistics collection of best-effort traffic.
 *
 *
 * @sa TrafficSinkApp
 * @ingroup Applications
 *
 * @author Till Steinbach, Sandra Reider
 */
class BGTrafficSinkApp : public virtual TrafficSinkApp
{
    private:
        unsigned int received;
    public:
        BGTrafficSinkApp();
    protected:
        inet::MACAddress address;
        /**
         * @brief Initialization of the module.
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
         **/
        virtual void handleParameterChange(const char* parname) override;
};

} //namespace

#endif
