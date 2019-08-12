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

#ifndef CORE4INET_AVBTRAFFICSINK_H_
#define CORE4INET_AVBTRAFFICSINK_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/applications/trafficsink/base/TrafficSinkApp.h"
#include "core4inet/services/avb/SRP/SRPTable.h"

namespace CoRE4INET {

/**
 * @brief Traffic sink application used for statistics collection.
 *
 *
 * @sa ApplicationBase
 * @ingroup Applications
 *
 * @author Till Steinbach, Philipp Meyer
 */
class AVBTrafficSinkApp : public virtual TrafficSinkApp, public virtual cListener
{
    private:
        /**
         * @brief Caches srpTable module
         */
        SRPTable *srpTable;

        /**
         * @brief Caches vlan_id parameter
         */
        unsigned short vlan_id;

        /**
         * @brief Caches streamID parameter
         */
        uint64_t streamID;

        /**
         * @brief Caches updateInterval parameter
         */
        simtime_t updateInterval;

        /**
         * @brief Caches retryInterval parameter
         */
        simtime_t retryInterval;

        /**
         * @brief Caches isStatic parameter
         */
        bool isStatic;
    public:
        /**
         * @brief Constructor of AVBTrafficSinkApp
         */
        AVBTrafficSinkApp();
    protected:
        /**
         * @brief Initialization of the module.
         */
        virtual void initialize() override;

        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;

        /**
         * @brief handles self message for srp registration updates
         *
         * @param msg incoming message
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
