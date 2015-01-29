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
#ifndef __CORE4INET_PCFINCOMING_H_
#define __CORE4INET_PCFINCOMING_H_

//CoRE4INET
#include "CoRE4INET_CTIncoming.h"
//Auto-Generated Messages
#include "PCFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Class for the critical traffic conformance check of
 * pcf traffic.
 *
 * This class checks whether incoming traffic was conform with the configured pcf type.
 * Conform messages are forwarded from in to out
 *
 * @sa Incoming
 *
 * @ingroup AS6802
 *
 * @author Lazar Todorov, Till Steinbach
 */
class PCFIncoming : public virtual CTIncoming
{
    private:
        /**
         * @brief caches pcfType parameter
         */
        PCFType pcfType;

    protected:
        /**
         * @brief Forwards messages arriving on in-gate to out-gate checks
         * conformance with configured pcf type.
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

        /**
         * @brief Initialization of the module
         */
        virtual void initialize() override;

    public:
        /**
         * @brief Constructor.
         */
        PCFIncoming();

};

} //namespace

#endif
