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

#ifndef CORE4INET_IEEE8021QINCONTROLINCONTROL_H_
#define CORE4INET_IEEE8021QINCONTROLINCONTROL_H_

#include <algorithm>    // std::sort

//INET Auto-generated Messages
#include "EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 * @author Till Steinbach
 */
template<class IC>
class IEEE8021QInControl : public IC
{
    public:
        /**
         * @brief Constructor
         */
        IEEE8021QInControl();
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

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

    private:
        /**
         * @brief Untagged VLAN.
         * Untagged incoming frames get tagged with this VLAN. Outgoing frames with this VLAN get untagged.
         */
        uint16_t untaggedVID;
        /**
         * @brief Tagged VLANs.
         * Only outgoing frames with one of the VLANs in this list are transmitted. Default is "0" to allow for untagged frames
         */
        std::vector<int> taggedVIDs;
};

template<class IC>
IEEE8021QInControl<IC>::IEEE8021QInControl()
{
    untaggedVID = 0;
}

template<class IC>
void IEEE8021QInControl<IC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg))
        {

            if (EthernetIIFrameWithQTag* qframe = dynamic_cast<EthernetIIFrameWithQTag*>(frame))
            {
                //VLAN tag if requested
                if (this->untaggedVID && qframe->getVID() == 0)
                {
                    qframe->setVID(this->untaggedVID);
                }
                //VLAN check if port is tagged with VLAN
                bool found = false;
                for (std::vector<int>::iterator vid = this->taggedVIDs.begin(); vid != this->taggedVIDs.end(); ++vid)
                {
                    //Shortcut due to sorted vector
                    if ((*vid) > qframe->getVID())
                    {
                        break;
                    }
                    if ((*vid) == qframe->getVID())
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    EV_WARN << "Received IEEE 802.1Q frame with VID " << qframe->getVID()
                            << " but port was not tagged with that VID. Frame was dropped";
                    delete qframe;
                    return;
                }
            }

            this->recordPacketReceived(frame);

            if (IC::isPromiscuous() || frame->getDest().isMulticast())
            {
                cSimpleModule::send(msg, "out");
            }
            else
            {
                inet::MACAddress address;
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

template<class IC>
void IEEE8021QInControl<IC>::handleParameterChange(const char* parname)
{
    IC::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "untaggedVID"))
    {
        this->untaggedVID = static_cast<uint16_t>(parameterULongCheckRange(cComponent::par("untaggedVID"), 0,
                MAX_VLAN_NUMBER));
    }
    if (!parname || !strcmp(parname, "taggedVIDs"))
    {
        taggedVIDs = cStringTokenizer(cComponent::par("taggedVIDs"), ",").asIntVector();
        std::sort(taggedVIDs.begin(), taggedVIDs.end());
    }
}

}

#endif
