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

#ifndef CORE4INET_IPV4OTT_H_
#define CORE4INET_IPV4OTT_H_

//==============================================================================

#include "CoRE4INET_IPv4oREBase.h"
#if __cplusplus >= 201103L
#include <unordered_map>
using namespace std;
#else
#include <tr1/unordered_map>
using namespace std::tr1;
#endif
#include "CoRE4INET_CTBuffer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

template<class Base>
class IPv4oTT : public Base {


public:

    IPv4oTT();
    virtual ~IPv4oTT();

    virtual void initialize(int stage);
    virtual void sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie);
    virtual void configureFilters(cXMLElement *config);
    virtual void handleMessage(cMessage* msg);

    /**
     * Encapsulates packet in RC frame and sends to each destination buffers.
     */
    virtual void sendPacketToBuffers(cPacket *packet, const InterfaceEntry *ie, std::list<IPoREFilter*> &filters);

    /**
     * Encapsulates packet in TT Frame and sends to destination Buffers.
     */
    void sendTTFrame(cPacket* packet, const InterfaceEntry* ie, const IPoREFilter* filter);


};

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#include "CoRE4INET_IPv4oTT.cc"

//==============================================================================

#endif /* CORE4INET_IPV4OTT_H_ */
