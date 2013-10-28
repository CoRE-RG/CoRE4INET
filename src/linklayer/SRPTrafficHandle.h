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

#ifndef SRPTRAFFICHANDLE_H_
#define SRPTRAFFICHANDLE_H_

#include "BGTrafficHandle.h"
#include "MACAddress.h"

namespace TTEthernetModel {

/**
 * @brief Implements a standard ETHERAPP that sends and receives
 * best-effort Ethernet frames and identifies SRP frames for seperate queueing.
 *
 * @sa BGTrafficHandle
 */
class SRPTrafficHandle : public BGTrafficHandle
{
    protected:
        int localSAP;
        int remoteSAP;
        MACAddress destMACAddressUnicast;
        MACAddress destMACAddressBroadcast;
        MACAddress srcMACAddress;

        /**
         * @brief In initialization the handle sends a register_DSAP message
         * to register itself at the LLC
         */
        virtual void initialize();

        /**
         * @brief Messages are transferred between lower and upper layer.
         *
         * For outgoing messages Ssap and Dsap are set.
         *
         * @param msg incoming messages
         */
        virtual void handleMessage(cMessage *msg);
};

} /* namespace TTEthernetModel */
#endif /* SRPTRAFFICHANDLE_H_ */
