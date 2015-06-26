/*
 * CoRE4INET_TrafficPattern.cc
 *
 *  Created on: 09.09.2014
 *      Author: Kai-Uwe
 */

//==============================================================================

#include <CoRE4INET_TrafficPattern.h>

//==============================================================================

#include "L3Address.h"
#include "L3AddressResolver.h"
#include "IPv4Datagram.h"
#include "UDPPacket.h"
#include "TCPSegment.h"
#include "cstringtokenizer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

TrafficPattern::TrafficPattern()
  : srcAddr(),
    srcPrefixLength(-1),
    destAddr(),
    destPrefixLength(-1),
    protocol(-1),
    tos(-1),
    tosMask(0),
    srcPortMin(-1),
    srcPortMax(-1),
    destPortMin(-1),
    destPortMax(-1)
{
}

//==============================================================================

TrafficPattern::~TrafficPattern() {
}

//==============================================================================

bool TrafficPattern::matches(const cPacket *packet)
{
    const inet::IPv4Datagram *datagram = dynamic_cast<const inet::IPv4Datagram*>(packet);
    if (!datagram)
        return false;


    if (srcPrefixLength > 0 && ((srcAddr.getType()==inet::L3Address::IPv6) || !datagram->getSrcAddress().prefixMatches(srcAddr.toIPv4(), srcPrefixLength)))
        return false;
    if (destPrefixLength > 0 && ((destAddr.getType()==inet::L3Address::IPv6) || !datagram->getDestAddress().prefixMatches(destAddr.toIPv4(), destPrefixLength)))
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
            srcPort = udpPacket->getSourcePort();
            destPort = udpPacket->getDestinationPort();
        }
        const inet::tcp::TCPSegment *tcpSegment = dynamic_cast<const inet::tcp::TCPSegment*>(encPacket);
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

//==============================================================================
// EOF
