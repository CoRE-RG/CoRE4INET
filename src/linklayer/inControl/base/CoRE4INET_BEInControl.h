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

#ifndef __CORE4INET_BEINCONTROL_H_
#define __CORE4INET_BEINCONTROL_H_

//INET Auto-generated Messages
#include "EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 * @author Till Steinbach
 */
template<class IC>
class BEInControl : public IC
{
    protected:
        /**
         * @brief Forwards frames to the appropriate incoming modules
         *
         * Critical traffic arriving on in-gate is forwarded to the incoming modules
         * or dropped if there is no module configured. Best-effort frames are
         * forwarded through the out-gate. The function timestamps messages using the
         * received and received_total parameters.
         *
         * @param msg incoming message
         */
        virtual void handleMessage(cMessage *msg) override;
};

template<class IC>
void BEInControl<IC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (EtherFrame *frame = dynamic_cast<EtherFrame*>(msg))
        {
            this->recordPacketReceived(frame);

            if (IC::isPromiscuous() || frame->getDest().isMulticast())
            {
                cSimpleModule::send(msg, "out");
            }
            else
            {
                MACAddress address;
                address.setAddress(frame->getArrivalGate()->getPathStartGate()->getOwnerModule()->par("address"));
                if (frame->getDest().equals(address))
                {
                    cSimpleModule::send(msg, "out");
                }
                else
                {
                    IC::handleMessage(msg);
                }
            }
        }
        else
        {
            throw cRuntimeError("Received message on port in that is no EtherFrame");
        }
    }
    else
    {
        IC::handleMessage(msg);
    }
}

}

#endif
