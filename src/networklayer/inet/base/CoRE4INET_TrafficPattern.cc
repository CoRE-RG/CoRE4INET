/*
 * CoRE4INET_TrafficPattern.cc
 *
 *  Created on: 09.09.2014
 *      Author: Kai-Uwe
 */

//==============================================================================

#include <CoRE4INET_TrafficPattern.h>

//==============================================================================

#include "IPvXAddress.h"
#include "IPvXAddressResolver.h"
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
    const IPv4Datagram *datagram = dynamic_cast<const IPv4Datagram*>(packet);
    if (!datagram)
        return false;


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
        const cPacket *encPacket = packet->getEncapsulatedPacket();
        const UDPPacket *udpPacket = dynamic_cast<const UDPPacket*>(encPacket);
        if (udpPacket)
        {
            srcPort = udpPacket->getSourcePort();
            destPort = udpPacket->getDestinationPort();
        }
        const TCPSegment *tcpSegment = dynamic_cast<const TCPSegment*>(encPacket);
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
