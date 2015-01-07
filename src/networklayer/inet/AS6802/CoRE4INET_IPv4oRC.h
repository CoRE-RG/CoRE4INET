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

#include "CoRE4INET_IPv4oREBase.h"

#include "CoRE4INET_CTBuffer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

template<class Base>
class IPv4oRC : public Base {


public:

    IPv4oRC();
    virtual ~IPv4oRC();

    virtual void initialize(int stage) override;
    virtual void sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie);
    virtual void configureFilters(cXMLElement *config);
    virtual void handleMessage(cMessage* msg) override;

    /**
     * Encapsulates packet in RC frame and sends to each destination buffers.
     */
    virtual void sendPacketToBuffers(cPacket *packet, const InterfaceEntry *ie, std::list<IPoREFilter*> &filters);

    /**
     * Encapsulates packet in RC Frame and sends to destination Buffers.
     */
    void sendRCFrame(cPacket* packet, const InterfaceEntry* ie, const IPoREFilter* filter);


};

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#include "CoRE4INET_IPv4oRC.cc"

//==============================================================================

#endif /* CORE4INET_IPV4ORC_H_ */
