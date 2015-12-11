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

#ifndef CORE4INET_IPV4OIEEE8021Q_CC_
#define CORE4INET_IPV4OIEEE8021Q_CC_

#include "CoRE4INET_IPv4oIEEE8021Q.h"

#include "CoRE4INET_Defs.h"
#include "IPoREDefs_m.h"
#include "CoRE4INET_IEEE8021QDestinationInfo.h"
#include "CoRE4INET_BGBuffer.h"
#include "EtherFrameWithQTag_m.h"
#include "CoRE4INET_IPoREFilter.h"
#include "L3Address.h"
#include "L3AddressResolver.h"
#include "Ieee802Ctrl.h"
#include "UDPPacket.h"
#include "TCPSegment.h"
#include "omnetpp.h"


//==============================================================================

namespace CoRE4INET {

//==============================================================================

template<class Base>
IPv4oIEEE8021Q<Base>::IPv4oIEEE8021Q()
{
}

//==============================================================================

template<class Base>
IPv4oIEEE8021Q<Base>::~IPv4oIEEE8021Q()
{
}

//==============================================================================

template<class Base>
void IPv4oIEEE8021Q<Base>::initialize(int stage)
{
    Base::initialize(stage);
    if (stage == 0)
    {
        cXMLElement *filters = Base::par("filters").xmlValue();
        IPv4oIEEE8021Q<Base>::configureFilters(filters);
    }
}

//==============================================================================

template<class Base>
void IPv4oIEEE8021Q<Base>::sendPacketToNIC(cPacket *packet, const inet::InterfaceEntry *ie)
{
    // Check for matching filters
    std::list<IPoREFilter*> matchingFilters;
    bool filterMatch = Base::getMatchingFilters(packet, matchingFilters, DestinationType_8021Q);

    // TODO: if you want to send packages to different buffers (e.g. TT and AVB) you have to check for the "alsoBE" filter element and call base::sendPacketToNIC()
    // send to corresponding modules
    if (filterMatch)
    {
        IPv4oIEEE8021Q<Base>::sendPacketToBuffers(packet, ie, matchingFilters);
    }
    else
    {
        Base::sendPacketToNIC(packet, ie);
    }
}

//==============================================================================

template<class Base>
void IPv4oIEEE8021Q<Base>::configureFilters(cXMLElement *config)
{
    inet::L3AddressResolver addressResolver;
    cXMLElementList filterElements = config->getChildrenByTagName("filter");
    for (size_t i = 0; i < filterElements.size(); i++)
    {
        cXMLElement *filterElement = filterElements[i];
        try
        {
            const char *destType = Base::getRequiredAttribute(filterElement, "destType");

//            if (!this->destTypeEnum) {
//                this->destTypeEnum = cEnum::get("CoRE4INET::DestinationType");
//            }
//
//            DestinationType dt = DestinationType(this->destTypeEnum->lookup(destType));
            cEnum *destTypeEnum = cEnum::get("CoRE4INET::DestinationType");
            DestinationType dt = DestinationType(destTypeEnum->lookup(destType));

            if (dt == DestinationType_8021Q)
            {
                // Destination Info
                const char *destModules = Base::getRequiredAttribute(filterElement, "destModules");
                const char *vid = Base::getRequiredAttribute(filterElement, "VID");
                const char *pcp = Base::getRequiredAttribute(filterElement, "PCP");

                const char *destMAC = Base::getRequiredAttribute(filterElement, "destMAC");

                // Traffic Pattern
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

                // Fill destination info
                IEEE8021QDestinationInfo *ieee8021QDestInfo = new IEEE8021QDestinationInfo();
                ieee8021QDestInfo->setDestType(DestinationType_8021Q);
                std::vector<std::string> bufferPaths = cStringTokenizer(destModules, DELIMITERS).asVector();
                std::vector<std::string>::const_iterator bufferPath = bufferPaths.begin();
                std::list<BGBuffer*> destBgBuffers;
                for (; bufferPath != bufferPaths.end(); ++bufferPath)
                {
                    cModule* module = getSimulation()->getModuleByPath((*bufferPath).c_str());
                    if (!module)
                    {
                        module = findModuleWhereverInNode((*bufferPath).c_str(), this);
                    }
                    if (!module)
                    {
                        throw cRuntimeError("destModule \"%s\" could not be resolved!", (*bufferPath).c_str());
                    }
                    if (BGBuffer *bgBuf = dynamic_cast<BGBuffer*>(module))
                    {
                        destBgBuffers.push_back(bgBuf);
                    }
                    else
                    {
                        throw cRuntimeError("destModule: %s is not a BGBuffer!", (*bufferPath).c_str());
                    }
                }
                if (destMAC)
                    ieee8021QDestInfo->setDestMac(new inet::MACAddress(destMAC));
                else
                    throw cRuntimeError("destMAC not specified!");
                ieee8021QDestInfo->setDestModules(destBgBuffers);
                ieee8021QDestInfo->setVID(static_cast<uint16_t>(Base::parseIntAttribute(vid, "VID", false)));
                ieee8021QDestInfo->setPCP(static_cast<uint8_t>(Base::parseIntAttribute(pcp, "PCP", false)));

                // Fill traffic pattern
                TrafficPattern *tp = new TrafficPattern();
                if (srcAddrAttr)
                    tp->setSrcAddr(addressResolver.resolve(srcAddrAttr));
                if (srcPrefixLengthAttr)
                    tp->setSrcPrefixLength(Base::parseIntAttribute(srcPrefixLengthAttr, "srcPrefixLength"));
                else if (srcAddrAttr)
                    tp->setSrcPrefixLength(tp->getSrcAddr().getType() == inet::L3Address::IPv6 ? 128 : 32);
                if (destAddrAttr)
                    tp->setDestAddr(addressResolver.resolve(destAddrAttr));
                if (destPrefixLengthAttr)
                    tp->setDestPrefixLength(Base::parseIntAttribute(destPrefixLengthAttr, "destPrefixLength"));
                else if (destAddrAttr)
                    tp->setDestPrefixLength(tp->getDestAddr().getType() == inet::L3Address::IPv6 ? 128 : 32);
                if (protocolAttr)
                    tp->setProtocol(Base::parseProtocol(protocolAttr, "protocol"));
                if (tosAttr)
                    tp->setTos(Base::parseIntAttribute(tosAttr, "tos"));
                if (tosMaskAttr)
                    tp->setTosMask(Base::parseIntAttribute(tosAttr, "tosMask"));
                if (srcPortAttr)
                {
                    tp->setSrcPortMin(Base::parseIntAttribute(srcPortAttr, "srcPort"));
                    tp->setSrcPortMax(tp->getSrcPortMin());
                }
                if (srcPortMinAttr)
                    tp->setSrcPortMin(Base::parseIntAttribute(srcPortMinAttr, "srcPortMin"));
                if (srcPortMaxAttr)
                    tp->setSrcPortMax(Base::parseIntAttribute(srcPortMaxAttr, "srcPortMax"));
                if (destPortAttr)
                {
                    tp->setDestPortMin(Base::parseIntAttribute(destPortAttr, "destPort"));
                    tp->setDestPortMax(tp->getDestPortMin());
                }
                if (destPortMinAttr)
                    tp->setDestPortMin(Base::parseIntAttribute(destPortMinAttr, "destPortMin"));
                if (destPortMaxAttr)
                    tp->setDestPortMax(Base::parseIntAttribute(destPortMaxAttr, "destPortMax"));

                // Add filter
                IPoREFilter *filter = new IPoREFilter();
                filter->setDestInfo(ieee8021QDestInfo);
                filter->setTrafficPattern(tp);
                Base::addFilter(filter);
            }

        }
        catch (std::exception& e)
        {
            throw cRuntimeError("Error in XML <filter> element at %s: %s", filterElement->getSourceLocation(),
                    e.what());
        }
    }

}

//==============================================================================

template<class Base>
void IPv4oIEEE8021Q<Base>::handleMessage(cMessage* msg)
{
    if (dynamic_cast<EthernetIIFrameWithQTag*>(msg))
    {
        EthernetIIFrameWithQTag* qFrame = dynamic_cast<EthernetIIFrameWithQTag*>(msg);

        // decapsulate and send up
        cPacket* ipPacket = qFrame->decapsulate();
        inet::Ieee802Ctrl *etherctrl = new inet::Ieee802Ctrl();
        etherctrl->setSrc(qFrame->getSrc());
        etherctrl->setDest(qFrame->getDest());
        etherctrl->setEtherType(qFrame->getEtherType());
        ipPacket->setControlInfo(etherctrl);
#if OMNETPP_VERSION < 0x0500
        ipPacket->setArrival(this, Base::gate("In")->getId());
#else
        ipPacket->setArrival(this->getId(), Base::gate("In")->getId());
#endif

        delete qFrame;
        Base::handleMessage(ipPacket);
    }
    else
    {
        Base::handleMessage(msg);
    }
}

//==============================================================================

template<class Base>
void IPv4oIEEE8021Q<Base>::sendPacketToBuffers(cPacket *packet, const inet::InterfaceEntry *ie,
        std::list<IPoREFilter*> &filters)
{
    if (packet->getByteLength() > MAX_ETHERNET_DATA_BYTES)
        Base::error("packet from higher layer (%d bytes) exceeds maximum Ethernet payload length (%d)",
                packet->getByteLength(), MAX_ETHERNET_DATA_BYTES);

    typename std::list<IPoREFilter*>::iterator filter = filters.begin();
    for (; filter != filters.end(); ++filter)
    {
        if ((*filter)->getDestInfo()->getDestType() == DestinationType_8021Q)
        {
            sendIEEE8021QFrame(packet->dup(), ie, (*filter));
        }
    }

    delete packet;

}

//==============================================================================

template<class Base>
void IPv4oIEEE8021Q<Base>::sendIEEE8021QFrame(cPacket* packet, __attribute__((unused))  const inet::InterfaceEntry* ie,
        const IPoREFilter* filter)
{
    IEEE8021QDestinationInfo *destInfo = dynamic_cast<IEEE8021QDestinationInfo*>(filter->getDestInfo());
    if (!destInfo)
    {
        Base::error("Wrong Destination Info Type. Filter invalid!");
        return;
    }

    EthernetIIFrameWithQTag *outFrame = new EthernetIIFrameWithQTag();
    outFrame->encapsulate(packet);
    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
    {
        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    if (destInfo->getVID() > 0)
    {
        outFrame->setVID(destInfo->getVID());
    }
    if (destInfo->getPCP() > 0)
    {
        outFrame->setPcp(destInfo->getPCP());
    }
    outFrame->setDest(*destInfo->getDestMac());
    outFrame->setName(packet->getName());

    std::list<BGBuffer*> destBuffers = destInfo->getDestModules();
    std::list<BGBuffer*>::iterator destBuf = destBuffers.begin();
    for (; destBuf != destBuffers.end(); ++destBuf)
    {
        Base::sendDirect(outFrame, (*destBuf)->gate("in"));
    }

}

//==============================================================================

} /* namespace CoRE4INET */

#endif // CORE4INET_IPV4OIEEE8021Q_CC_

//==============================================================================
