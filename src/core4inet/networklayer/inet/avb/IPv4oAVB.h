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

#ifndef CORE4INET_IPV4OAVB_H_
#define CORE4INET_IPV4OAVB_H_

#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/networklayer/inet/base/IPv4oREBase.h"
#include "core4inet/buffer/base/Buffer.h"
#include "core4inet/incoming/avb/AVBIncoming.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
#include "core4inet/networklayer/inet/base/IPoREFilter.h"
#include "core4inet/base/IPoRE/IPoREDefs_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/networklayer/ipv4/IPv4.h"

namespace CoRE4INET {

template<class base>
class IPv4oAVB : public base {

    private:
        class UpdateListenerMsg : public cMessage {
            public:
                UpdateListenerMsg(const char *newName=nullptr, short kind=0)
                : cMessage(newName, kind)
                {
                    this->streamId = 0;
                    this->vlanId = 0;
                }
            public:
                uint64_t streamId;
                unsigned short vlanId;
        };


    protected:
        enum class MsgKind { START = 0xBEEF };


    public:
        IPv4oAVB();
        virtual ~IPv4oAVB();

    protected:
        virtual void initialize(int stage);
        virtual void sendPacketToNIC(cPacket *packet, const inet::InterfaceEntry *ie);
        virtual void configureFilters(cXMLElement *config);
        virtual void configureSubscriptions(cXMLElement *config);
        virtual void registerSrpCallbacks(SRPTable *srpTable);
        virtual void registerTalker(const std::list<IPoREFilter*> &filters, SRPTable *srpTable);
        virtual void registerTalker(const IPoREFilter* filter, SRPTable *srpTable);
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details);
        virtual void handleMessage(cMessage* msg);

        /**
         * Encapsulates packet in Ethernet II frame and sends to each destination buffers.
         * Destination MAC address and destination buffer is taken from filter.
         */
        virtual void sendPacketToBuffers(cPacket *packet, const inet::InterfaceEntry *ie, std::list<IPoREFilter*> &filters);

        /**
         * Encapsulates packet in AVB Frame and sends to destination AVB Buffer.
         * StreamID, Name, DestMAC, DestBuffer is taken from filter.
         */
        void sendAVBFrame(cPacket* packet, const inet::InterfaceEntry* ie, const IPoREFilter* filter);

    protected:
        std::list<int> m_subscribeList;
};







} /* namespace CoRE4INET */

#include "core4inet/networklayer/inet/avb/IPv4oAVB.cc"


#endif /* CORE4INET_IPV4OAVB_H_ */
