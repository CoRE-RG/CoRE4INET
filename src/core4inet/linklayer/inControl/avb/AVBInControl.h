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

#ifndef CORE4INET_AVBINCONTROL_H_
#define CORE4INET_AVBINCONTROL_H_

//CoRE4INET
#include "core4inet/utilities/ModuleAccess.h"
#include "core4inet/services/avb/SRP/SRPTable.h"
//CoRE4INET Auto-generated Messages
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 * AVB traffic arriving on in-gate is forwarded to the incoming module
 * or dropped if there is no module configured. Best-effort frames are
 * forwarded through the out-gate.
 *
 * @author Philipp Meyer
 *
 */
template<class IC>
class AVBInControl : public IC
{
    protected:
        /**
         * @brief Forwards frames to the appropriate incoming module
         *
         * An AVB frame arriving on in-gate is forwarded to the AVBctc module
         * or dropped if there is no module configured.
         *
         * @param msg incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

    private:
        /**
         * @brief Helper function checks whether a Frame is AVB traffic.
         *
         * @param frame Pointer to the frame to check.
         * @return true if frame is critical, else false
         */
        virtual bool isAVB(const inet::EtherFrame *frame) const;
};

template<class IC>
void AVBInControl<IC>::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg);

        //Is AVB Frame?
        if (frame && isAVB(frame))
        {
            this->recordPacketReceived(frame);
            cSimpleModule::sendDirect(frame,
                    cModule::getParentModule()->getParentModule()->getSubmodule("avbCTC")->gate("in"));
        }
        else
        {
            IC::handleMessage(msg);
        }
    }
    else
    {
        IC::handleMessage(msg);
    }
}

template<class IC>
bool AVBInControl<IC>::isAVB(const inet::EtherFrame *frame) const
{
    bool result = false;
    if (const inet::EthernetIIFrame* ether2frame = dynamic_cast<const inet::EthernetIIFrame*>(frame))
    {
        if (ether2frame->getEtherType() == 0x8100)
        {
            if (const EthernetIIFrameWithQTag* qframe = dynamic_cast<const EthernetIIFrameWithQTag*>(frame))
            {
                SRPTable* srpTable = dynamic_cast<SRPTable*>(findModuleWhereverInNode("srpTable", cModule::getParentModule()));
                if (srpTable->containsStream(qframe->getDest(), qframe->getVID()))
                {
                    result = true;
                }
            }
            else
            {
                throw cRuntimeError("Ethertype is 0x8100 but message type is not EthernetIIFrameWithQTag");
            }
        }
    }
    return result;
}

}

#endif
