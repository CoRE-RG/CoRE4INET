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

#ifndef __CORE4INET_BGTRAFFICHANDLE_H_
#define __CORE4INET_BGTRAFFICHANDLE_H_

#include <omnetpp.h>

namespace CoRE4INET {

/**
 * @brief Implements a standard ETHERAPP that sends and receives
 * best-effort Ethernet frames.
 *
 * To allow the sending of best-effort Ethernet frames through the
 * TTEthernet API this BGTrafficHandle forwards messages.
 *
 * @author Till Steinbach
 */
class BGTrafficHandle : public cSimpleModule
{
  protected:
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

} //namespace

#endif
