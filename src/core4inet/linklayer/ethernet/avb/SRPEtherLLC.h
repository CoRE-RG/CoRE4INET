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

#ifndef CORE4INET_SRPETHERLLC_H
#define CORE4INET_SRPETHERLLC_H

//CoRE4INET
#include "core4inet/linklayer/ethernet/base/BGEtherLLC.h"
//Auto-generated Messages
#include "core4inet/linklayer/ethernet/avb/SRPFrame_m.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief This module forwards frames based on their destination MAC addresses to appropriate ports.
 *
 * It can handle: AVBs SRP frames.
 * Incoming SRP frames are forwarded as SRP messages through srpOut to the SRProtocol module.
 * Outgoing SRP messages coming through srpIn gate are forwarded according to the controlInfo as EtherFrame
 *
 * @sa BGEtherLLC
 *
 * @author Till Steinbach
 */
class SRPEtherLLC : public BGEtherLLC
{
    protected:
        /**
         * @brief Handles incoming messages
         *
         * @param msg cMessage pointer
         */
        virtual void handleMessage(cMessage *msg) override;

    private:
        /**
         * @brief Forwards SRPFrame to outgoing Port
         *
         * @param srp SRPFrame pointer
         */
        void dispatchSRP(SRPFrame * srp);
        /**
         * @brief Delivers SRPFrame to SRProtocol module
         *
         * @param frame EtherFrame pointer
         */
        void deliverSRP(inet::EtherFrame * frame);
};

}
#endif
