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

#ifndef CORE4INET_SRPRELAY_H_
#define CORE4INET_SRPRELAY_H_

//INET
#include "inet/linklayer/ieee8021d/relay/Ieee8021dRelay.h"
#include "inet/linklayer/ethernet/EtherFrame.h"
//Auto-generated Messages
#include "core4inet/linklayer/ethernet/avb/SRPFrame_m.h"

namespace CoRE4INET {

/**
 * @brief This module forwards frames (~inet::EtherFrame) based on their destination MAC addresses to appropriate ports.
 *
 * It can handle: AVBs SRP frames.
 * Incoming SRP frames are forwarded as SRP messages through srpOut to the SRProtocol module.
 * Outgoing SRP messages coming through srpIn gate are forwarded according to the controlInfo as inet::EtherFrame
 *
 * @see Ieee8021dRelay, SRProtocol
 *
 * @author Till Steinbach
 */
class SRPRelay : public virtual inet::Ieee8021dRelay
{

    protected:
        /**
         * Module initialization, only requires 1 stage
         */
        virtual void initialize(int stage) override;
        /**
         * @brief Number of initialization stages, at least 1!
         *
         * @return at least 1, more when parent moduile requires more stages.
         */
        virtual int numInitStages() const override
        {
            return 1 > inet::Ieee8021dRelay::numInitStages() ? 1 : inet::Ieee8021dRelay::numInitStages();
        }

        /**
         *
         */
        virtual void handleMessage(cMessage * msg) override;
    private:
        void dispatchSRP(SRPFrame * srp);

        void deliverSRP(inet::EtherFrame * frame);

};

}
#endif
