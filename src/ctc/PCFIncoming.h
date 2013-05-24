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
#ifndef __TTETHERNETMODELV2_PCFINCOMING_H_
#define __TTETHERNETMODELV2_PCFINCOMING_H_

#include <omnetpp.h>
#include <Incoming.h>

#include "PCFrame_m.h"

namespace TTEthernetModel {

/**
 * @brief Class for the critical traffic conformance check of
 * pcf traffic.
 *
 * This class checks whether incoming traffic was conform with the configured pcf type.
 * Conform messages are forwarded from in to out
 *
 * @sa Incoming
 *
 * @author Lazar Todorov, Till Steinbach
 */
class PCFIncoming:public Incoming
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
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);

        /**
         * @brief Initialization of the module
         */
        virtual void initialize();

    public:
        /**
         * @brief Constructor.
         */
        PCFIncoming();

};

}//namespace

#endif
