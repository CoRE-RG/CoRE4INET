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

#ifndef __TTETHERNETMODELV2_CTINCONTROL_H_
#define __TTETHERNETMODELV2_CTINCONTROL_H_

#include <omnetpp.h>

#include <EtherFrame_m.h>
#include <ModuleAccess.h>

#include <CTIncoming.h>
#include <Buffer.h>

#include "TTE4INETDefs.h"
#include "HelperFunctions.h"

#include <map>
#include <list>


namespace TTEthernetModel {

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
template <class IC>
class CTInControl : public IC
{
    private:
        /**
         * @brief Lists of incoming modules for each critical traffic id.
         */
        std::map<uint16_t, std::list<CTIncoming*> > ct_incomings;

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
        static simsignal_t ctDroppedSignal;

    protected:
        /**
         * @brief Initialization of the module
         */
        virtual void initialize();

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
        virtual void handleMessage(cMessage *msg);
    public:
        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);
    private:
        /**
         * @brief Helper function checks whether a Frame is critical traffic.
         *
         * @param frame Pointer to the frame to check.
         * @return true if frame is critical, else false
         */
        virtual bool isCT(EtherFrame *frame);

        /**
         * @brief Returns the critical traffic id for a given frame.
         *
         * @warning does not check if it is really critical traffic.
         * If you need to be sure use isCT(EtherFrame *frame)
         *
         * @param frame Pointer to the frame to get critical traffic id from.
         * @return critical traffic id
         *
         * @sa isCT(EtherFrame *frame)
         */
        virtual uint16_t getCTID(EtherFrame *frame);
};

template <class IC>
simsignal_t CTInControl<IC>::ctDroppedSignal = SIMSIGNAL_NULL;

template <class IC>
void CTInControl<IC>::initialize()
{
    BaseInControl::initialize();
    ctDroppedSignal = cComponent::registerSignal("ctDropped");
}

template <class IC>
void CTInControl<IC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        EtherFrame *frame = (EtherFrame*) msg;

        //Auf CTCs verteilen oder BE traffic
        if (isCT(frame))
        {
            this->recordPacketReceived(frame);

            std::map<uint16_t, std::list<CTIncoming *> >::iterator ct_incomingList = ct_incomings.find(getCTID(frame));
            if (ct_incomingList != ct_incomings.end())
            {
                //Send to all CTCs for the CT-ID
                for (std::list<CTIncoming*>::iterator ct_incoming = ct_incomingList->second.begin(); ct_incoming
                        != ct_incomingList->second.end(); ct_incoming++)
                {
                    IC::setParameters(frame);
                    cSimpleModule::sendDirect(frame->dup(), (*ct_incoming)->gate("in"));
                }
                delete frame;
            }
            else
            {
                cComponent::emit(ctDroppedSignal, frame);
                IC::hadError=true;
                if(ev.isGUI()){
                    cComponent::bubble("No matching buffer configured");
                    cComponent::getDisplayString().setTagArg("i2", 0, "status/excl3");
                    cComponent::getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                    cModule::getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    cModule::getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                    cModule::getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    cModule::getParentModule()->getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                }
                delete frame;
            }
        }else{
            IC::handleMessage(msg);
        }
    }
    else{
        IC::handleMessage(msg);
    }
}

template <class IC>
void CTInControl<IC>::handleParameterChange(const char* parname){
    IC::handleParameterChange(parname);

    ctMask = (uint32_t)cComponent::par("ct_mask").longValue();
    ctMarker = (uint32_t)cComponent::par("ct_marker").longValue();

    ct_incomings.clear();

    std::vector<std::string> ct_incomingPaths = cStringTokenizer(cComponent::par("ct_incomings").stringValue(), DELIMITERS).asVector();
    for(std::vector<std::string>::iterator ct_incomingPath = ct_incomingPaths.begin();
            ct_incomingPath!=ct_incomingPaths.end();ct_incomingPath++){
        cModule* module = simulation.getModuleByPath((*ct_incomingPath).c_str());
        if(!module){
            module = findModuleWhereverInNode((*ct_incomingPath).c_str(),this);
        }
        if(module){
            if(findContainingNode(module)!=findContainingNode(this)){
                opp_error("Configuration problem of ct_incomings: Module: %s is not in node %s! Maybe a copy-paste problem?", (*ct_incomingPath).c_str(),
                        findContainingNode(this)->getFullName());
            }
            else
            {
                CTIncoming *ct_incoming = dynamic_cast<CTIncoming*> (module);
                if(ct_incoming){
                    Buffer *buffer = dynamic_cast<Buffer*> (ct_incoming->gate("out")->getPathEndGate()->getOwner());
                    if(buffer && buffer->hasPar("ct_id")){
                        ct_incomings[buffer->par("ct_id").longValue()].push_back(ct_incoming);
                    }
                    else{
                        opp_error("CTIncoming module %s has no Buffer attached with ct_id configured!", (*ct_incomingPath).c_str());
                    }
                }
                else{
                    opp_error("Configuration problem of ct_incomings: Module: %s is no CTIncoming module!", (*ct_incomingPath).c_str());
                }
            }
        }
        else{
            opp_error("Configuration problem of ct_incomings: Module: %s could not be resolved!", (*ct_incomingPath).c_str());
        }
    }
}

template <class IC>
bool CTInControl<IC>::isCT(EtherFrame *frame)
{
    unsigned char macBytes[6];
    frame->getDest().getAddressBytes(macBytes);
    //Check for ct
    if ((((macBytes[0] << 24) | (macBytes[1] << 16) | (macBytes[2] << 8) | (macBytes[3])) & ctMask) == (ctMarker
            & ctMask))
    {
        return true;
    }
    //TODO More checking ?
    return false;
}

template <class IC>
uint16_t CTInControl<IC>::getCTID(EtherFrame *frame)
{
    unsigned char macBytes[6];
    frame->getDest().getAddressBytes(macBytes);
    return (macBytes[4] << 8) | macBytes[5];
}

}

#endif
