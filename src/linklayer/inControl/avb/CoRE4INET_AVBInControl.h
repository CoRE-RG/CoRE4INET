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

#ifndef __CORE4INET_AVBINCONTROL_H_
#define __CORE4INET_AVBINCONTROL_H_

//CoRE4INET Auto-generated Messages
#include "AVBFrame_m.h"
//INET Auto-generated Messages
#include "EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 *Critical traffic arriving on in-gate is forwarded to the incoming modules
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
         * @brief Forwards frames to the appropriate incoming modules
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
        virtual bool isAVB(const EtherFrame *frame) const;
};

template<class IC>
void AVBInControl<IC>::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        EtherFrame *frame = dynamic_cast<EtherFrame*>(msg);

        //Is AVB Frame?
        if (frame && isAVB(frame))
        {
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
bool AVBInControl<IC>::isAVB(const EtherFrame *frame) const
{
    //TODO: Major: Detect AVB frame only using priority
    if (dynamic_cast<const EthernetIIFrameWithQTag*>(frame))
    {
        if (dynamic_cast<const AVBFrame*>(frame))
        {
            return true;
        }
    }
    return false;
}

}

#endif
