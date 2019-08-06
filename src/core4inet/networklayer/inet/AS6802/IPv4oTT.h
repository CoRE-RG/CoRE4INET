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

#include "core4inet/networklayer/inet/base/IPv4oREBase.h"

//Std
#include <unordered_map>

#include "core4inet/buffer/AS6802/CTBuffer.h"
#include "core4inet/networklayer/inet/AS6802/TTDestinationInfo.h"
#include "core4inet/networklayer/inet/AS6802/QueuedPacket.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

template<class Base>
class IPv4oTT : public Base {

protected:
    enum class MsgKind { START = 0xBEEF };

public:

    IPv4oTT();
    virtual ~IPv4oTT() override;

    virtual void initialize(int stage) override;
    virtual void sendPacketToNIC(cPacket *packet, const inet::InterfaceEntry *ie) override;
    virtual void configureFilters(cXMLElement *config) override;
    virtual void handleMessage(cMessage* msg) override;

    /**
     * Encapsulates packet in RC frame and sends to each destination buffers.
     */
    virtual void sendPacketToBuffers(cPacket *packet, const inet::InterfaceEntry *ie, std::list<IPoREFilter*> &filters) override;

    /**
     * Encapsulates packet in TT Frame and sends to destination Buffers.
     */
    void sendTTFrame(cPacket* packet, const IPoREFilter* filter);

    /**
     * Registers Timing events at the periods with the given actionTime for each filter.
     */
    virtual void registerSendTimingEvents(std::list<IPoREFilter*> &filters);

    /**
     * Registers a single timing event at the period with the given actionTime
     */
    virtual void registerSendTimingEvent(TTDestinationInfo *destInfo);

    /**
     * Handles synchronized events
     */
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj,  cObject *details) override;


protected:

    std::unordered_map<std::string, std::list<QueuedPacket*> > ttPackets;    ///< buffered outgoing packets for each TT filter
    std::unordered_map<std::string, Period *>                  periods;      ///< period module for each TT filter (period module is used for timing)
    bool                                                       synchronized; ///< node is synchronized with other TT nodes

};

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#include "core4inet/networklayer/inet/AS6802/IPv4oTT.cc"

//==============================================================================

#endif /* CORE4INET_IPV4OTT_H_ */
