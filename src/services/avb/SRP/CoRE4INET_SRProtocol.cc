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

#include "CoRE4INET_SRProtocol.h"

//Std
#include <algorithm>
//CoRE4INET
#include "CoRE4INET_AVBDefs.h"
#include "ExtendedIeee802Ctrl_m.h"
#include "CoRE4INET_NotifierConsts.h"
//Auto-generated Messages
#include "SRPFrame_m.h"

namespace CoRE4INET {

Define_Module(SRProtocol);

void SRProtocol::initialize()
{
    srpTable = dynamic_cast<SRPTable *>(getParentModule()->getSubmodule("srpTable"));
    if (!srpTable)
    {
        throw cRuntimeError("srpTable module required for stream reservation");
    }
    srpTable->subscribe(NF_AVB_TALKER_REGISTERED, this);
    srpTable->subscribe(NF_AVB_LISTENER_REGISTERED, this);
    srpTable->subscribe(NF_AVB_LISTENER_UPDATED, this);
}

void SRProtocol::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        Ieee802Ctrl *etherctrl = dynamic_cast<Ieee802Ctrl *>(msg->removeControlInfo());
        if (!etherctrl)
        {
            error("packet `%s' from lower layer received without Ieee802Ctrl", msg->getName());
        }
        else
        {
            int arrivedOn = etherctrl->getSwitchPort();
            cModule *port = getParentModule()->getSubmodule("phy", arrivedOn);

            if (TalkerAdvertise* talkerAdvertise = dynamic_cast<TalkerAdvertise*>(msg))
            {
                SR_CLASS srClass;
                if (talkerAdvertise->getPriorityAndRank() == PRIOANDRANK_SRCLASSA)
                {
                    srClass = SR_CLASS_A;
                }
                else if (talkerAdvertise->getPriorityAndRank() == PRIOANDRANK_SRCLASSB)
                {
                    srClass = SR_CLASS_B;
                }
                else
                {
                    srClass = SR_CLASS_A;
                }
                srpTable->updateTalkerWithStreamId(talkerAdvertise->getStreamID(), port,
                        talkerAdvertise->getDestination_address(), srClass, talkerAdvertise->getMaxFrameSize(),
                        talkerAdvertise->getMaxIntervalFrames(), talkerAdvertise->getVlan_identifier());
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
                utilizedBandwidth += static_cast<unsigned long>(port->getSubmodule("shaper")->par(
                        "AVBHigherPriorityBandwidth").longValue());
                unsigned long requiredBandwidth = srpTable->getBandwidthForStream(listenerReady->getStreamID(),
                        listenerReady->getVlan_identifier());

                cGate *physOutGate = port->getSubmodule("mac")->gate("phys$o");
                cChannel *outChannel = physOutGate->findTransmissionChannel();

                unsigned long totalBandwidth = static_cast<unsigned long>(outChannel->getNominalDatarate());

                double reservableBandwidth = par("reservableBandwidth").doubleValue();

                if (update
                        || ((utilizedBandwidth + requiredBandwidth)
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
                        srp = new ListenerReadyFailed("Listener Ready Failed", IEEE802CTRL_DATA);
                    }
                    else
                    {
                        bubble("Listener Failed!");
                        srp = new ListenerAskingFailed("Listener Failed", IEEE802CTRL_DATA);
                    }
                    srp->setStreamID(listenerReady->getStreamID());

                    ExtendedIeee802Ctrl *new_etherctrl = new ExtendedIeee802Ctrl();
                    new_etherctrl->setEtherType(MSRP_ETHERTYPE);
                    new_etherctrl->setDest(SRP_ADDRESS);
                    cModule* talker = srpTable->getTalkerForStreamId(listenerReady->getStreamID(),
                            listenerReady->getVlan_identifier());
                    if (talker && talker->isName("phy"))
                    {
                        new_etherctrl->setSwitchPort(talker->getIndex());
                        srp->setControlInfo(new_etherctrl);
                        send(srp, gate("out"));
                    }
                }
            }
            else if (ListenerAskingFailed* listenerFailed = dynamic_cast<ListenerAskingFailed*>(msg))
            {
                bubble("Listener Failed!");
                ExtendedIeee802Ctrl *new_etherctrl = new ExtendedIeee802Ctrl();
                new_etherctrl->setEtherType(MSRP_ETHERTYPE);
                new_etherctrl->setDest(SRP_ADDRESS);
                cModule* talker = srpTable->getTalkerForStreamId(listenerFailed->getStreamID(),
                        listenerFailed->getVlan_identifier());
                if (talker && talker->isName("phy"))
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

void SRProtocol::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent
    ();
    if (id == NF_AVB_TALKER_REGISTERED)
    {
        if (SRPTable::TalkerEntry *tentry = dynamic_cast<SRPTable::TalkerEntry*>(obj))
        {
            TalkerAdvertise *talkerAdvertise = new TalkerAdvertise("Talker Advertise", IEEE802CTRL_DATA);
            //talkerAdvertise->setStreamDA(tentry->address);
            talkerAdvertise->setStreamID(tentry->streamId);
            talkerAdvertise->setMaxFrameSize(static_cast<uint16_t>(tentry->framesize));
            talkerAdvertise->setMaxIntervalFrames(tentry->intervalFrames);
            talkerAdvertise->setDestination_address(tentry->address);
            talkerAdvertise->setVlan_identifier(tentry->vlan_id);
            if (tentry->srClass == SR_CLASS_A)
                talkerAdvertise->setPriorityAndRank(PRIOANDRANK_SRCLASSA);
            if (tentry->srClass == SR_CLASS_B)
                talkerAdvertise->setPriorityAndRank(PRIOANDRANK_SRCLASSB);

            ExtendedIeee802Ctrl *etherctrl = new ExtendedIeee802Ctrl();
            etherctrl->setEtherType(MSRP_ETHERTYPE);
            etherctrl->setDest(SRP_ADDRESS);
            etherctrl->setSwitchPort(SWITCH_PORT_BROADCAST);
            talkerAdvertise->setControlInfo(etherctrl);

            //If talker was received from phy we have to exclude the incoming port
            if (strcmp(tentry->module->getName(), "phy") == 0)
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
            if (talker && talker->isName("phy"))
            {
                ListenerReady *listenerReady = new ListenerReady("Listener Ready", IEEE802CTRL_DATA);
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
