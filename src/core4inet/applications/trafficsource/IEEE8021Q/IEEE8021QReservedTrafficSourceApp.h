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

#ifndef CORE4INET_IEEE8021QRESERVEDTRAFFICSOURCEAPP_H_
#define CORE4INET_IEEE8021QRESERVEDTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "core4inet/applications/trafficsource/IEEE8021Q/IEEE8021QTrafficSourceApp.h"

#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/base/avb/AVBDefs.h"
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/services/avb/SRP/SRPTable.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @brief IEEE802.1Q bandwidth reserved traffic source
 *
 * Generates and sends Q-tagged Ethernetframes based on a reserved bandwidth.
 *
 * @ingroup IEEE8021Q
 *
 * @author Timo Haeckel
 */
class IEEE8021QReservedTrafficSourceApp : public virtual IEEE8021QTrafficSourceApp, public virtual Timed, public virtual cListener
{
    protected:
        bool isStreaming;
        SR_CLASS srClass;
        unsigned long streamID;
        size_t frameSize;
        uint16_t intervalFrames;
        bool isStatic;

        SRPTable * srpTable;

    public:
        IEEE8021QReservedTrafficSourceApp();

    protected:
        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize() override;

        /**
         * @brief Handles message generation
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Schedule next send interval
         */
        virtual void scheduleInterval();

        /**
         * @brief Receives Stream Reservation Protocol signals
         */
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

        /**
         * @brief
         *
         * @return
         */
        virtual simtime_t getSendInterval();

};

} //namespace

#endif
