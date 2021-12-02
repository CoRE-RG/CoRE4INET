//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "core4inet/services/avb/SRP/SRProtocol.h"

//Std
#include <algorithm>
//CoRE4INET
#include "core4inet/utilities/ModuleAccess.h"
#include "core4inet/base/avb/AVBDefs.h"
#include "core4inet/linklayer/contract/ExtendedIeee802Ctrl_m.h"
#include "core4inet/base/NotifierConsts.h"
//Auto-generated Messages
#include "core4inet/linklayer/ethernet/avb/SRPFrame_m.h"

namespace CoRE4INET {

Define_Module(SRProtocol);

SRProtocol::SRProtocol(){
    this->srpTable = nullptr;
}

void SRProtocol::initialize()
{
    srpTable = inet::getModuleFromPar<SRPTable>(par("srpTable"), this, true);
    if (!srpTable)
    {
        throw cRuntimeError("srpTable module required for stream reservation");
    }

    //this part is optional
    if(!this->gate("in")->isConnected() && !this->gate("out")->isConnected())
    {
        if(strcmp(par("srpEncap"),"") !=0)
        {
            if(cModule* interface = dynamic_cast<cModule*> (getModuleByPath(par("srpEncap"))))
            {
                this->gate("out")->connectTo(interface->gate("srpIn"));
                interface->gate("srpOut")->connectTo(this->gate("in"));
            }else
            {
                throw cRuntimeError("could not get interface module");
            }
        }else
        {
            throw cRuntimeError("could not find path to interface module in param <srcEncap>");
        }
    }

    srpTable->subscribe(NF_AVB_TALKER_REGISTERED, this);
    srpTable->subscribe(NF_AVB_LISTENER_REGISTERED, this);
    srpTable->subscribe(NF_AVB_LISTENER_UPDATED, this);
    this->handleParameterChange(nullptr);
}

void SRProtocol::handleParameterChange(const char* parname)
{
    if(!parname || !strcmp(parname, "pcpSRClassA"))
    {
        this->pcpSRClassA = static_cast<uint8_t>(parameterULongCheckRange(par("pcpSRClassA"), 0, 7));
        this->priortyAndRankSRClassA = static_cast<uint8_t>(0x10 | (this->pcpSRClassA << 5));
    }
    if(!parname || !strcmp(parname, "pcpSRClassB"))
    {
        this->pcpSRClassB = static_cast<uint8_t>(parameterULongCheckRange(par("pcpSRClassB"), 0, 7));
        this->priortyAndRankSRClassB = static_cast<uint8_t>(0x10 | (this->pcpSRClassB << 5));
    }
    if(this->pcpSRClassA == this->pcpSRClassB)
    {
        throw cRuntimeError("PCP value for SRClass A and B are the same!");
    }
}

void SRProtocol::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        inet::Ieee802Ctrl *etherctrl = dynamic_cast<inet::Ieee802Ctrl *>(msg->removeControlInfo());
        if (!etherctrl)
        {
            error("packet `%s' from lower layer received without Ieee802Ctrl", msg->getName());
        }
        else
        {
            int arrivedOn = etherctrl->getSwitchPort();
            cModule *port = getParentModule()->getSubmodule(par("portModule").stringValue(), arrivedOn);

            if (TalkerAdvertise* talkerAdvertise = dynamic_cast<TalkerAdvertise*>(msg))
            {
                SR_CLASS srClass;
                if (talkerAdvertise->getPriorityAndRank() == this->priortyAndRankSRClassA)
                {
                    srClass = SR_CLASS::A;
                }
                else if (talkerAdvertise->getPriorityAndRank() == this->priortyAndRankSRClassB)
                {
                    srClass = SR_CLASS::B;
                }
                else
                {
                    srClass = SR_CLASS::A;
                }
                //only take first 3 bit and shift them to fit the uint8_t
                uint8_t pcp = (talkerAdvertise->getPriorityAndRank() & 0xE0) >> 5;
                srpTable->updateTalkerWithStreamId(talkerAdvertise->getStreamID(), port,
                        talkerAdvertise->getDestination_address(), srClass, talkerAdvertise->getMaxFrameSize(),
                        talkerAdvertise->getMaxIntervalFrames(), talkerAdvertise->getVlan_identifier(), pcp);
            }
            else if (ListenerReady* listenerReady = dynamic_cast<ListenerReady*>(msg))
            {
                bool update = false;
                std::list<cModule*> listeners = srpTable->getListenersForStreamId(listenerReady->getStreamID(),
                        listenerReady->getVlan_identifier());
                //Is this a new or updated stream
                if (std::find(listeners.begin(), listeners.end(), port) != listeners.end())
                {
                    update = true;
                }

                unsigned long utilizedBandwidth = srpTable->getBandwidthForModule(port);
                //Add Higher Priority Bandwidth
                utilizedBandwidth += static_cast<unsigned long>(findModuleWherever("shaper", port)->par("AVBHigherPriorityBandwidth"));
                unsigned long requiredBandwidth = srpTable->getBandwidthForStream(listenerReady->getStreamID(),
                        listenerReady->getVlan_identifier());

                cGate *physOutGate = findModuleWherever("mac", port)->gate("phys$o");
                cChannel *outChannel = physOutGate->findTransmissionChannel();

                unsigned long totalBandwidth = static_cast<unsigned long>(outChannel->getNominalDatarate());

                double reservableBandwidth = par("reservableBandwidth").doubleValue();

                if (update
                        || (static_cast<double>(utilizedBandwidth + requiredBandwidth)
                                <= (static_cast<double>(totalBandwidth) * reservableBandwidth)))
                {
                    srpTable->updateListenerWithStreamId(listenerReady->getStreamID(), port,
                            listenerReady->getVlan_identifier());
                    if (!update)
                    {
                        EV_DETAIL << "Listener for stream " << listenerReady->getStreamID() << " registered on port "
                                << port->getFullName() << ". Utilized Bandwidth: "
                                << static_cast<double>(utilizedBandwidth + requiredBandwidth)
                                        / static_cast<double>(1000000) << " of "
                                << (static_cast<double>(totalBandwidth) * reservableBandwidth)
                                        / static_cast<double>(1000000) << " reservable Bandwidth of "
                                << static_cast<double>(totalBandwidth) / static_cast<double>(1000000) << " MBit/s.";
                    }
                }
                else
                {
                    EV_DETAIL << "Listener for stream " << listenerReady->getStreamID()
                            << " could not be registered on port " << port->getFullName() << ". Required bandwidth: "
                            << static_cast<double>(requiredBandwidth) / static_cast<double>(1000000)
                            << "MBit/s, remaining bandwidth "
                            << ((static_cast<double>(totalBandwidth) * reservableBandwidth)
                                    - static_cast<double>(utilizedBandwidth)) / static_cast<double>(1000000)
                            << "MBit/s.";
                    SRPFrame *srp;
                    if (srpTable->getListenersForStreamId(listenerReady->getStreamID(),
                            listenerReady->getVlan_identifier()).size() > 0)
                    {
                        bubble("Listener Ready Failed!");
                        ListenerReadyFailed *lrf = new ListenerReadyFailed("Listener Ready Failed", inet::IEEE802CTRL_DATA);
                        lrf->setVlan_identifier(listenerReady->getVlan_identifier());
                        srp = lrf;
                    }
                    else
                    {
                        bubble("Listener Asking Failed!");
                        ListenerAskingFailed *laf = new ListenerAskingFailed("Listener Asking Failed", inet::IEEE802CTRL_DATA);
                        laf->setVlan_identifier(listenerReady->getVlan_identifier());
                        srp = laf;
                    }
                    srp->setStreamID(listenerReady->getStreamID());

                    ExtendedIeee802Ctrl *new_etherctrl = new ExtendedIeee802Ctrl();
                    new_etherctrl->setEtherType(MSRP_ETHERTYPE);
                    new_etherctrl->setDest(SRP_ADDRESS);
                    cModule* talker = srpTable->getTalkerForStreamId(listenerReady->getStreamID(),
                            listenerReady->getVlan_identifier());
                    if (talker && talker->isName(par("portModule").stringValue()))
                    {
                        new_etherctrl->setSwitchPort(talker->getIndex());
                        srp->setControlInfo(new_etherctrl);
                        send(srp, gate("out"));
                    }
                }
            }
            else if (ListenerAskingFailed* listenerFailed = dynamic_cast<ListenerAskingFailed*>(msg))
            {
                bubble("Listener Asking Failed!");
                ExtendedIeee802Ctrl *new_etherctrl = new ExtendedIeee802Ctrl();
                new_etherctrl->setEtherType(MSRP_ETHERTYPE);
                new_etherctrl->setDest(SRP_ADDRESS);
                cModule* talker = srpTable->getTalkerForStreamId(listenerFailed->getStreamID(),
                        listenerFailed->getVlan_identifier());
                if (talker && talker->isName(par("portModule").stringValue()))
                {
                    new_etherctrl->setSwitchPort(talker->getIndex());
                    //Necessary because controlInfo is not duplicated
                    ListenerAskingFailed* listenerFailedCopy = listenerFailed->dup();
                    listenerFailedCopy->setControlInfo(new_etherctrl);
                    send(listenerFailedCopy, gate("out"));
                }
            }
            delete etherctrl;
        }
    }
    delete msg;
}

