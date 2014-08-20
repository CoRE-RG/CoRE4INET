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

#include "networklayer/inet/CoRE4INET_IPv4oRE.h"

//==============================================================================

#include "CoRE4INET_Defs.h"
#include "CoRE4INET_Buffer.h"
#include "IPvXAddress.h"
#include "IPvXAddressResolver.h"
#include "DiffservUtil.h"
#include "UDPPacket.h"
#include "TCPSegment.h"
#include "cstringtokenizer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

Define_Module(IPv4oRE);

//==============================================================================

IPv4oRE::IPv4oRE() {
    // TODO Auto-generated constructor stub

}

//==============================================================================

IPv4oRE::~IPv4oRE() {
    // TODO Auto-generated destructor stub
}

//==============================================================================

void IPv4oRE::initialize(int stage) {
    IPv4::initialize(stage);
    if (stage == 3)
    {
        cXMLElement *config = par("filters").xmlValue();
        configureFilters(config);
    }
}

//==============================================================================

void IPv4oRE::sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie) {
    bool packetIsBE = true;

    // TODO: check for matching filters
    std::list<Filter*> matchingFilters;
    packetIsBE = !getMatchingFilters(packet, matchingFilters);

    if(packetIsBE) {
        IPv4::sendPacketToNIC(packet, ie);
    } else {
        sendPacketToBuffers(packet, ie, matchingFilters);
    }
}

//==============================================================================

void IPv4oRE::addFilter(const Filter &filter) {
    if (!filter.srcAddr.isUnspecified() && ((filter.srcAddr.isIPv6() && filter.srcPrefixLength > 128) ||
                                            (!filter.srcAddr.isIPv6() && filter.srcPrefixLength > 32)))
        throw cRuntimeError("srcPrefixLength is invalid");
    if (!filter.destAddr.isUnspecified() && ((filter.destAddr.isIPv6() && filter.destPrefixLength > 128) ||
                                             (!filter.destAddr.isIPv6() && filter.destPrefixLength > 32)))
        throw cRuntimeError("srcPrefixLength is invalid");
    if (filter.protocol != -1 && (filter.protocol < 0 || filter.protocol > 0xff))
        throw cRuntimeError("protocol is not a valid protocol number");
    if (filter.tos != -1 && (filter.tos < 0 || filter.tos > 0xff))
        throw cRuntimeError("tos is not valid");
    if (filter.tosMask < 0 || filter.tosMask > 0xff)
        throw cRuntimeError("tosMask is not valid");
    if (filter.srcPortMin != -1 && (filter.srcPortMin < 0 || filter.srcPortMin > 0xffff))
        throw cRuntimeError("srcPortMin is not a valid port number");
    if (filter.srcPortMax != -1 && (filter.srcPortMax < 0 || filter.srcPortMax > 0xffff))
        throw cRuntimeError("srcPortMax is not a valid port number");
    if (filter.srcPortMin != -1 && filter.srcPortMin > filter.srcPortMax)
        throw cRuntimeError("srcPortMin > srcPortMax");
    if (filter.destPortMin != -1 && (filter.destPortMin < 0 || filter.destPortMin > 0xffff))
        throw cRuntimeError("destPortMin is not a valid port number");
    if (filter.destPortMax != -1 && (filter.destPortMax < 0 || filter.destPortMax > 0xffff))
        throw cRuntimeError("destPortMax is not a valid port number");
    if (filter.destPortMin != -1 && filter.destPortMin > filter.destPortMax)
        throw cRuntimeError("destPortMin > destPortMax");

    m_filterList.push_back(filter);
}

//==============================================================================

