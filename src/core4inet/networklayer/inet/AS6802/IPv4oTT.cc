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

#ifndef CORE4INET_IPV4OTT_CC_
#define CORE4INET_IPV4OTT_CC_

//==============================================================================

#include "core4inet/networklayer/inet/AS6802/IPv4oTT.h"

#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/base/IPoRE/IPoREDefs_m.h"
#include "core4inet/linklayer/ethernet/AS6802/TTFrame_m.h"
#include "core4inet/networklayer/inet/AS6802/TTDestinationInfo.h"
#include "core4inet/buffer/AS6802/TTBuffer.h"
#include "core4inet/networklayer/inet/base/IPoREFilter.h"
#include "core4inet/incoming/base/Incoming.h"
#include "core4inet/base/NotifierConsts.h"
#include "core4inet/synchronisation/base/SyncNotification_m.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/transportlayer/udp/UDPPacket.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

template<class Base>
IPv4oTT<Base>::IPv4oTT()
{
    this->synchronized = false;
}

//==============================================================================

template<class Base>
IPv4oTT<Base>::~IPv4oTT()
{
    std::unordered_map<std::string, std::list<QueuedPacket*> >::iterator i = ttPackets.begin();
    while (i != ttPackets.end())
    {
        std::list<QueuedPacket*>::iterator j = i->second.begin();
        while (j != i->second.end())
        {
            QueuedPacket *qp = (*j);
            cPacket *p = qp->getPacket();
            delete p;
            delete qp;
            ++j;
        }
        i->second.clear();
        ++i;
    }
    ttPackets.clear();
}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::initialize(int stage)
{
    Base::initialize(stage);
    if (stage == 0)
    {
        synchronized = false;

        cXMLElement *filters = Base::par("filters").xmlValue();
        IPv4oTT<Base>::configureFilters(filters);

        Base::scheduleAt(simTime(),
                new cMessage("IPv4oTT register action time events", static_cast<short>(MsgKind::START)));

        ASSERT2(findContainingNode(this)!=nullptr,
                "TrafficSource is not inside a Node (Node must be marked by @node property in ned module)");
        findContainingNode(this)->subscribe(NF_SYNC_STATE_CHANGE, this);
    }
}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::sendPacketToNIC(cPacket *packet, const inet::InterfaceEntry *ie)
{
    // Check for matching filters
    std::list<IPoREFilter*> matchingFilters;
    bool filterMatch = Base::getMatchingFilters(packet, matchingFilters, DestinationType_TT);

    // INFO: if you want to send packages to different buffers (e.g. TT and AVB) you have to check for the "alsoBE" filter element and call base::sendPacketToNIC()
    // send to corresponding modules
    if (filterMatch)
    {
        IPv4oTT<Base>::sendPacketToBuffers(packet, ie, matchingFilters);
    }
    else
    {
        Base::sendPacketToNIC(packet, ie);
    }
}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::configureFilters(cXMLElement *config)
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

            if (dt == DestinationType_TT)
            {
                // Destination Info
                const char *destModule = Base::getRequiredAttribute(filterElement, "destModule");
                const char *ctId = Base::getRequiredAttribute(filterElement, "ctId");
                const char *period = filterElement->getAttribute("period");
                const char *actionTime = Base::getRequiredAttribute(filterElement, "actionTime");
                const char *oscillator = filterElement->getAttribute("oscillator");

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
                TTDestinationInfo *ttDestInfo = new TTDestinationInfo();
                ttDestInfo->setDestType(DestinationType_TT);
                cModule* module = getSimulation()->getModuleByPath(destModule);
                if (!module)
                {
                    module = findModuleWhereverInNode(destModule, this);
                }
                if (!module)
                {
                    throw cRuntimeError("destModule \"%s\" could not be resolved!", destModule);
                }
                if (TTBuffer *ttBuf = dynamic_cast<TTBuffer*>(module))
                {
                    ttDestInfo->setDestModule(ttBuf);
                }
                else
                {
                    throw cRuntimeError("destModule: %s is not a TTBuffer!", destModule);
                }
                ttDestInfo->setCtId(static_cast<uint16_t>(Base::parseIntAttribute(ctId, "ctId", false)));

                Period *periodModule;
                if (period)
                {
                    periodModule = dynamic_cast<Period*>(findModuleWhereverInNode(period, this));
                }
                else
                {
                    periodModule = dynamic_cast<Period*>(findModuleWhereverInNode("period[0]", this));
                }
                if (periodModule)
                {
                    ttDestInfo->setPeriod(periodModule);
                }
                else
                {
                    throw cRuntimeError("period module \"%s\" not found or is not of type Period!", period);
                }

                ttDestInfo->setActionTime(
                        static_cast<double>(Base::parseIntAttribute(actionTime, "actionTime", false))
                                / static_cast<double>(1000000));

                Oscillator *osc;
                if (oscillator)
                {
                    osc = dynamic_cast<Oscillator*>(findModuleWhereverInNode(oscillator, this));
                }
                else
                {
                    osc = dynamic_cast<Oscillator*>(findModuleWhereverInNode("oscillator", this));
                }
                if (osc)
                {
                    ttDestInfo->setOscillator(osc);
                }
                else
                {
                    throw cRuntimeError("oscillator module \"%s\" not found or is not of type Oscillator!", oscillator);
                }

                // Fill traffic pattern
                TrafficPattern *tp = new TrafficPattern();
                if (srcAddrAttr)
                    tp->setSrcAddr(addressResolver.resolve(srcAddrAttr));
                if (srcPrefixLengthAttr)
                    tp->setSrcPrefixLength(Base::parseIntAttribute(srcPrefixLengthAttr, "srcPrefixLength"));
                else if (srcAddrAttr)
                    tp->setSrcPrefixLength(tp->getSrcAddr().getType()==inet::L3Address::IPv6 ? 128 : 32);
                if (destAddrAttr)
                    tp->setDestAddr(addressResolver.resolve(destAddrAttr));
                if (destPrefixLengthAttr)
                    tp->setDestPrefixLength(Base::parseIntAttribute(destPrefixLengthAttr, "destPrefixLength"));
                else if (destAddrAttr)
                    tp->setDestPrefixLength(tp->getDestAddr().getType()==inet::L3Address::IPv6 ? 128 : 32);
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
                filter->setDestInfo(ttDestInfo);
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
void IPv4oTT<Base>::handleMessage(cMessage* msg)
{

    if (msg->isSelfMessage() && (strcmp(msg->getName(), "IPv4oTT register action time events") == 0))
    {
        std::list<IPoREFilter*> ttFilters = Base::getFilters(DestinationType_TT);
        registerSendTimingEvents(ttFilters);
        delete msg;
    }
    else if (msg->arrivedOn("schedulerIn"))
    {
        std::string msgName(msg->getName());

        if (periods.count(msgName) > 0)
        {
            if (synchronized && ttPackets[msgName].size() > 0)
            {
                QueuedPacket *toSend = ttPackets[msgName].front();
                ttPackets[msgName].pop_front();
                sendTTFrame(toSend->getPacket(), toSend->getFilter());
                delete toSend;
            }

            SchedulerActionTimeEvent *event = check_and_cast<SchedulerActionTimeEvent *>(msg);
            event->setNext_cycle(true);
            periods[msgName]->registerEvent(event);
        }

    }
    else if (dynamic_cast<TTFrame*>(msg))
    {
        TTFrame* ttFrame = dynamic_cast<TTFrame*>(msg);

        // decapsulate and send up
        cPacket* ipPacket = ttFrame->decapsulate();
        inet::Ieee802Ctrl *etherctrl = new inet::Ieee802Ctrl();
        etherctrl->setSrc(ttFrame->getSrc());
        etherctrl->setDest(ttFrame->getDest());
        etherctrl->setEtherType(ttFrame->getEtherType());
        ipPacket->setControlInfo(etherctrl);
        ipPacket->setArrival(this->getId(), Base::gate("TTIn")->getId());

        delete ttFrame;
        Base::handleMessage(ipPacket);
    }
    else if (msg->arrivedOn("TTIn"))
    {
        // discard msg on TTIn, if not TTFrame
        delete msg;
    }
    else
    {
        Base::handleMessage(msg);
    }
}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::sendPacketToBuffers(cPacket *packet, __attribute__((unused))  const inet::InterfaceEntry *ie,
        std::list<IPoREFilter*> &filters)
{
    if (packet->getByteLength() > MAX_ETHERNET_DATA_BYTES)
        Base::error("packet from higher layer (%d bytes) exceeds maximum Ethernet payload length (%d)",
                packet->getByteLength(), MAX_ETHERNET_DATA_BYTES);

    typename std::list<IPoREFilter*>::iterator filter = filters.begin();
    for (; filter != filters.end(); ++filter)
    {
        if ((*filter)->getDestInfo()->getDestType() == DestinationType_TT)
        {
            ttPackets[static_cast<TTDestinationInfo*>((*filter)->getDestInfo())->getDestModule()->getFullPath()].push_back(
                    new QueuedPacket((*filter), packet->dup()));
        }
    }

    delete packet;

}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::sendTTFrame(cPacket* packet, const IPoREFilter* filter)
{
    TTDestinationInfo *destInfo = dynamic_cast<TTDestinationInfo*>(filter->getDestInfo());
    if (!destInfo)
        Base::error("Wrong Destination Info Type. Filter invalid!");

    TTFrame *outFrame = new TTFrame();
    outFrame->encapsulate(packet);
    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
    {
        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    outFrame->setCtID(destInfo->getCtId());
    outFrame->setName(packet->getName());

    TTBuffer *destBuf = destInfo->getDestModule();

    if (destBuf->gate("in")->getPathStartGate())
    {
        Incoming* in = dynamic_cast<Incoming *>(destBuf->gate("in")->getPathStartGate()->getOwner());
        if (in)
        {
            Base::sendDirect(outFrame, in->gate("in"));
        }
        else
        {
            throw cRuntimeError("You can only connect an Incoming module to a Buffer (Buffer:%s, Attached Module:%s)",
                    destBuf->getFullPath().c_str(),
                    destBuf->gate("in")->getPathStartGate()->getOwner()->getFullPath().c_str());
        }
    }
    else //It is ok to directly send a frame to a buffer if no incoming is attached!
    {
        Base::sendDirect(outFrame, destBuf->gate("in"));
    }

}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::registerSendTimingEvents(std::list<IPoREFilter*> &filters)
{
    std::list<IPoREFilter*>::iterator f = filters.begin();
    for (; f != filters.end(); ++f)
    {
        registerSendTimingEvent(check_and_cast<TTDestinationInfo *>((*f)->getDestInfo()));
    }
}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::registerSendTimingEvent(TTDestinationInfo *destInfo)
{
    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent(destInfo->getDestModule()->getFullPath().c_str(),
            ACTION_TIME_EVENT);
    event->setAction_time(
            static_cast<uint32_t>(destInfo->getActionTime() / destInfo->getOscillator()->par("tick").doubleValue()));
    event->setDestinationGate(Base::gate("schedulerIn"));

    if (event->getAction_time() >= static_cast<uint32_t>(destInfo->getPeriod()->par("cycle_ticks").intValue()))
    {
        throw cRuntimeError("The action_time (%d ticks) starts outside of the period (%d ticks)",
                event->getAction_time(), destInfo->getPeriod()->par("cycle_ticks").intValue());
    }

    destInfo->getPeriod()->registerEvent(event);
    periods[destInfo->getDestModule()->getFullPath()] = destInfo->getPeriod();
}

//==============================================================================

template<class Base>
void IPv4oTT<Base>::receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details)
{

    if (SyncNotification *notification = dynamic_cast<SyncNotification *>(obj))
    {
        if (notification->getKind() == SYNC)
        {
            synchronized = true;
        }
        else
        {
            synchronized = false;
        }
    }
    else
    {
        Base::receiveSignal(src, id, obj, details);
    }
}

} /* namespace CoRE4INET */

//==============================================================================

#endif // CORE4INET_IPV4OTT_CC_
