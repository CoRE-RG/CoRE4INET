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

#ifndef CORE4INET_AVBINCOMING_H_
#define CORE4INET_AVBINCOMING_H_

//CoRE4INET
#include "core4inet/incoming/base/Incoming.h"
#include "core4inet/services/avb/SRP/SRPTable.h"

namespace CoRE4INET {

//This disables the padding warning for this class! please recheck when adding new members!
#pragma GCC diagnostic ignored "-Wpadded"

/**
 * @brief Class for the critical traffic conformance check of
 * audio-video bridging traffic.
 *
 * @sa Incoming
 *
 * @author Philipp Meyer
 */
class AVBIncoming : public Incoming
{
    protected:
        /**
         * @brief Caches srpTable module
         */
        SRPTable *srptable;

    public:
        /**
         * @brief Constructor.
         */
        AVBIncoming();

    protected:
        /**
         * @brief Initialization of the module
         */
        virtual void initialize() override;

        /**
         * @brief Forwards messages arriving on in-gate to out-gate.
         *
         * @param msg the incoming message.
         */
        virtual void handleMessage(cMessage *msg) override;
};

} /* namespace CoRE4INET */
#endif /* CORE4INET_AVBINCOMING_H_ */
