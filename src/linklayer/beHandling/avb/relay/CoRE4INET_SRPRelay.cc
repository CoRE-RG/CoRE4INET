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

#include "CoRE4INET_SRPRelay.h"

//CoRE4INET
#include "CoRE4INET_AVBDefs.h"
//Auto-generated Messages
#include "ExtendedIeee802Ctrl_m.h"

namespace CoRE4INET {

Define_Module(SRPRelay);

void SRPRelay::initialize(int stage)
{
    ::Ieee8021dRelay::initialize(stage);
}

void SRPRelay::handleMessage(cMessage * msg)
{
    if (!isOperational)
    {
        EV_ERROR << "Message '" << msg << "' arrived when module status is down, dropped it." << endl;
        delete msg;
        return;
    }

    if (msg && !msg->isSelfMessage())
    {
        // messages from STP process
        if (msg->arrivedOn("srpIn"))
        {
            SRPFrame * srpFrame = check_and_cast<SRPFrame*>(msg);
            dispatchSRP(srpFrame);

        }
        else if (msg->arrivedOn("ifIn"))
        {
            EtherFrame * frame = check_and_cast<EtherFrame*>(msg);
            if ((frame->getDest() == SRP_ADDRESS || frame->getDest() == bridgeAddress))
            {
                EV_DETAIL << "Deliver SRPFrame to the SRP module" << endl;
                deliverSRP(frame); // deliver to the SRP module
            }
            else
            {
                ::Ieee8021dRelay::handleMessage(msg);
            }
        }
    }
    else
        throw cRuntimeError("This module doesn't handle self-messages!");
}

void SRPRelay::dispatchSRP(SRPFrame * srp)
{
    ExtendedIeee802Ctrl * controlInfo = dynamic_cast<ExtendedIeee802Ctrl *>(srp->removeControlInfo());
    if (!controlInfo)
    {
        throw cRuntimeError("SRP is missing ControlInfo");
    }
    int portNum = controlInfo->getSwitchPort();
    int notPortNum = controlInfo->getNotSwitchPort();
    MACAddress address = controlInfo->getDest();

    if (portNum >= static_cast<int>(portCount))
        throw cRuntimeError("Output port %d doesn't exist!", portNum);

    EthernetIIFrame * frame = new EthernetIIFrame(srp->getName());
    frame->setSrc(bridgeAddress);
    frame->setDest(address);
    frame->setByteLength(ETHER_MAC_FRAME_BYTES);
    frame->setEtherType(MSRP_ETHERTYPE);
    frame->encapsulate(srp);

    delete controlInfo;

    if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
        frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);

    //Broadcast
    if (portNum < 0)
    {
        for (size_t i = 0; i < portCount; ++i)
        {
            if (static_cast<int>(i) != notPortNum)
            {
                send(frame->dup(), "ifOut", static_cast<int>(i));
                EV_INFO << "Sending SRP frame " << frame << " with destination = " << frame->getDest() << ", port = "
                        << i << endl;
            }
        }
        delete frame;
    }
    else
    {
        send(frame, "ifOut", portNum);
        EV_INFO << "Sending SRP frame " << frame << " with destination = " << frame->getDest() << ", port = " << portNum
                << endl;
    }
}

void SRPRelay::deliverSRP(EtherFrame * frame)
{
    SRPFrame * srp = check_and_cast<SRPFrame *>(frame->decapsulate());

    Ieee802Ctrl * controlInfo = new Ieee802Ctrl();
    controlInfo->setSrc(frame->getSrc());
    controlInfo->setSwitchPort(frame->getArrivalGate()->getIndex());
    controlInfo->setDest(frame->getDest());

    srp->setControlInfo(controlInfo);

    delete frame; // we have the SRP packet, so delete the frame

    EV_INFO << "Sending SRP frame " << srp << " to the SRP module" << endl;
    send(srp, "srpOut");
}

}
