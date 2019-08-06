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

#ifndef CORE4INET_IPV4ORC_H_
#define CORE4INET_IPV4ORC_H_

//==============================================================================

#include "core4inet/networklayer/inet/base/IPv4oREBase.h"

#include "core4inet/buffer/AS6802/CTBuffer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

template<class Base>
class IPv4oRC : public Base {


public:

    IPv4oRC();
    virtual ~IPv4oRC() override;

    virtual void initialize(int stage) override;
    virtual void sendPacketToNIC(cPacket *packet, const inet::InterfaceEntry *ie) override;
    virtual void configureFilters(cXMLElement *config) override;
    virtual void handleMessage(cMessage* msg) override;

    /**
     * Encapsulates packet in RC frame and sends to each destination buffers.
     */
    virtual void sendPacketToBuffers(cPacket *packet, const inet::InterfaceEntry *ie, std::list<IPoREFilter*> &filters) override;

    /**
     * Encapsulates packet in RC Frame and sends to destination Buffers.
     */
    void sendRCFrame(cPacket* packet, const inet::InterfaceEntry* ie, const IPoREFilter* filter);


};

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#include "core4inet/networklayer/inet/AS6802/IPv4oRC.cc"

//==============================================================================

#endif /* CORE4INET_IPV4ORC_H_ */
