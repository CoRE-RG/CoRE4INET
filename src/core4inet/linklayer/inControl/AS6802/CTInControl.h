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

#ifndef CORE4INET_CTINCONTROL_H_
#define CORE4INET_CTINCONTROL_H_

//Std
#include <unordered_map>

#include <list>
//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/incoming/AS6802/CTIncoming.h"
#include "core4inet/buffer/AS6802/CTBuffer.h"
#include "core4inet/utilities/customWatch.h"
#include "core4inet/utilities/HelperFunctions.h"
#include "core4inet/utilities/ConfigFunctions.h"
//INET
#include "inet/common/ModuleAccess.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 * Critical traffic arriving on in-gate is forwarded to the incoming modules
 * or dropped if there is no module configured. Best-effort frames are
 * forwarded through the out-gate.
 *
 * @ingroup AS6802
 *
 * @author Till Steinbach
 */
template<class IC>
class CTInControl : public IC
{
    private:
        /**
         * @brief Lists of incoming modules for each critical traffic id.
         */
        std::unordered_map<uint16_t, std::list<CTIncoming*> > ct_incomings;

        /**
         * @brief caches ct_mask parameter
         */
        uint32_t ctMask;
        /**
         * @brief caches ct_marker parameter
         */
        uint32_t ctMarker;
    protected:
        /**
         * @brief Signal that is emitted when a frame is dropped.
         *
         * Frames may be dropped when no incoming module is configured.
         */
        static simsignal_t droppedPkSignal;

    protected:
        /**
         * @brief Initialization of the module
         */
        virtual void initialize() override;

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
};

template<class IC>
simsignal_t CTInControl<IC>::droppedPkSignal = cComponent::registerSignal("droppedPk");

template<class IC>
void CTInControl<IC>::initialize()
{
    BaseInControl::initialize();
    WATCH_LISTUMAP(ct_incomings);
}

template<class IC>
void CTInControl<IC>::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame *>(msg);

        //Auf CTCs verteilen oder BE traffic
        if (frame && isCT(frame, ctMarker, ctMask))
        {
            this->recordPacketReceived(frame);

            std::unordered_map<uint16_t, std::list<CTIncoming *> >::iterator ct_incomingList = ct_incomings.find(
                    getCTID(frame));
            if (ct_incomingList != ct_incomings.end())
            {
                //Send to all CTCs for the CT-ID
                for (std::list<CTIncoming*>::iterator ct_incoming = ct_incomingList->second.begin();
                        ct_incoming != ct_incomingList->second.end(); ct_incoming++)
                {
                    IC::setParameters(frame);
                    cSimpleModule::sendDirect(frame->dup(), (*ct_incoming)->gate("in"));
                }
                delete frame;
            }
            else
            {
                cComponent::emit(droppedPkSignal, frame);
                IC::hadError = true;
                if (getEnvir()->isGUI())
                {
                    cComponent::bubble("No matching buffer configured");
                    cComponent::getDisplayString().setTagArg("i2", 0, "status/excl3");
                    cComponent::getDisplayString().setTagArg("tt", 0,
                            "WARNING: Input configuration problem - No matching buffer configured");
                    cModule::getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    cModule::getParentModule()->getDisplayString().setTagArg("tt", 0,
                            "WARNING: Input configuration problem - No matching buffer configured");
                    cModule::getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 0,
                            "status/excl3");
                    cModule::getParentModule()->getParentModule()->getDisplayString().setTagArg("tt", 0,
                            "WARNING: Input configuration problem - No matching buffer configured");
                }
                delete frame;
            }
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
void CTInControl<IC>::handleParameterChange(const char* parname)
{
    IC::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "ct_mask"))
    {
        this->ctMask = cComponent::par("ct_mask");
    }
    if (!parname || !strcmp(parname, "ct_marker"))
    {
        this->ctMarker = cComponent::par("ct_marker");
    }
    if (!parname || !strcmp(parname, "ct_incomings"))
    {
        ct_incomings.clear();
        std::vector<cModule*> modules = parameterToModuleList(cComponent::par("ct_incomings"), DELIMITERS);
        for (std::vector<cModule*>::const_iterator module = modules.begin(); module != modules.end(); ++module)
        {
            if (inet::findContainingNode(*module) != inet::findContainingNode(this))
            {
                throw cRuntimeError(
                        "Configuration problem of parameter ct_incomings in module %s: Module: %s is not in node %s! Maybe a copy-paste problem?",
                        this->getFullName(), (*module)->getFullName(), inet::findContainingNode(this)->getFullName());
            }
            if (CTIncoming *ct_incoming = dynamic_cast<CTIncoming*>(*module))
            {
                if (CTBuffer *buffer = dynamic_cast<CTBuffer*>(ct_incoming->gate("out")->getPathEndGate()->getOwner()))
                {
                    ct_incomings[buffer->getCTID()].push_back(ct_incoming);
                }
                else
                {
                    throw cRuntimeError("CTIncoming module %s has no CTBuffer attached!", ct_incoming->getFullName());
                }
            }
            else
            {
                throw cRuntimeError(
                        "Configuration problem of parameter ct_incomings in module %s: Module: %s is no CTIncoming module!",
                        this->getFullName(), (*module)->getFullName());
            }
        }
    }
}

}

#endif
