/*
 * CoRE4INET_TrafficPattern.h
 *
 *  Created on: 09.09.2014
 *      Author: Kai-Uwe
 */

#ifndef CORE4INET_TRAFFICPATTERN_H_
#define CORE4INET_TRAFFICPATTERN_H_


#include "IPvXAddress.h"
#include "csimplemodule.h"

namespace CoRE4INET {

class TrafficPattern {

public:
    TrafficPattern();
    virtual ~TrafficPattern();

public:
    bool matches(const cPacket *packet);

public:
    const IPvXAddress& getDestAddr() const { return destAddr; }
    void setDestAddr(const IPvXAddress& destAddr) { this->destAddr = destAddr; }
    int getDestPortMax() const { return destPortMax; }
    void setDestPortMax(int destPortMax) { this->destPortMax = destPortMax; }
    int getDestPortMin() const { return destPortMin; }
    void setDestPortMin(int destPortMin) { this->destPortMin = destPortMin; }
    int getDestPrefixLength() const { return destPrefixLength; }
    void setDestPrefixLength(int destPrefixLength) { this->destPrefixLength = destPrefixLength; }
    int getProtocol() const { return protocol; }
    void setProtocol(int protocol) { this->protocol = protocol; }
    const IPvXAddress& getSrcAddr() const { return srcAddr; }
    void setSrcAddr(const IPvXAddress& srcAddr) { this->srcAddr = srcAddr; }
    int getSrcPortMax() const { return srcPortMax; }
    void setSrcPortMax(int srcPortMax) { this->srcPortMax = srcPortMax; }
    int getSrcPortMin() const { return srcPortMin; }
    void setSrcPortMin(int srcPortMin) { this->srcPortMin = srcPortMin; }
    int getSrcPrefixLength() const { return srcPrefixLength; }
    void setSrcPrefixLength(int srcPrefixLength) { this->srcPrefixLength = srcPrefixLength; }
    int getTos() const { return tos; }
    void setTos(int tos) { this->tos = tos; }
    int getTosMask() const { return tosMask; }
    void setTosMask(int tosMask) { this->tosMask = tosMask; }

private:
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
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_TRAFFICPATTERN_H_ */
