/*
 * CoRE4INET_TrafficPattern.h
 *
 *  Created on: 09.09.2014
 *      Author: Kai-Uwe
 */

#ifndef CORE4INET_TRAFFICPATTERN_H_
#define CORE4INET_TRAFFICPATTERN_H_

#include "inet/networklayer/common/L3Address.h"

namespace CoRE4INET {

class TrafficPattern {

public:
    TrafficPattern();
    virtual ~TrafficPattern();

public:
    bool matches(const cPacket *packet);

public:
    const inet::L3Address& getDestAddr() const { return destAddr; }
    void setDestAddr(const inet::L3Address& new_destAddr) { this->destAddr = new_destAddr; }
    int getDestPortMax() const { return destPortMax; }
    void setDestPortMax(int new_destPortMax) { this->destPortMax = new_destPortMax; }
    int getDestPortMin() const { return destPortMin; }
    void setDestPortMin(int new_destPortMin) { this->destPortMin = new_destPortMin; }
    int getDestPrefixLength() const { return destPrefixLength; }
    void setDestPrefixLength(int new_destPrefixLength) { this->destPrefixLength = new_destPrefixLength; }
    int getProtocol() const { return protocol; }
    void setProtocol(int new_protocol) { this->protocol = new_protocol; }
    const inet::L3Address& getSrcAddr() const { return srcAddr; }
    void setSrcAddr(const inet::L3Address& new_srcAddr) { this->srcAddr = new_srcAddr; }
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
    inet::L3Address srcAddr;
    int srcPrefixLength;
    inet::L3Address destAddr;
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
