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

//==============================================================================

#include "CoRE4INET_IPv4oREBase.h"

//==============================================================================

#include "CoRE4INET_Defs.h"
#include "CoRE4INET_Buffer.h"
#include "CoRE4INET_IPoREFilter.h"
#include "CoRE4INET_AVBDestinationInfo.h"
#include "IPoREDefs_m.h"
#include "AVBFrame_m.h"
#include "IPvXAddress.h"
#include "IPvXAddressResolver.h"
#include "UDPPacket.h"
#include "TCPSegment.h"
#include "cstringtokenizer.h"

#include <algorithm>

//==============================================================================

namespace CoRE4INET {

//==============================================================================

IPv4oREBase::IPv4oREBase()
{
    this->m_protocolEnum = cEnum::get("IPProtocolId");
}

//==============================================================================

IPv4oREBase::~IPv4oREBase()
{
    for(std::list<IPoREFilter*>::iterator i = m_filterList.begin(); i != m_filterList.end(); ++i){
        IPoREFilter * filter = (*i);
        delete filter;
    }
    m_filterList.clear();
}

//==============================================================================

void IPv4oREBase::addFilter(IPoREFilter *filter)
{
    TrafficPattern *tp = filter->getTrafficPattern();
    if (!tp->getSrcAddr().isUnspecified() && ((tp->getSrcAddr().isIPv6() && tp->getSrcPrefixLength() > 128) ||
                                            (!tp->getSrcAddr().isIPv6() && tp->getSrcPrefixLength() > 32)))
        throw cRuntimeError("srcPrefixLength is invalid");
    if (!tp->getDestAddr().isUnspecified() && ((tp->getDestAddr().isIPv6() && tp->getDestPrefixLength() > 128) ||
                                             (!tp->getDestAddr().isIPv6() && tp->getDestPrefixLength() > 32)))
        throw cRuntimeError("srcPrefixLength is invalid");
    if (tp->getProtocol() != -1 && (tp->getProtocol() < 0 || tp->getProtocol() > 0xff))
        throw cRuntimeError("protocol is not a valid protocol number");
    if (tp->getTos() != -1 && (tp->getTos() < 0 || tp->getTos() > 0xff))
        throw cRuntimeError("tos is not valid");
    if (tp->getTosMask() < 0 || tp->getTosMask() > 0xff)
        throw cRuntimeError("tosMask is not valid");
    if (tp->getSrcPortMin() != -1 && (tp->getSrcPortMin() < 0 || tp->getSrcPortMin() > 0xffff))
        throw cRuntimeError("srcPortMin is not a valid port number");
    if (tp->getSrcPortMax() != -1 && (tp->getSrcPortMax() < 0 || tp->getSrcPortMax() > 0xffff))
        throw cRuntimeError("srcPortMax is not a valid port number");
    if (tp->getSrcPortMin() != -1 && tp->getSrcPortMin() > tp->getSrcPortMax())
        throw cRuntimeError("srcPortMin > srcPortMax");
    if (tp->getDestPortMin() != -1 && (tp->getDestPortMin() < 0 || tp->getDestPortMin() > 0xffff))
        throw cRuntimeError("destPortMin is not a valid port number");
    if (tp->getDestPortMax() != -1 && (tp->getDestPortMax() < 0 || tp->getDestPortMax() > 0xffff))
        throw cRuntimeError("destPortMax is not a valid port number");
    if (tp->getDestPortMin() != -1 && tp->getDestPortMin() > tp->getDestPortMax())
        throw cRuntimeError("destPortMin > destPortMax");

    m_filterList.push_back(filter);
}

//==============================================================================

const char *IPv4oREBase::getRequiredAttribute(cXMLElement *element, const char *attrName)
{
    const char *attrValue = element->getAttribute(attrName);
    if (!attrValue)
        throw cRuntimeError("missing attribute '%s' from <%s> element", attrName, element->getTagName());
    return attrValue;
}

//==============================================================================

int IPv4oREBase::parseIntAttribute(const char *attrValue, const char *attrName, bool isOptional)
{
    if (isEmpty(attrValue))
    {
        if (isOptional)
            return -1;
        else
            throw cRuntimeError("missing %s attribute", attrName);
    }

    unsigned long num;
    char *endp;
    if (*attrValue == '0' && *(attrValue+1) == 'b') // 0b prefix for binary
        num = strtoul(attrValue+2, &endp, 2);
    else
        num = strtoul(attrValue, &endp, 0); // will handle hex/octal/decimal

    if (*endp != '\0')
        throw cRuntimeError("malformed %s attribute: %s", attrName, attrValue);

    if (num > INT_MAX)
        throw cRuntimeError("attribute %s is too large: %s", attrName, attrValue);

    return static_cast<int>(num);
}

//==============================================================================

int IPv4oREBase::parseProtocol(const char *attrValue, const char *attrName)
{
    if (isEmpty(attrValue))
        return -1;
    if (isdigit(*attrValue))
        return parseIntAttribute(attrValue, attrName);
    m_protocolEnum = cEnum::get("IPProtocolId");
    char name[20];
    strcpy(name, "IP_PROT_");
    char *dest;
    for (dest = name+8; *attrValue; ++dest, ++attrValue)
        *dest = static_cast<char>(toupper(*attrValue));
    *dest = '\0';

    return m_protocolEnum->lookup(name);
}

//==============================================================================

bool IPv4oREBase::getMatchingFilters(cPacket *packet, std::list<IPoREFilter*> &filters, DestinationType dt)
{
    bool foundMatch = false;
    typename std::list<IPoREFilter*>::iterator filter = m_filterList.begin();
    while(filter != m_filterList.end()) {
        if ((*filter)->getTrafficPattern()->matches(packet)  &&  ((*filter)->getDestInfo()->getDestType() == dt)) {
            filters.push_back((*filter));
            foundMatch = true;
        }
        ++filter;
    }
    return foundMatch;
}

//==============================================================================

std::list<IPoREFilter*> IPv4oREBase::getFilters(DestinationType destType)
{
    std::list<IPoREFilter*> result;
    std::list<IPoREFilter*>::iterator f = m_filterList.begin();
    for (  ; f != m_filterList.end(); ++f) {
        if ((*f)->getDestInfo()->getDestType() == destType)
            result.push_back(*f);
    }
    return result;
}

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================