void IPv4oRE::configureFilters(cXMLElement *config) {
    IPvXAddressResolver addressResolver;
    cXMLElementList filterElements = config->getChildrenByTagName("filter");
    for (int i = 0; i < (int)filterElements.size(); i++)
    {
        cXMLElement *filterElement = filterElements[i];
        try
        {
            const char *destBuf = getRequiredAttribute(filterElement, "destBuffer");
            const char *destMAC = getRequiredAttribute(filterElement, "destMAC");
            const char *srcAddrAttr = filterElement->getAttribute("srcAddress");
            const char *srcPrefixLengthAttr = filterElement->getAttribute("srcPrefixLength");
            const char *destAddrAttr = filterElement->getAttribute("destAddress");
            const char *destPrefixLengthAttr = filterElement->getAttribute("destPrefixLength");
            const char *protocolAttr = filterElement->getAttribute("protocol");
            const char *tosAttr = filterElement->getAttribute("tos");
            const char *tosMaskAttr = filterElement->getAttribute("tosMask");
            const char *srcPortAttr = filterElement->getAttribute("srcPort");
            const char *srcPortMinAttr = filterElement->getAttribute("srcPortMin");
            const char *srcPortMaxAttr = filterElement->getAttribute("srcPortMax");
            const char *destPortAttr = filterElement->getAttribute("destPort");
            const char *destPortMinAttr = filterElement->getAttribute("destPortMin");
            const char *destPortMaxAttr = filterElement->getAttribute("destPortMax");

            Filter filter;


            cModule* module = simulation.getModuleByPath(destBuf);
            if (!module) {
               module = findModuleWhereverInNode(destBuf, this);
            }
            if (!module) {
               throw cRuntimeError("Configuration problem of buffers: Module: %s could not be resolved!", destBuf);
            }
            if (Buffer *buffer = dynamic_cast<Buffer*>(module)) {
               filter.destBuffer = buffer;
            } else {
                throw cRuntimeError("Configuration problem of buffers: Module: %s is not a buffer!", destBuf);
            }
            if (destMAC)
                filter.destMAC.setAddress(destMAC);
            else
                throw cRuntimeError("Configuration problem: destMAC not specified!");
            if (srcAddrAttr)
                filter.srcAddr = addressResolver.resolve(srcAddrAttr);
            if (srcPrefixLengthAttr)
                filter.srcPrefixLength = parseIntAttribute(srcPrefixLengthAttr, "srcPrefixLength");
            else if (srcAddrAttr)
                filter.srcPrefixLength = filter.srcAddr.isIPv6() ? 128 : 32;
            if (destAddrAttr)
                filter.destAddr = addressResolver.resolve(destAddrAttr);
            if (destPrefixLengthAttr)
                filter.destPrefixLength = parseIntAttribute(destPrefixLengthAttr, "destPrefixLength");
            else if (destAddrAttr)
                filter.destPrefixLength = filter.destAddr.isIPv6() ? 128 : 32;
            if (protocolAttr)
                filter.protocol = parseProtocol(protocolAttr, "protocol");
            if (tosAttr)
                filter.tos = parseIntAttribute(tosAttr, "tos");
            if (tosMaskAttr)
                filter.tosMask = parseIntAttribute(tosAttr, "tosMask");
            if (srcPortAttr)
                filter.srcPortMin = filter.srcPortMax = parseIntAttribute(srcPortAttr, "srcPort");
            if (srcPortMinAttr)
                filter.srcPortMin = parseIntAttribute(srcPortMinAttr, "srcPortMin");
            if (srcPortMaxAttr)
                filter.srcPortMax = parseIntAttribute(srcPortMaxAttr, "srcPortMax");
            if (destPortAttr)
                filter.destPortMin = filter.destPortMax = parseIntAttribute(destPortAttr, "destPort");
            if (destPortMinAttr)
                filter.destPortMin = parseIntAttribute(destPortMinAttr, "destPortMin");
            if (destPortMaxAttr)
                filter.destPortMax = parseIntAttribute(destPortMaxAttr, "destPortMax");

            addFilter(filter);
        }
        catch (std::exception& e)
        {
            throw cRuntimeError("Error in XML <filter> element at %s: %s", filterElement->getSourceLocation(), e.what());
        }
    }
}

//==============================================================================

