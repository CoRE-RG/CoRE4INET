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

#ifndef CORE4INET_IPV4OREBASE_H_
#define CORE4INET_IPV4OREBASE_H_

#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/buffer/base/Buffer.h"
#include "core4inet/networklayer/inet/base/IPoREFilter.h"
#include "core4inet/base/IPoRE/IPoREDefs_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/networklayer/ipv4/IPv4.h"

namespace CoRE4INET {

class IPv4oREBase : public inet::IPv4 {

    public:
        IPv4oREBase();
        virtual ~IPv4oREBase();

    public:

        /**
         * Adds the filter to the internal filter list if filter is valid.
         */
        virtual void addFilter(IPoREFilter *filter);

        /**
         * Returns true, if the string is empty (nullptr or "");
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
        bool getMatchingFilters(cPacket *packet, std::list<IPoREFilter*> &filters, DestinationType dt);

        /**
         * Returns a list of all filters for a given destination type.
         */
        std::list<IPoREFilter*> getFilters(DestinationType destType);

    protected:

        virtual void handleMessage(cMessage* msg);

        std::list<IPoREFilter*> m_filterList;
        cEnum *m_protocolEnum;
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_IPV4OREBASE_H_ */
