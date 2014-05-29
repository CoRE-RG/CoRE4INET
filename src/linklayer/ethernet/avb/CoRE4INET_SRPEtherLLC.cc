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

#include "CoRE4INET_SRPEtherLLC.h"

//CoRE4INET
#include "CoRE4INET_AVBDefs.h"
//INET Auto-generated Messages
#include "ExtendedIeee802Ctrl_m.h"


namespace CoRE4INET {

Define_Module(SRPEtherLLC);

void SRPEtherLLC::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("srpIn"))
    {
        SRPFrame * srpFrame = check_and_cast<SRPFrame*>(msg);
        dispatchSRP(srpFrame);
    }
    else if (msg->arrivedOn("lowerLayerIn"))
    {
        EtherFrame * frame = check_and_cast<EtherFrame*>(msg);
        if (frame->getDest() == SRP_ADDRESS)
        {
            EV_DETAIL << "Deliver SRPFrame to the SRP module" << endl;
            deliverSRP(frame); // deliver to the SRP module
        }
        else
        {
            BGEtherLLC::handleMessage(msg);
        }
    }
    else
    {
        BGEtherLLC::handleMessage(msg);
    }
}

void SRPEtherLLC::dispatchSRP(SRPFrame * srp)
{
    ExtendedIeee802Ctrl * controlInfo = dynamic_cast<ExtendedIeee802Ctrl *>(srp->removeControlInfo());
    int portNum = controlInfo->getSwitchPort();
    int notPortNum = controlInfo->getNotSwitchPort();
    MACAddress address = controlInfo->getDest();

    if (portNum >= 1)
        throw cRuntimeError("Output port %d doesn't exist!", portNum);

    EthernetIIFrame * frame = new EthernetIIFrame(srp->getName());
    frame->setDest(address);
    frame->setSrc(controlInfo->getSrc());
    frame->setByteLength(ETHER_MAC_FRAME_BYTES);
    frame->setEtherType(MSRP_ETHERTYPE);
    frame->encapsulate(srp);

    delete controlInfo;

    if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
        frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);

    if (notPortNum != 0)
    {
        send(frame, "lowerLayerOut");
                EV_INFO << "Sending SRP frame " << frame << " with destination = " << frame->getDest() << ", port = " << portNum
                        << endl;
    }
    else{
        delete frame;
    }
}

void SRPEtherLLC::deliverSRP(EtherFrame * frame)
{
    SRPFrame * srp = check_and_cast<SRPFrame *>(frame->decapsulate());

    Ieee802Ctrl * controlInfo = new Ieee802Ctrl();
    controlInfo->setSrc(frame->getSrc());
    controlInfo->setSwitchPort(0);
    controlInfo->setDest(frame->getDest());

    srp->setControlInfo(controlInfo);

    delete frame; // we have the SRP packet, so delete the frame

    EV_INFO << "Sending SRP frame " << srp << " to the SRP module" << endl;
    send(srp, "srpOut");
}

}
