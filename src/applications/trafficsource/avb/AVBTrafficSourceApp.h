//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __CORE4INET_AVBTRAFFICSOURCEAPP_H_
#define __CORE4INET_AVBTRAFFICSOURCEAPP_H_

#include <omnetpp.h>
#include "TrafficSourceAppBase.h"
#include "Timed.h"
#include "AVBIncoming.h"

namespace CoRE4INET {

/**
 * @brief Simple AVB Traffic Source-Application.
 *
 *
 * @sa TTEApplicationBase
 * @ingroup Applications
 *
 * @author Philipp Meyer
 *
 * TODO Normal: Documentation
 */

class AVBTrafficSourceApp : public TrafficSourceAppBase, public Timed
{
    private:
        bool talker;
        bool isStreaming;
        unsigned long streamID;
        unsigned int frameSize;
        unsigned int intervalFrames;
        unsigned int payload;
        Buffer *srpOutBuffer;
        AVBIncoming* avbCTC;
        cModule *avbOutCTC;
        double tick;
    protected:
        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize();
        /**
         * @brief Handles message generation
         */
        virtual void handleMessage(cMessage *msg);

        void sendAVBFrame();
};

} /* namespace CoRE4INET */
#endif /* __CORE4INET_AVBTRAFFICSOURCEAPP_H_ */
