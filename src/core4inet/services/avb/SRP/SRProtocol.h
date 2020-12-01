//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CORE4INET_SRPROTOCOL_H_
#define CORE4INET_SRPROTOCOL_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

/**
 * @brief This module handles the Stream Reservation Protocol
 *
 * See the NED definition for details.
 *
 * @author Till Steinbach, Philipp Meyer
 */
class SRProtocol : public virtual cSimpleModule, public cListener
{
    protected:
        /**
         * @brief Module representing the srpTable
         */
        SRPTable *srpTable;
        /**
         * @brief PCP value representing SRClass A
         */
        uint8_t pcpSRClassA;
        /**
         * @brief PCP value representing SRClass B
         */
        uint8_t pcpSRClassB;
        /**
         * @brief PriortyAndRank of SRClass A
         */
        uint8_t priortyAndRankSRClassA;
        /**
         * @brief PriortyAndRank of SRClass B
         */
        uint8_t priortyAndRankSRClassB;

    public:
        /**
         * @brief Constructor
         */
        SRProtocol();

    protected:
        /**
         * @brief Initialization, retrieves srpTable module and registers for signals
         */
        virtual void initialize() override;
        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
        /**
         * @brief handles incoming SRP Messages
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;
        /**
         * @brief handles signals containing srpTable changes
         *
         * @param src src module (srpTable)
         * @param id signal id
         * @param obj the related entry in the table
         */
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
};

} /* namespace CoRE4INET */
#endif
