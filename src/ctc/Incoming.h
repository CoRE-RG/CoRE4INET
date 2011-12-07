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

#ifndef __TTETHERNETMODELV2_INCOMING_H_
#define __TTETHERNETMODELV2_INCOMING_H_

#include <omnetpp.h>

namespace TTEthernetModel {

/**
 * @brief Base class for the critical traffic conformance check.
 *
 * This base class simply forwards messages from in to out
 *
 * @sa RCIncoming, TTIncoming
 */
class Incoming : public cSimpleModule
{
    protected:
        /**
         * @brief set to true if there was an error during runtime
         */
        bool hadError;
        /**
         * @brief Signal that is emitted when a frame is dropped.
         *
         * Frames may be dropped when there was a violation of CT rules.
         */
        static simsignal_t ctDroppedSignal;
    public:
        /**
         * @brief Constructor
         */
        Incoming();
    protected:
        /**
         * @brief Initialization of the module
         */
        virtual void initialize();
        /**
         * @brief Forwards messages arriving on in-gate to out-gate
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif
