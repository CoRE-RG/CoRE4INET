/*
 * CoRE4INET_TrafficPattern.cc
 *
 *  Created on: 09.09.2014
 *      Author: Kai-Uwe
 */

//==============================================================================
#include "core4inet/networklayer/inet/base/TrafficPattern.h"

//==============================================================================

#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/ipv4/IPv4Datagram.h"
#include "inet/transportlayer/udp/UDPPacket.h"
#include "inet/transportlayer/tcp_common/TCPSegment.h"
#include "inet/transportlayer/sctp/SCTPMessage.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

TrafficPattern::TrafficPattern() :
        srcAddr(), srcPrefixLength(-1), destAddr(), destPrefixLength(-1), protocol(-1), tos(-1), tosMask(0), srcPortMin(
                -1), srcPortMax(-1), destPortMin(-1), destPortMax(-1)
{
}

//==============================================================================

TrafficPattern::~TrafficPattern()
{
}

//==============================================================================

bool TrafficPattern::matches(const cPacket *packet)
{
    const inet::IPv4Datagram *datagram = dynamic_cast<const inet::IPv4Datagram*>(packet);
    if (!datagram)
        return false;

    if (srcPrefixLength > 0
            && ((srcAddr.getType() == inet::L3Address::IPv6)
                    || !datagram->getSrcAddress().prefixMatches(srcAddr.toIPv4(), srcPrefixLength)))
        return false;
    if (destPrefixLength > 0
            && ((destAddr.getType() == inet::L3Address::IPv6)
                    || !datagram->getDestAddress().prefixMatches(destAddr.toIPv4(), destPrefixLength)))
        return false;
    if (protocol >= 0 && datagram->getTransportProtocol() != protocol)
        return false;
    if (tosMask != 0 && (tos & tosMask) != (datagram->getTypeOfService() & tosMask))
        return false;
    if (srcPortMin >= 0 || destPortMin >= 0)
    {
        int srcPort = -1, destPort = -1;
        const cPacket *encPacket = packet->getEncapsulatedPacket();
        const inet::UDPPacket *udpPacket = dynamic_cast<const inet::UDPPacket*>(encPacket);
        if (udpPacket)
        {
            srcPort = static_cast<int>(udpPacket->getSourcePort());
            destPort = static_cast<int>(udpPacket->getDestinationPort());
        }
        const inet::tcp::TCPSegment *tcpSegment = dynamic_cast<const inet::tcp::TCPSegment*>(encPacket);
        if (tcpSegment)
        {
            srcPort = tcpSegment->getSrcPort();
            destPort = tcpSegment->getDestPort();
        }
        const inet::sctp::SCTPMessage *sctpPacket = dynamic_cast<const inet::sctp::SCTPMessage*>(encPacket);
        if (sctpPacket)
        {
            srcPort = static_cast<int>(sctpPacket->getSrcPort());
            destPort = static_cast<int>(sctpPacket->getDestPort());
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

//==============================================================================
// EOF
