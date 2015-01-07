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

#include "IPv4.h"
#include "CoRE4INET_IPv4oREBase.h"
#include "CoRE4INET_Buffer.h"
#include "CoRE4INET_AVBIncoming.h"
#include "CoRE4INET_SRPTable.h"
#include "CoRE4INET_IPoREFilter.h"
#include "IPvXAddress.h"
#include "IPoREDefs_m.h"

#include "csimplemodule.h"

namespace CoRE4INET {

template<class base>
class IPv4oAVB : public base {

    private:
        class UpdateListenerMsg : public cMessage {
            public:
                UpdateListenerMsg(const char *name=nullptr, short kind=0)
                : cMessage(name, kind)
                {
                    this->streamId = 0;
                    this->vlanId = 0;
                }
            public:
                uint64_t streamId;
                unsigned short vlanId;
        };


    protected:
        enum MsgKind { MSGKIND_START = 0xBEEF };


    public:
        IPv4oAVB();
        virtual ~IPv4oAVB();

    protected:
        virtual void initialize(int stage);
        virtual void sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie);
        virtual void configureFilters(cXMLElement *config);
        virtual void configureSubscriptions(cXMLElement *config);
        virtual void registerSrpCallbacks(SRPTable *srpTable);
        virtual void registerTalker(const std::list<IPoREFilter*> filters, SRPTable *srpTable);
        virtual void registerTalker(const IPoREFilter* filter, SRPTable *srpTable);
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
        virtual void handleMessage(cMessage* msg);

        /**
         * Encapsulates packet in Ethernet II frame and sends to each destination buffers.
         * Destination MAC address and destination buffer is taken from filter.
         */
        virtual void sendPacketToBuffers(cPacket *packet, const InterfaceEntry *ie, std::list<IPoREFilter*> &filters);

        /**
         * Encapsulates packet in AVB Frame and sends to destination AVB Buffer.
         * StreamID, Name, DestMAC, DestBuffer is taken from filter.
         */
        void sendAVBFrame(cPacket* packet, const InterfaceEntry* ie, const IPoREFilter* filter);

    protected:
        std::list<int> m_subscribeList;
};







} /* namespace CoRE4INET */

#include "CoRE4INET_IPv4oAVB.cc"

#endif /* CORE4INET_IPV4OAVB_H_ */
