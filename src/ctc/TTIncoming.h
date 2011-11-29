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

#ifndef __TTETHERNETMODELV2_TTINCOMING_H_
#define __TTETHERNETMODELV2_TTINCOMING_H_

#include <omnetpp.h>

#include <Incoming.h>
#include <EtherFrame_m.h>

namespace TTEthernetModel {

/**
 * @brief Class for the critical traffic conformance check of
 * time-triggered traffic.
 *
 * This class checks whether incoming traffic arrived in the configured receive window.
 * Messages are delayed until the configured permanence point in time.
 *
 * @sa Incoming
 */
class TTIncoming : public Incoming
{
    private:
        /**
         * @brief Stores the frame until the configured permanence point in time.
         */
        EtherFrame *frame;

    public:
        /**
         * @brief Constructor
         */
        TTIncoming();
        /**
         * @brief Destructor
         */
        virtual ~TTIncoming();
    protected:
        /**
         * @brief Forwards messages arriving on in-gate to out-gate checks
         * conformance with receive window, delays messages until permanence pit.
         *
         * After checking the receive window when a frame arrived, a SchedulerActionTimeEvent
         * is registered at the TTEScheduler that triggeres the forwarding at the permanence
         * point in time that was configured
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif
