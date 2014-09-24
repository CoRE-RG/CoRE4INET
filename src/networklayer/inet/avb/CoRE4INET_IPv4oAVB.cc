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

#ifndef CORE4INET_IPV4OAVB_CC_
#define CORE4INET_IPV4OAVB_CC_

//==============================================================================

#include "CoRE4INET_IPv4oAVB.h"

//==============================================================================

#include "CoRE4INET_Defs.h"
#include "CoRE4INET_Buffer.h"
#include "CoRE4INET_SRPTable.h"
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

template<class base>
IPv4oAVB<base>::IPv4oAVB()
{
    // TODO Auto-generated constructor stub
}

//==============================================================================

template<class base>
IPv4oAVB<base>::~IPv4oAVB()
{
    // TODO Auto-generated destructor stub
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::initialize(int stage)
{
    base::initialize(stage);
    if (stage==0)
    {
        cXMLElement *filters = base::par("filters").xmlValue();
        IPv4oAVB<base>::configureFilters(filters);
        IPv4oAVB<base>::configureSubscriptions(filters);
        SRPTable *srpTable = check_and_cast<SRPTable *>(findModuleWhereverInNode("srpTable", this));
        IPv4oAVB<base>::registerSrpCallbacks(srpTable);
        base::scheduleAt(simTime(), new cMessage("IPv4oAVB registerTalker", MSGKIND_START));
    }
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::registerSrpCallbacks(SRPTable *srpTable) {
    srpTable->subscribe("talkerRegistered", this);
    srpTable->subscribe("listenerRegistered", this);
    srpTable->subscribe("listenerUnregistered", this);
    srpTable->subscribe("listenerRegistrationTimeout", this);
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie)
{
    // Check for matching filters
    bool filterMatch = true;
    std::list<IPoREFilter*> matchingFilters;
    filterMatch = base::getMatchingFilters(packet, matchingFilters);

    // send to corresponding modules
    if(filterMatch) {
        IPv4oAVB<base>::sendPacketToBuffers(packet->dup(), ie, matchingFilters);
    } else {
        base::sendPacketToNIC(packet, ie);
    }
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage() && (strcmp(msg->getName(), "IPv4oAVB registerTalker") == 0))
    {
        SRPTable *srpTable = check_and_cast<SRPTable *>(findModuleWhereverInNode("srpTable", this));
        registerTalker(this->m_filterList, srpTable);
        delete msg;
    }
    else if (dynamic_cast<AVBFrame*>(msg)) {
        AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(msg);
        cPacket* ipPacket = avbFrame->decapsulate();

        Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
        etherctrl->setSrc(avbFrame->getSrc());
        etherctrl->setDest(avbFrame->getDest());
        etherctrl->setEtherType(avbFrame->getEtherType());
        ipPacket->setControlInfo(etherctrl);

        ipPacket->setArrival(this, base::gate("AVBin")->getId());

        base::handleMessage(ipPacket);
    }
    else {
        base::handleMessage(msg);
    }
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent();
    if (id == base::registerSignal("talkerRegistered"))
    {
        SRPTable::TalkerEntry *tentry = check_and_cast<SRPTable::TalkerEntry*>(obj);

        if (std::find(m_subscribeList.begin(), m_subscribeList.end(), tentry->streamId) != m_subscribeList.end())
        {
            SRPTable *srpTable = check_and_cast<SRPTable *>(src);

            //TODO Minor: try to get VLAN
            srpTable->updateListenerWithStreamId(tentry->streamId, this, 0);
            // TODO: update timer???
        }
    }
    else if (id == base::registerSignal("listenerRegistrationTimeout"))
    {
        // TODO
//        SRPTable::ListenerEntry *lentry = check_and_cast<SRPTable::ListenerEntry*>(obj);
//        if (lentry->streamId == (unsigned int) par("streamID").longValue())
//        {
//            if (lentry->module == this)
//            {
//                getDisplayString().setTagArg("i2", 0, "status/hourglass");
//                simtime_t retryInterval = par("retryInterval").doubleValue();
//                if (retryInterval != 0)
//                {
//                    scheduleAt(simTime() + retryInterval, new cMessage("retrySubscription"));
//                }
//            }
//        }
    }
    else if (id == base::registerSignal("listenerRegistered"))
    {
        // TODO
    }
    else if (id == base::registerSignal("listenerUnregistered"))
    {
        //TODO
    }
    else
    {
        base::receiveSignal(src, id, obj);
    }
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::configureFilters(cXMLElement *config)
{
    IPvXAddressResolver addressResolver;
    cXMLElementList filterElements = config->getChildrenByTagName("filter");
    for (int i = 0; i < (int)filterElements.size(); i++)
    {
        cXMLElement *filterElement = filterElements[i];
        try
        {
            const char *destType = base::getRequiredAttribute(filterElement, "destType");


//            if (!this->destTypeEnum) {
//                this->destTypeEnum = cEnum::get("CoRE4INET::DestinationType");
//            }
//
//            DestinationType dt = DestinationType(this->destTypeEnum->lookup(destType));
            cEnum *destTypeEnum = cEnum::get("CoRE4INET::DestinationType");
            DestinationType dt = DestinationType(destTypeEnum->lookup(destType));

            if (dt == DestinationType_AVB) {

                const char *destModule = base::getRequiredAttribute(filterElement, "destModule");
                const char *destMAC = base::getRequiredAttribute(filterElement, "destMAC");
                const char *alsoBE = base::getRequiredAttribute(filterElement, "alsoBE");
                const char *streamId = filterElement->getAttribute("streamId");
                const char *srClass = filterElement->getAttribute("trafficClass");
                const char *frameSize = filterElement->getAttribute("frameSize");
                const char *intFrames = filterElement->getAttribute("intervallFrames");
                const char *vlanId = filterElement->getAttribute("vlanId");
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
                AVBDestinationInfo *avbDestInfo = new AVBDestinationInfo();
                avbDestInfo->setDestType(DestinationType_AVB);

                cModule* module = simulation.getModuleByPath(destModule);
                if (!module) {
                   module = findModuleWhereverInNode(destModule, this);
                }
                if (!module) {
                   throw cRuntimeError("destModule \"%s\" could not be resolved!", destModule);
                }
                if (AVBIncoming *avbCtc = dynamic_cast<AVBIncoming*>(module)) {
                   avbDestInfo->setDestModule(avbCtc);
                } else {
                    throw cRuntimeError("destModule: %s is not a AVBIncoming!", destModule);
                }
                if (destMAC)
                    avbDestInfo->setDestMac(new MACAddress(destMAC));
                else
                     throw cRuntimeError("destMAC not specified!");
                avbDestInfo->setStreamId(base::parseIntAttribute(streamId, "streamId", false));
                avbDestInfo->setSrClass(SR_CLASS(base::parseIntAttribute(srClass, "trafficClass", false)));
                avbDestInfo->setFrameSize(base::parseIntAttribute(frameSize, "frameSize", false));
                avbDestInfo->setIntervallFrames(base::parseIntAttribute(intFrames, "intervallFrames", false));
                avbDestInfo->setVlanId(base::parseIntAttribute(vlanId, "vlanId", false));
                if (alsoBE)
                    avbDestInfo->setAlsoBe(base::parseIntAttribute(alsoBE, "alsoBE", false) != 0);

                // Fill traffic pattern
                TrafficPattern *tp = new TrafficPattern();
                if (srcAddrAttr)
                    tp->setSrcAddr(addressResolver.resolve(srcAddrAttr));
                if (srcPrefixLengthAttr)
                    tp->setSrcPrefixLength(base::parseIntAttribute(srcPrefixLengthAttr, "srcPrefixLength"));
                else if (srcAddrAttr)
                    tp->setSrcPrefixLength(tp->getSrcAddr().isIPv6() ? 128 : 32);
                if (destAddrAttr)
                    tp->setDestAddr(addressResolver.resolve(destAddrAttr));
                if (destPrefixLengthAttr)
                    tp->setDestPrefixLength(base::parseIntAttribute(destPrefixLengthAttr, "destPrefixLength"));
                else if (destAddrAttr)
                    tp->setDestPrefixLength(tp->getDestAddr().isIPv6() ? 128 : 32);
                if (protocolAttr)
                    tp->setProtocol(base::parseProtocol(protocolAttr, "protocol"));
                if (tosAttr)
                    tp->setTos(base::parseIntAttribute(tosAttr, "tos"));
                if (tosMaskAttr)
                    tp->setTosMask(base::parseIntAttribute(tosAttr, "tosMask"));
                if (srcPortAttr) {
                    tp->setSrcPortMin(base::parseIntAttribute(srcPortAttr, "srcPort"));
                    tp->setSrcPortMax(tp->getSrcPortMin());
                }
                if (srcPortMinAttr)
                    tp->setSrcPortMin(base::parseIntAttribute(srcPortMinAttr, "srcPortMin"));
                if (srcPortMaxAttr)
                    tp->setSrcPortMax(base::parseIntAttribute(srcPortMaxAttr, "srcPortMax"));
                if (destPortAttr) {
                    tp->setDestPortMin(base::parseIntAttribute(destPortAttr, "destPort"));
                    tp->setDestPortMax(tp->getDestPortMin());
                }
                if (destPortMinAttr)
                    tp->setDestPortMin(base::parseIntAttribute(destPortMinAttr, "destPortMin"));
                if (destPortMaxAttr)
                    tp->setDestPortMax(base::parseIntAttribute(destPortMaxAttr, "destPortMax"));

                // Add filter
                IPoREFilter *filter = new IPoREFilter();
                filter->setDestInfo(avbDestInfo);
                filter->setTrafficPattern(tp);
                base::addFilter(filter);
            }
            

        }
        catch (std::exception& e)
        {
            throw cRuntimeError("Error in XML <filter> element at %s: %s", filterElement->getSourceLocation(), e.what());
        }
    }

}

//==============================================================================

template<class base>
void IPv4oAVB<base>::configureSubscriptions(cXMLElement *config)
{
    cXMLElementList filterElements = config->getChildrenByTagName("subscribe");
    for (int i = 0; i < (int)filterElements.size(); i++)
    {
        cXMLElement *filterElement = filterElements[i];
        try
        {
            const char *streamId = base::getRequiredAttribute(filterElement, "streamId");

            if (streamId) {
                int id = base::parseIntAttribute(streamId, "streamId");
                m_subscribeList.push_back(id);
            }
        }
        catch (std::exception& e)
        {
            throw cRuntimeError("Error in XML <subscribe> element at %s: %s", filterElement->getSourceLocation(), e.what());
        }
    }
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::registerTalker(const std::list<IPoREFilter*> filters, SRPTable *srpTable)
{
    typename std::list<IPoREFilter*>::const_iterator filter = filters.begin();
    for ( ; filter != filters.end(); ++filter) {
        if ((*filter)->getDestInfo()->getDestType() == DestinationType_AVB) {
            registerTalker((*filter), srpTable);
        }
    }
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::registerTalker(const IPoREFilter* filter, SRPTable *srpTable)
{
    if (srpTable)
    {
        EV << "Register Talker in node" << std::endl;
        AVBDestinationInfo *avbDestInfo = dynamic_cast<AVBDestinationInfo *>(filter->getDestInfo());
        srpTable->updateTalkerWithStreamId(
                avbDestInfo->getStreamId(),
                this,
                *(avbDestInfo->getDestMac()),
                avbDestInfo->getSrClass(),
                avbDestInfo->getFrameSize(),
                avbDestInfo->getIntervallFrames(),
                avbDestInfo->getVlanId());
    }
    else
    {
        throw cRuntimeError("srpTable module required for stream reservation");
    }
}

//==============================================================================

template<class base>
int IPv4oAVB<base>::sendPacketToBuffers(cPacket *packet, const InterfaceEntry *ie, std::list<IPoREFilter*> &filters)
{
    if (packet->getByteLength() > MAX_ETHERNET_DATA_BYTES)
        base::error("packet from higher layer (%d bytes) exceeds maximum Ethernet payload length (%d)", (int)packet->getByteLength(), MAX_ETHERNET_DATA_BYTES);

    int matchingFilters = 0;
    typename std::list<IPoREFilter*>::iterator filter = filters.begin();
    for ( ; filter != filters.end(); ++filter) {
        switch ((*filter)->getDestInfo()->getDestType()) {
        case DestinationType_AVB:
            {
                sendAVBFrame(packet->dup(), ie, (*filter));
                matchingFilters++;
                break;
            }
        default:
            {
                break;
            }
        }
        if ((*filter)->getDestInfo()->isAlsoBe()) {
            base::sendPacketToNIC(packet->dup(), ie);
        }
    }

    delete packet;

    return matchingFilters;
}

//==============================================================================

template<class base>
void IPv4oAVB<base>::sendAVBFrame(cPacket* packet, const InterfaceEntry* ie, const IPoREFilter* filter)
{
	AVBDestinationInfo *avbDestInfo = dynamic_cast<AVBDestinationInfo *>(filter->getDestInfo());
    std::stringstream name;
    name << "Stream " << avbDestInfo->getStreamId();
    AVBFrame *outFrame = new AVBFrame(name.str().c_str());
    outFrame->setStreamID(avbDestInfo->getStreamId());
    outFrame->setDest(*(avbDestInfo->getDestMac()));
    outFrame->setEtherType(ETHERTYPE_IPv4);

    outFrame->encapsulate(packet);

    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
    {
        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    base::sendDirect(outFrame, avbDestInfo->getDestModule()->gate("in"));

}

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#endif // CORE4INET_IPV4OAVB_CC_

