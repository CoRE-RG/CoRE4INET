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

#ifndef __CORE4INET_RCINCOMING_H_
#define __CORE4INET_RCINCOMING_H_

//CoRE4INET
#include "CoRE4INET_CTIncoming.h"
#include "CoRE4INET_Timed.h"

namespace CoRE4INET {

/**
 * @brief Class for the critical traffic conformance check of
 * rate-constrained traffic.
 *
 * This class checks whether incoming traffic was conform with the configured bag.
 * Conform messages are forwarded from in to out
 *
 * @sa AS6802
 *
 * @author Till Steinbach
 */
class RCIncoming : public virtual CTIncoming, public virtual Timed
{
    private:
        /**
         * Saves the tickcount of the last message
         */
        uint64_t lastArrived;
        /**
         * Checks weather this is the first message. The first message is always allowed to pass
         */
        bool firstMessage;

        /**
         * @brief caches bag parameter
         */
        uint64_t bag;
        /**
         * @brief caches jitter parameter
         */
        uint64_t jitter;
    protected:
        /**
         * @brief Initialization of the module
         */
        virtual void initialize() override;

        /**
         * @brief Forwards messages arriving on in-gate to out-gate checks
         * conformance with configured bag.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
    public:
        /**
         * @brief Constructor.
         */
        RCIncoming();
};

} //namespace

#endif
