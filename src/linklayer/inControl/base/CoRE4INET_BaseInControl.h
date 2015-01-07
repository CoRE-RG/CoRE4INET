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

#ifndef __CORE4INET_BASEINCONTROL_H_
#define __CORE4INET_BASEINCONTROL_H_

//OMNeT++
#include "csimplemodule.h"
//CoRE4INET
#include "CoRE4INET_Timed.h"
//INET Auto-generated Messages
#include "EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 * @author Till Steinbach
 */
class BaseInControl : public virtual cSimpleModule, public Timed
{
    private:
        /**
         * @brief True if parameters were initialized
         */
        bool parametersInitialized;
        /**
         * @brief caches promiscuous parameter
         */
        bool promiscuous;
    protected:
        /**
         * @brief set to true if there was an error during runtime
         */
        bool hadError;

        /**
         * Signal that is emitted every time a frame was received.
         */
        static simsignal_t rxPkSignal;
    public:
        /**
         * @brief Constructor
         */
        BaseInControl()
        {
            parametersInitialized = false;
            promiscuous = false;
            hadError = false;
        }

        /**
         * @brief Initializes the module
         */
        virtual void initialize() override;

        virtual void handleMessage(cMessage *msg) override
        {
            delete msg;
        }

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override
        {
            Timed::handleParameterChange(parname);

            if (!parametersInitialized)
            {
                parametersInitialized = true;
            }
            if (!parname || !strcmp(parname, "promiscuous"))
            {
                this->promiscuous = par("promiscuous").boolValue();
            }
        }

        bool isPromiscuous()
        {
            if (!parametersInitialized)
            {
                handleParameterChange(nullptr);
            }
            return promiscuous;
        }
    protected:
        /**
         * @brief Sets parameters in the frame such as received_port and times
         *
         * @param frame the frame that was received
         */
        void setParameters(EtherFrame *frame);

        /**
         * @brief Emits a statistics signal that a frame was received in the buffer
         *
         * @param frame the frame that was received
         */
        void recordPacketReceived(EtherFrame *frame);
};
}

#endif