void IPv4oRE::sendPacketToBuffers(cPacket *packet, const InterfaceEntry *ie, std::list<Filter*> &filters) {

    if (packet->getByteLength() > MAX_ETHERNET_DATA_BYTES)
        error("packet from higher layer (%d bytes) exceeds maximum Ethernet payload length (%d)", (int)packet->getByteLength(), MAX_ETHERNET_DATA_BYTES);


    // create Ethernet II frame, fill it in from Ieee802Ctrl and encapsulate msg in it
    EV << "Encapsulating higher layer packet `" << packet->getName() <<"' for MAC\n";

    Ieee802Ctrl *etherctrl = check_and_cast<Ieee802Ctrl*>(packet->removeControlInfo());
    EthernetIIFrame *frame = new EthernetIIFrame(packet->getName());

    frame->setSrc(etherctrl->getSrc());  // if blank, will be filled in by MAC
    frame->setDest(etherctrl->getDest());
    frame->setEtherType(etherctrl->getEtherType());
    frame->setByteLength(ETHER_MAC_FRAME_BYTES);
    delete etherctrl;

    frame->encapsulate(packet);
    if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
        frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);  // "padding"

    std::list<Filter*>::iterator filter = filters.begin();
    EthernetIIFrame *sendFrame;
    for( ; filter != filters.end(); ++filter) {
        sendFrame = frame->dup();
        sendFrame->setDest((*filter)->destMAC);
        sendDirect(sendFrame, (*filter)->destBuffer->gate("in"));
    }
    delete frame;
}

//==============================================================================

const char *IPv4oRE::getRequiredAttribute(cXMLElement *element, const char *attrName)
{
    const char *attrValue = element->getAttribute(attrName);
    if (!attrValue)
        throw cRuntimeError("missing attribute '%s' from <%s> element", attrName, element->getTagName());
    return attrValue;
}

//==============================================================================

int IPv4oRE::parseIntAttribute(const char *attrValue, const char *attrName, bool isOptional)
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

    return (int)num;
}

//==============================================================================

int IPv4oRE::parseProtocol(const char *attrValue, const char *attrName)
{
    if (isEmpty(attrValue))
        return -1;
    if (isdigit(*attrValue))
        return parseIntAttribute(attrValue, attrName);
    if (!m_protocolEnum)
        m_protocolEnum = cEnum::get("IPProtocolId");
    char name[20];
    strcpy(name, "IP_PROT_");
    char *dest;
    for (dest = name+8; *attrValue; ++dest, ++attrValue)
        *dest = toupper(*attrValue);
    *dest = '\0';

    return m_protocolEnum->lookup(name);
}

//==============================================================================

bool IPv4oRE::getMatchingFilters(cPacket *packet, std::list<Filter*> &filters) {
    bool foundMatch = false;
    std::list<Filter>::iterator filter = m_filterList.begin();
    while(filter != m_filterList.end()) {
        if (filter->matches(packet)) {
            filters.push_back(&(*filter));
            foundMatch = true;
        }
        ++filter;
    }
    return foundMatch;
}

//==============================================================================

bool IPv4oRE::Filter::matches(cPacket *packet) {

    IPv4Datagram *datagram = check_and_cast<IPv4Datagram*>(packet);

    if (srcPrefixLength > 0 && (srcAddr.isIPv6() || !datagram->getSrcAddress().prefixMatches(srcAddr.get4(), srcPrefixLength)))
        return false;
    if (destPrefixLength > 0 && (destAddr.isIPv6() || !datagram->getDestAddress().prefixMatches(destAddr.get4(), destPrefixLength)))
        return false;
    if (protocol >= 0 && datagram->getTransportProtocol() != protocol)
        return false;
    if (tosMask != 0 && (tos & tosMask) != (datagram->getTypeOfService() & tosMask))
        return false;
    if (srcPortMin >= 0 || destPortMin >= 0)
    {
        int srcPort = -1, destPort = -1;
        cPacket *encPacket = packet->getEncapsulatedPacket();
        UDPPacket *udpPacket = dynamic_cast<UDPPacket*>(encPacket);
        if (udpPacket)
        {
            srcPort = udpPacket->getSourcePort();
            destPort = udpPacket->getDestinationPort();
        }
        TCPSegment *tcpSegment = dynamic_cast<TCPSegment*>(encPacket);
        if (tcpSegment)
        {
            srcPort = tcpSegment->getSrcPort();
            destPort = tcpSegment->getDestPort();
        }

        if (srcPortMin >= 0 && (srcPort < srcPortMin || srcPort > srcPortMax))
            return false;
        if (destPortMin >= 0 && (destPort < destPortMin || destPort > destPortMax))
            return false;
    }
    return true;
}

//==============================================================================

} /* namespace CoRE4INET */
