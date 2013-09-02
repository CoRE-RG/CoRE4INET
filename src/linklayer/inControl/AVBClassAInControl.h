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

#ifndef __TTETHERNETMODELV2_AVBCLASSAINCONTROL_H_
#define __TTETHERNETMODELV2_AVBCLASSAINCONTROL_H_

#include <omnetpp.h>

#include <EtherFrame_m.h>
#include <SRPFrame_m.h>
#include <ModuleAccess.h>

#include <AVBIncoming.h>
#include <Buffer.h>

#include "TTE4INETDefs.h"
#include "HelperFunctions.h"

#include <map>
#include <list>


namespace TTEthernetModel {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 *Critical traffic arriving on in-gate is forwarded to the incoming modules
 * or dropped if there is no module configured. Best-effort frames are
 * forwarded through the out-gate.
 */
template <class IC>
class AVBClassAInControl : public IC
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
        virtual void handleMessage(cMessage *msg);

    private:
        /**
         * @brief Helper function checks whether a Frame is AVB traffic.
         *
         * @param frame Pointer to the frame to check.
         * @return true if frame is critical, else false
         */
        virtual bool isAVB(EtherFrame *frame);
};

template <class IC>
void AVBClassAInControl<IC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        EtherFrame *frame = (EtherFrame*) msg;

        //Is AVB Frame?
        if(isAVB(frame))
        {
            cSimpleModule::sendDirect(frame, cModule::getParentModule()->getParentModule()->getSubmodule("avbCTC")->gate("in"));
        }else{
            std::string msgClass = frame->getEncapsulatedPacket()->getClassName();
            std::string msgName = frame->getEncapsulatedPacket()->getName();
            if(msgClass.compare("TTEthernetModel::SRPFrame") == 0)
            {
                if(msgName.compare("Talker Advertise"))
                {
                    frame->setDest(*(new MACAddress("000000000000")));

                }
                SRPFrame *srpFrame = ((SRPFrame*)frame->getEncapsulatedPacket());
                srpFrame->setPortIndex(cModule::getParentModule()->getIndex());
            }

            IC::handleMessage(msg);
        }
    }
    else{
        IC::handleMessage(msg);
    }
}

template <class IC>
bool AVBClassAInControl<IC>::isAVB(EtherFrame *frame)
{
    bool result = false;
    std::string className = frame->getClassName();
    if(className.compare("TTEthernetModel::AVBFrame") == 0)
        result = true;
    cComponent::bubble(frame->getClassName());
    return result;
}

}

#endif
