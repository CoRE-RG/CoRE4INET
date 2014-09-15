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

#ifndef CORE4INET_IPV4RTADAPTER_H_
#define CORE4INET_IPV4RTADAPTER_H_

#include "IPv4.h"

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

    public:
        IPv4oAVB();
        virtual ~IPv4oAVB();

    protected:
        virtual void initialize(int stage);
        virtual void sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie);
        virtual void addFilter(const IPoREFilter &filter);
        virtual void configureFilters(cXMLElement *config);
        virtual void configureSubscriptions(cXMLElement *config);
        virtual void registerSrpCallbacks(SRPTable *srpTable);
        virtual void registerTalker(const std::list<IPoREFilter> filters, SRPTable *srpTable);
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

        /**
         * Returns true, if the string is empty (NULL or "");
         */
        inline bool isEmpty(const char *str) { return !str || !(*str); }

        /**
        * Returns the value of the named attribute of the XML element,
        * or throws an exception if not found.
        */
        const char *getRequiredAttribute(cXMLElement *element, const char *attrName);

        /**
        * Parses an integer attribute.
        * Supports decimal, octal ("0" prefix), hexadecimal ("0x" prefix), and binary ("0b" prefix) bases.
        */
        int parseIntAttribute(const char *attrValue, const char *attrName, bool isOptional = true);

        /**
        * Parses an IP protocol number.
        * Recognizes the names defined in IPProtocolId.msg (e.g. "UDP", "udp", "Tcp"),
        * and accepts decimal/octal/hex/binary numbers.
        */
        int parseProtocol(const char *attrValue, const char *attrName);

        /**
         * Gets matching filters for given packet.
         * Multiple filters can be returned in case of multiple matching filters.
         */
        bool getMatchingFilters(cPacket *packet, std::list<IPoREFilter*> &filters);

    protected:
        std::list<IPoREFilter> m_filterList;
        std::list<int> m_subscribeList;
        cEnum *m_protocolEnum;
        cEnum *destTypeEnum;
        bool filterValid;
};







} /* namespace CoRE4INET */

#include "CoRE4INET_IPv4oAVB.impl"

#endif /* CORE4INET_IPV4RTADAPTER_H_ */
