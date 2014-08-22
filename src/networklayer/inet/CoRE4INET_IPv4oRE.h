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
#include "IPvXAddress.h"

#include "csimplemodule.h"

namespace CoRE4INET {

class IPv4oRE : public IPv4 {

    public:
        enum DestinationType {
            DestType_invalid = 0,
            DestType_AVB
        };

        struct AVBInfo {
            CoRE4INET::AVBIncoming* destModule;
            MACAddress destMAC;
            uint64_t streamId;
        };

        struct Filter {
            IPvXAddress srcAddr;
            int srcPrefixLength;
            IPvXAddress destAddr;
            int destPrefixLength;
            int protocol;
            int tos;
            int tosMask;
            int srcPortMin;
            int srcPortMax;
            int destPortMin;
            int destPortMax;

            DestinationType destType;
            AVBInfo avbDestInfo;
            bool alsoBE;

            bool matches(cPacket *packet);
        };

    public:
        IPv4oRE();
        virtual ~IPv4oRE();

    protected:
        virtual void initialize(int stage);
        virtual void sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie);
        virtual void addFilter(const Filter &filter);
        virtual void configureFilters(cXMLElement *config);
        virtual void registerTalker(const std::list<Filter> filters);
        virtual void registerTalker(const Filter* filter);

        /**
         * Encapsulates packet in Ethernet II frame and sends to each destination buffers.
         * Destination MAC address and destination buffer is taken from filter.
         */
        virtual void sendPacketToBuffers(cPacket *packet, const InterfaceEntry *ie, std::list<Filter*> &filters);

        /**
         * Encapsulates packet in AVB Frame and sends to destination AVB Buffer.
         * StreamID, Name, DestMAC, DestBuffer is taken from filter.
         */
        void sendAVBFrame(cPacket* packet, const InterfaceEntry* ie, const Filter* filter);

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
        bool getMatchingFilters(cPacket *packet, std::list<Filter*> &filters);

    protected:
        std::list<Filter> m_filterList;
        cEnum *m_protocolEnum;
        cEnum *destTypeEnum;
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_IPV4RTADAPTER_H_ */
