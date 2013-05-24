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

#ifndef __TTETHERNETMODELV2_TTEINPUT_H_
#define __TTETHERNETMODELV2_TTEINPUT_H_

#include <omnetpp.h>

#include <ctc/Incoming.h>
#include <EtherFrame_m.h>

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
class TTEInput : public cSimpleModule
{
    protected:
        /**
         * @brief Lists of incoming modules for each critical traffic id.
         */
        std::map<uint16_t, std::list<Incoming*> > incomings;

        /**
         * @brief caches ct_mask parameter
         */
        uint32_t ctMask;
        /**
         * @brief caches ct_marker parameter
         */
        uint32_t ctMarker;
        /**
         * @brief caches promiscuous parameter
         */
        bool promiscuous;
        /**
         * @brief set to true if there was an error during runtime
         */
        bool hadError;
        /**
         * @brief Signal that is emitted when a frame is dropped.
         *
         * Frames may be dropped when no incoming module is configured.
         */
        static simsignal_t ctDroppedSignal;
    public:
        /**
         * @brief Constructor
         */
        TTEInput();
//        /**
//         * @brief Adds an incoming module to the list.
//         *
//         * @param ctID critical traffic id of the incoming module
//         * @param incoming Pointer to the Incoming module
//         */
//        virtual void addIncoming(uint16 ctID, Incoming *incoming);
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
    protected:
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
}

#endif
