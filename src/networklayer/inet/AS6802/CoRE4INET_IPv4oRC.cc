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


#ifndef CORE4INET_IPV4ORC_CC_
#define CORE4INET_IPV4ORC_CC_

//==============================================================================

#include "CoRE4INET_IPv4oRC.h"

#include "CoRE4INET_Defs.h"
#include "IPoREDefs_m.h"
#include "RCFrame_m.h"
#include "CoRE4INET_RCDestinationInfo.h"
#include "CoRE4INET_RCBuffer.h"
#include "CoRE4INET_IPoREFilter.h"
#include "CoRE4INET_Incoming.h"
#include "IPvXAddress.h"
#include "IPvXAddressResolver.h"
#include "UDPPacket.h"
#include "TCPSegment.h"
#include "cstringtokenizer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

template<class Base>
IPv4oRC<Base>::IPv4oRC() {
}

//==============================================================================

template<class Base>
IPv4oRC<Base>::~IPv4oRC() {
}

//==============================================================================

template<class Base>
void IPv4oRC<Base>::initialize(int stage)
{
    Base::initialize(stage);
    if (stage == 0)
    {
        cXMLElement *filters = Base::par("filters").xmlValue();
        IPv4oRC<Base>::configureFilters(filters);
    }
}

//==============================================================================

template<class Base>
void IPv4oRC<Base>::sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie)
{
    // Check for matching filters
    std::list<IPoREFilter*> matchingFilters;
    bool filterMatch = Base::getMatchingFilters(packet, matchingFilters, DestinationType_RC);

    // TODO: if you want to send packages to different buffers (e.g. TT and AVB) you have to check for the "alsoBE" filter element and call base::sendPacketToNIC()
    // send to corresponding modules
    if(filterMatch) {
        IPv4oRC<Base>::sendPacketToBuffers(packet, ie, matchingFilters);
    } else {
        Base::sendPacketToNIC(packet, ie);
    }
}

//==============================================================================

template<class Base>
void IPv4oRC<Base>::configureFilters(cXMLElement *config)
{
    IPvXAddressResolver addressResolver;
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

            if (dt == DestinationType_RC) {
                // Destination Info
                const char *destModules = Base::getRequiredAttribute(filterElement, "destModules");
                const char *ctId = Base::getRequiredAttribute(filterElement, "ctId");

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
                RCDestinationInfo *rcDestInfo = new RCDestinationInfo();
                rcDestInfo->setDestType(DestinationType_RC);
                std::vector<std::string> bufferPaths = cStringTokenizer(destModules, DELIMITERS).asVector();
                std::vector<std::string>::const_iterator bufferPath = bufferPaths.begin();
                std::list<RCBuffer*> destCtBuffers;
                for (  ; bufferPath != bufferPaths.end(); ++bufferPath)
                {
                    cModule* module = simulation.getModuleByPath((*bufferPath).c_str());
                    if (!module) {
                       module = findModuleWhereverInNode((*bufferPath).c_str(), this);
                    }
                    if (!module) {
                       throw cRuntimeError("destModule \"%s\" could not be resolved!", (*bufferPath).c_str());
                    }
                    if (RCBuffer *rcBuf = dynamic_cast<RCBuffer*>(module)) {
                        destCtBuffers.push_back(rcBuf);
                    } else {
                        throw cRuntimeError("destModule: %s is not a RCBuffer!", (*bufferPath).c_str());
                    }
                }
                rcDestInfo->setDestModules(destCtBuffers);
                rcDestInfo->setCtId(static_cast<uint16_t>(Base::parseIntAttribute(ctId, "ctId", false)));

                // Fill traffic pattern
                TrafficPattern *tp = new TrafficPattern();
                if (srcAddrAttr)
                    tp->setSrcAddr(addressResolver.resolve(srcAddrAttr));
                if (srcPrefixLengthAttr)
                    tp->setSrcPrefixLength(Base::parseIntAttribute(srcPrefixLengthAttr, "srcPrefixLength"));
                else if (srcAddrAttr)
                    tp->setSrcPrefixLength(tp->getSrcAddr().isIPv6() ? 128 : 32);
                if (destAddrAttr)
                    tp->setDestAddr(addressResolver.resolve(destAddrAttr));
                if (destPrefixLengthAttr)
                    tp->setDestPrefixLength(Base::parseIntAttribute(destPrefixLengthAttr, "destPrefixLength"));
                else if (destAddrAttr)
                    tp->setDestPrefixLength(tp->getDestAddr().isIPv6() ? 128 : 32);
                if (protocolAttr)
                    tp->setProtocol(Base::parseProtocol(protocolAttr, "protocol"));
                if (tosAttr)
                    tp->setTos(Base::parseIntAttribute(tosAttr, "tos"));
                if (tosMaskAttr)
                    tp->setTosMask(Base::parseIntAttribute(tosAttr, "tosMask"));
                if (srcPortAttr) {
                    tp->setSrcPortMin(Base::parseIntAttribute(srcPortAttr, "srcPort"));
                    tp->setSrcPortMax(tp->getSrcPortMin());
                }
                if (srcPortMinAttr)
                    tp->setSrcPortMin(Base::parseIntAttribute(srcPortMinAttr, "srcPortMin"));
                if (srcPortMaxAttr)
                    tp->setSrcPortMax(Base::parseIntAttribute(srcPortMaxAttr, "srcPortMax"));
                if (destPortAttr) {
                    tp->setDestPortMin(Base::parseIntAttribute(destPortAttr, "destPort"));
                    tp->setDestPortMax(tp->getDestPortMin());
                }
                if (destPortMinAttr)
                    tp->setDestPortMin(Base::parseIntAttribute(destPortMinAttr, "destPortMin"));
                if (destPortMaxAttr)
                    tp->setDestPortMax(Base::parseIntAttribute(destPortMaxAttr, "destPortMax"));

                // Add filter
                IPoREFilter *filter = new IPoREFilter();
                filter->setDestInfo(rcDestInfo);
                filter->setTrafficPattern(tp);
                Base::addFilter(filter);
            }


        }
        catch (std::exception& e)
        {
            throw cRuntimeError("Error in XML <filter> element at %s: %s", filterElement->getSourceLocation(), e.what());
        }
    }

}

