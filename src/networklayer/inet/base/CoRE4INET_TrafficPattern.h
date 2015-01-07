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
    void setDestAddr(const IPvXAddress& new_destAddr) { this->destAddr = new_destAddr; }
    int getDestPortMax() const { return destPortMax; }
    void setDestPortMax(int new_destPortMax) { this->destPortMax = new_destPortMax; }
    int getDestPortMin() const { return destPortMin; }
    void setDestPortMin(int new_destPortMin) { this->destPortMin = new_destPortMin; }
    int getDestPrefixLength() const { return destPrefixLength; }
    void setDestPrefixLength(int new_destPrefixLength) { this->destPrefixLength = new_destPrefixLength; }
    int getProtocol() const { return protocol; }
    void setProtocol(int new_protocol) { this->protocol = new_protocol; }
    const IPvXAddress& getSrcAddr() const { return srcAddr; }
    void setSrcAddr(const IPvXAddress& new_srcAddr) { this->srcAddr = new_srcAddr; }
    int getSrcPortMax() const { return srcPortMax; }
    void setSrcPortMax(int new_srcPortMax) { this->srcPortMax = new_srcPortMax; }
    int getSrcPortMin() const { return srcPortMin; }
    void setSrcPortMin(int new_srcPortMin) { this->srcPortMin = new_srcPortMin; }
    int getSrcPrefixLength() const { return srcPrefixLength; }
    void setSrcPrefixLength(int new_srcPrefixLength) { this->srcPrefixLength = new_srcPrefixLength; }
    int getTos() const { return tos; }
    void setTos(int new_tos) { this->tos = new_tos; }
    int getTosMask() const { return tosMask; }
    void setTosMask(int new_tosMask) { this->tosMask = new_tosMask; }

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