void SRProtocol::receiveSignal(cComponent *src, simsignal_t id, cObject *obj, __attribute__((unused)) cObject *details)
{
    Enter_Method_Silent
    ();
    if (id == NF_AVB_TALKER_REGISTERED)
    {
        if (SRPTable::TalkerEntry *tentry = dynamic_cast<SRPTable::TalkerEntry*>(obj))
        {
            TalkerAdvertise *talkerAdvertise = new TalkerAdvertise("Talker Advertise", inet::IEEE802CTRL_DATA);
            //talkerAdvertise->setStreamDA(tentry->address);
            talkerAdvertise->setStreamID(tentry->streamId);
            talkerAdvertise->setMaxFrameSize(static_cast<uint16_t>(tentry->framesize));
            talkerAdvertise->setMaxIntervalFrames(tentry->intervalFrames);
            talkerAdvertise->setDestination_address(tentry->address);
            talkerAdvertise->setVlan_identifier(tentry->vlan_id);
            if (tentry->srClass == SR_CLASS::A)
               talkerAdvertise->setPriorityAndRank(this->priortyAndRankSRClassA);
           if (tentry->srClass == SR_CLASS::B)
               talkerAdvertise->setPriorityAndRank(this->priortyAndRankSRClassB);
            ExtendedIeee802Ctrl *etherctrl = new ExtendedIeee802Ctrl();
            etherctrl->setEtherType(MSRP_ETHERTYPE);
            etherctrl->setDest(SRP_ADDRESS);
            etherctrl->setSwitchPort(SWITCH_PORT_BROADCAST);
            talkerAdvertise->setControlInfo(etherctrl);
            // If talker was received from phy we have to exclude the incoming port
            if (strcmp(tentry->module->getName(), par("portModule").stringValue()) == 0)
            {
                etherctrl->setNotSwitchPort(tentry->module->getIndex());
            }

            send(talkerAdvertise, gate("out"));
        }
        else
        {
            throw cRuntimeError("Received signal with wrong object type");
        }
    }
    else if (id == NF_AVB_LISTENER_REGISTERED || id == NF_AVB_LISTENER_UPDATED)
    {
        if (SRPTable::ListenerEntry *lentry = dynamic_cast<SRPTable::ListenerEntry*>(obj))
        {

            //Get Talker Port
            SRPTable *signal_srpTable = dynamic_cast<SRPTable *>(src);
            if (!signal_srpTable)
            {
                throw cRuntimeError(
                        "listenerRegistered or listenerUpdated signal received, from module that is not a SRPTable");
            }
            cModule* talker = signal_srpTable->getTalkerForStreamId(lentry->streamId, lentry->vlan_id);
            //Send listener ready only when talker is not a local application
            if (talker && talker->isName(par("portModule").stringValue()))
            {
                ListenerReady *listenerReady = new ListenerReady("Listener Ready", inet::IEEE802CTRL_DATA);
                listenerReady->setStreamID(lentry->streamId);
                listenerReady->setVlan_identifier(lentry->vlan_id);

                ExtendedIeee802Ctrl *etherctrl = new ExtendedIeee802Ctrl();
                etherctrl->setEtherType(MSRP_ETHERTYPE);
                etherctrl->setDest(SRP_ADDRESS);
                etherctrl->setSwitchPort(talker->getIndex());
                listenerReady->setControlInfo(etherctrl);

                send(listenerReady, gate("out"));
            }
        }
        else
        {
            throw cRuntimeError("Received signal with wrong object type");
        }

    }
}

} /* namespace CoRE4INET */
