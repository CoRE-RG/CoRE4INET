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

#ifndef __CORE4INET_INCOMING_H_
#define __CORE4INET_INCOMING_H_

//OMNeT++
#include "csimplemodule.h"
//INET
#include "EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Base class for the critical traffic conformance check.
 *
 * This base class simply forwards messages from in to out
 *
 * @sa RCIncoming, TTIncoming
 *
 * @author Till Steinbach
 */
class Incoming : public virtual cSimpleModule
{
    private:
        /**
         * @brief True if parameters were initialized
         */
        bool parametersInitialized;

        /**
         * @brief Caches hardware_delay parameter
         */
        simtime_t hardware_delay;
    protected:
        /**
         * @brief set to true if there was an error during runtime
         */
        bool hadError;
        /**
         * @brief Signal that is emitted when a frame is dropped.
         *
         * Frames may be dropped when there was a violation of rules.
         */
        static simsignal_t droppedSignal;
        /**
         * Signal that is emitted every time a frame was received.
         */
        static simsignal_t rxPkSignal;
    public:
        /**
         * @brief Constructor
         */
        Incoming();

        /**
         * @brief returns the configured hardware delay
         *
         * return Hardware delay in simtime
         */
        simtime_t getHardwareDelay();
    protected:
        /**
         * @brief Forwards messages arriving on in-gate to out-gate
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Emits a statistics signal that a frame was received in the buffer
         *
         * @param frame the frame that was received
         */
        void recordPacketReceived(EtherFrame *frame);

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
};

} //namespace

#endif