//==============================================================================

template<class Base>
void IPv4oRC<Base>::handleMessage(cMessage* msg)
{
    if (dynamic_cast<RCFrame*>(msg)) {
        RCFrame* rcFrame = dynamic_cast<RCFrame*>(msg);

        //Reset Bag
        RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(msg->getSenderModule());
        if (rcBuffer)
            rcBuffer->resetBag();

        // decapsulate and send up
        cPacket* ipPacket = rcFrame->decapsulate();
        Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
        etherctrl->setSrc(rcFrame->getSrc());
        etherctrl->setDest(rcFrame->getDest());
        etherctrl->setEtherType(rcFrame->getEtherType());
        ipPacket->setControlInfo(etherctrl);

        ipPacket->setArrival(this, Base::gate("RCIn")->getId());

        delete rcFrame;
        Base::handleMessage(ipPacket);
    }
    else {
        Base::handleMessage(msg);
    }
}

//==============================================================================

template<class Base>
void IPv4oRC<Base>::sendPacketToBuffers(cPacket *packet, const InterfaceEntry *ie, std::list<IPoREFilter*> &filters)
{
    if (packet->getByteLength() > MAX_ETHERNET_DATA_BYTES)
        Base::error("packet from higher layer (%d bytes) exceeds maximum Ethernet payload length (%d)", packet->getByteLength(), MAX_ETHERNET_DATA_BYTES);

    typename std::list<IPoREFilter*>::iterator filter = filters.begin();
    for ( ; filter != filters.end(); ++filter) {
        if ((*filter)->getDestInfo()->getDestType() == DestinationType_RC) {
            sendRCFrame(packet->dup(), ie, (*filter));
        }
    }

    delete packet;

}

//==============================================================================

template<class Base>
void IPv4oRC<Base>::sendRCFrame(cPacket* packet, __attribute__((unused)) const InterfaceEntry* ie, const IPoREFilter* filter)
{
    RCDestinationInfo *destInfo = dynamic_cast<RCDestinationInfo*>(filter->getDestInfo());
    if (!destInfo)
        Base::error("Wrong Destination Info Type. Filter invalid!");

    RCFrame *outFrame = new RCFrame();
    outFrame->encapsulate(packet);
    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    outFrame->setCtID(destInfo->getCtId());
    outFrame->setName(packet->getName());

    std::list<RCBuffer*> destBuffers = destInfo->getDestModules();
    std::list<RCBuffer*>::iterator destBuf = destBuffers.begin();
    for (  ; destBuf != destBuffers.end(); ++destBuf) {
        if ((*destBuf)->gate("in")->getPathStartGate())
        {
            Incoming* in = dynamic_cast<Incoming *>((*destBuf)->gate("in")->getPathStartGate()->getOwner());
            if (in)
            {
                Base::sendDirect(outFrame, in->gate("in"));
            }
            else
            {
                throw cRuntimeError("You can only connect an Incoming module to a Buffer (Buffer:%s, Attached Module:%s)",
                        (*destBuf)->getFullPath().c_str(),
                        (*destBuf)->gate("in")->getPathStartGate()->getOwner()->getFullPath().c_str());
            }
        }
        else //It is ok to directly send a frame to a buffer if no incoming is attached!
        {
            Base::sendDirect(outFrame, (*destBuf)->gate("in"));
        }
    }

}

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#endif // CORE4INET_IPV4ORC_CC_
