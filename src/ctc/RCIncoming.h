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

#ifndef __TTETHERNETMODELV2_RCINCOMING_H_
#define __TTETHERNETMODELV2_RCINCOMING_H_

#include <omnetpp.h>
#include <Incoming.h>

namespace TTEthernetModel {

/**
 * @brief Class for the critical traffic conformance check of
 * rate-constrained traffic.
 *
 * This class checks whether incoming traffic was conform with the configured bag.
 * Conform messages are forwarded from in to out
 *
 * @sa Incoming
 */
class RCIncoming : public Incoming
{
    private:
        /**
         * Saves the tickcount of the last message
         */
        uint64_t lastArrived;

        /**
         * @brief caches bag parameter
         */
        uint64_t bag;
    protected:
        /**
         * @brief Forwards messages arriving on in-gate to out-gate checks
         * conformance with configured bag.
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
    public:
        /**
         * @brief Constructor.
         */
        RCIncoming();
};

} //namespace

#endif
